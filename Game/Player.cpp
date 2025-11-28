#include "stdafx.h"
//#include "Status.h"
#include "Player.h"
#include <thread>
#include <memory>


namespace {
	Vector2 CHAR_CON_SCL = { 15.0f, 65.0f };

	const Vector3 ATK_COLLISION_SCL = { 40.0f, 10.0f, 30.0f };

}


Player::Player() {

	
}

Player::~Player() {
}


void Player::LoadAnimationClips() {
	//m_animationClips.clear();
	//m_animationClips.resize(EnPlayerState::enPlayerState_Num);

	{
		//m_animationClips[EnPlayerState::enPlayerState_Idle] = new AnimationClip;
		m_animationClips[EnPlayerState::enPlayerState_Idle].Load("Assets/animData/player/idle.tka");
		m_animationClips[EnPlayerState::enPlayerState_Idle].SetLoopFlag(true);
	}
	{
		//m_animationClips[EnPlayerState::enPlayerState_Walk] = new AnimationClip;
		m_animationClips[EnPlayerState::enPlayerState_Walk].Load("Assets/animData/player/walk.tka");
		m_animationClips[EnPlayerState::enPlayerState_Walk].SetLoopFlag(true);
	}
	{
		//m_animationClips[EnPlayerState::enPlayerState_Run] = new AnimationClip;
		m_animationClips[EnPlayerState::enPlayerState_Run].Load("Assets/animData/player/run.tka");
		m_animationClips[EnPlayerState::enPlayerState_Run].SetLoopFlag(true);
	}
	{
		//m_animationClips[EnPlayerState::enPlayerState_Jump] = new AnimationClip;
		m_animationClips[EnPlayerState::enPlayerState_Jump].Load("Assets/animData/player/jump.tka");
		m_animationClips[EnPlayerState::enPlayerState_Jump].SetLoopFlag(false);
	}
}


void Player::SetUpModel() {
	const Vector2 charConScl = CHAR_CON_SCL;

	AnimationClip* a = m_animationClips.data();

	m_modelRender.Init(
		"Assets/modelData/player/unityChan.tkm",
		m_animationClips.data(),
		EnPlayerState::enPlayerState_Num,  // クリップ数
		enModelUpAxisY);
	m_firstPos = m_transform.position;
	m_modelRender.Update();
	
	m_characterController.Init(charConScl.x, charConScl.y, m_transform.position);
}


void Player::InitializeCollisionObject() {
	m_atkCollision = new CollisionObject;
	//攻撃用のボックスコリジョンを作成
	m_atkCollision->CreateBox(m_transform.position, m_transform.rotation, { 20.0f, 5.0f, 15.0f });
	m_atkCollision->SetIsEnable(false);
	UpdateAtkCollisionInfo();
}


void Player::InitializeStatusInfo() {
	//ステータス変数の初期化
	m_state = EnPlayerState::enPlayerState_Idle;
	m_moveState = EnMoveState::enMoveState_Walk;
	m_jumpPowerState = EnJumpPower::enJumpPower_First;
}


bool Player::Start() {
	LoadAnimationClips();
	SetUpModel();
	InitializeCollisionObject();
	InitializeStatusInfo();
	return true;
}


void Player::Update() {

	Move();
	Jump();

	ManageStateAndAnimation();

	//更新
	UpdateTRSInfo();
}


void Player::Render(RenderContext& rc) {
	if (GetModelRender() && !m_isNearCamera) {
		m_modelRender.Draw(rc);
	}
}


void Player::Move() {
	//x,zの移動速度を初期化
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector2 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	//スティックの入力がなければ下の処理をしない
	if (!IsStick(stickL)) {	return;	}

	//カメラの前方向と右方向を取得
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y成分を0にして水平移動のみにする
	forward.y = 0.0f;
	right.y = 0.0f;
	
	//移動ステートに応じたスピードを取得
	const float speed = m_playerStatus.GetMoveSpeed(m_moveState);

	right *= stickL.x *= speed;
	forward *= stickL.y *= speed;

	//加算する移動速度を決定
	const Vector3 addSpeed = right + forward;

	//移動速度を計算して加算
	m_moveSpeed += addSpeed;

	RotateToMoveDirection();
}


void Player::Jump() {
	if (IsJump()) {
		m_moveSpeed.x -= 0.00000001f;
		m_moveSpeed.z -= 0.00000001f;

		UpdateAtkCollisionInfo();
	}


	if (m_isKillEnemy) {
		StompJump();
	}
	else {
		TripleJump();
	}
	
	if (m_atkCollision) {
		//ジャンプ状態に応じて攻撃コリジョンの有効無効を切り替え
		m_atkCollision->SetIsEnable(IsJump());
	}
	
}


void Player::TripleJump() {

	//ジャンプしていれば
	if (IsJump()) {
		//着地時間をリセット
		m_playerStatus.ResetStandingTime();

		//重力を発生させる
		m_moveSpeed.y += m_playerStatus.GetGravity();
		return;
	}

	//滞空時間をリセット
	m_playerStatus.ResetFlyingTime();
	
	//Y方向の移動速度を0にする
	m_moveSpeed.y = 0.0f;


	//最初の段階のジャンプでなければ
	if (m_jumpPowerState != EnJumpPower::enJumpPower_First) {


		//次の段階のジャンプに切り替え可能か
		if (!m_playerStatus.CanNextJump()) {


			//ジャンプ力状態を最初に戻す
			m_jumpPowerState = EnJumpPower::enJumpPower_First;

			//着地時間をリセット
			m_playerStatus.ResetStandingTime();
		}
	}


	//ジャンプボタンが押されていなければ
	if (!g_pad[0]->IsTrigger(enButtonA)) {
		return;
	}

	m_moveSpeed.y = 0.0f;

	//現在のジャンプ力状態をもとにジャンプ力を設定
	const float jumpPower = m_playerStatus.GetJumpInfo(m_jumpPowerState).GetJumpPower();
	m_moveSpeed.y = jumpPower;


	//ジャンプ力状態を更新
	AdjustNextJumpState();
}


void Player::StompJump() {

	if (!IsJump()) m_isKillEnemy = false;


	float jumpPower = 0.0f;
	
	if (!m_playerStatus.CanStompJump()) {
		//敵を倒したフラグをリセット
		m_isKillEnemy = false;

		//滞空時間をリセット
		m_playerStatus.ResetFlyingTime();

		//落下速度を0にする
		m_moveSpeed.y = 0.0f;
		jumpPower = m_playerStatus.GetJumpInfo(EnJumpPower::enJumpPower_First).GetJumpPower();
		m_moveSpeed.y += jumpPower;
		return;
	}
	if (!g_pad[0]->IsTrigger(enButtonA)) {
		return;
	}

	m_isKillEnemy = false;
	//滞空時間をリセット
	m_playerStatus.ResetFlyingTime();
	//落下速度を0にする
	m_moveSpeed.y = 0.0f;
	jumpPower = m_playerStatus.GetJumpInfo(m_jumpPowerState).GetJumpPower();
	m_moveSpeed.y += jumpPower;
	AdjustNextJumpState();	
}


void Player::ManageStateAndAnimation() {
	float animationSpeed = 0.0f;

	m_state = EnPlayerState::enPlayerState_Idle;
	//移動中であれば
	if (IsMove()) {
		m_state = EnPlayerState::enPlayerState_Walk;
		m_moveState = EnMoveState::enMoveState_Walk;

	}
	//走っていれば
	if (IsRun()) {
		m_state = EnPlayerState::enPlayerState_Run;
		m_moveState = EnMoveState::enMoveState_Run;
	}

	animationSpeed = m_animationSpeed[m_state];

	//地面についていなければ
	if (IsJump()) {
		m_state = EnPlayerState::enPlayerState_Jump;
		//AdjustNextJumpState(m_jumpPowerState);
		

		//現在のジャンプ力状態を取得、調整
		uint8_t nextState = m_jumpPowerState + 2;
		EnJumpPower state = static_cast<EnJumpPower>(nextState % enJumpPower_Num);

		//ジャンプ力状態に応じてアニメーション速度を変更
		animationSpeed *= m_playerStatus.GetJumpInfo(m_jumpPowerState).GetJumpAnimSpeed();
	}

	//アニメーション再生
	m_modelRender.SetAnimationSpeed(animationSpeed);
	m_modelRender.PlayAnimation(m_state);
}


void Player::UpdateAtkCollisionInfo() {
	m_atkCollision->SetPosition(m_transform.position);
	m_atkCollision->SetRotation(m_transform.rotation);
	m_atkCollision->Update();
}
