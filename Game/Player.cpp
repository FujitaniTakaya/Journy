#include "stdafx.h"
#include "Player.h"
#include <thread>

//namespace {
//	//ファイルの場所
//	const std::string PLAYER_FILEPATH = "Assets/animData/";
//	//拡張子
//	const std::string PLAYER_EXTENSTION = ".tka";
//
//	struct PlayerAnimInfo{
//		//ファイル名
//		std::string fileName;
//
//		//ファイルパスを取得
//		std::string GetModelFullPath()const {
//			return PLAYER_FILEPATH + fileName + PLAYER_EXTENSTION;
//		}
//	};
//
//
//	const PlayerAnimInfo PlayerInfo[enPlayerState_Num] = {
//		"idle",	"walk" , "run" , "jump"
//	};
//	const char* UNITY_MODEL = "Assets/modelData/unityChan.tkm";
//
//	const Vector2 CHARA_CON = { 15.0f, 65.0f };
//	const Vector3 START_POS = { 100.0f, 0.0f, 100.0f };
//
//	namespace MoveInfo {
//		const float MOVE_SPEED[enPlayerMoveState_Num] = {
//		200.0f, 400.0f
//		};
//
//		const float CAN_NEXT_JUMP_FRAME = 0.2f;					//次の段のジャンプに切り替えれるまでの猶予時間
//
//		const float JUMP_POWER[enJumpPower_Num] = {				//ジャンプパワーの配列
//			200.0f, 400.0f, 600.0f
//		};
//
//
//		const float MAX_FLYING_TIME = 0.5f;						//重力加速の最大フレーム数
//		const float GRAVITY = -9.8f;								//重力加速度
//	}
//
//
//	namespace AtkInfo {
//		const Vector3 ATK_COLLISION_SCL = { 40.0f, 10.0f, 30.0f };
//	}
//
//
//	namespace LifeInfo {
//		const int MAX_LIFE = 3;
//		const float INVINCIBLE_FRAME = 2.0f;						//無敵
//	}
//}
//
//
//Player::Player() {
//	//モデルの設定
//	SetPlayerModel();
//	//自身のコリジョンの設定
//	SetCharaConCollision();
//	//残機と無敵情報の設定
//	SetLifeAndInvincibleInfo();
//}
//
//
//Player::~Player() {
//	//モデルの解放
//	delete m_playerModelRender;
//	m_playerModelRender = nullptr;
//	//攻撃コリジョンの解放
//	delete m_playerAtkCollision;
//	m_playerAtkCollision = nullptr;
//	//キャラコンコリジョンの解放
//	delete m_playerCharaConCollision;
//	m_playerCharaConCollision = nullptr;
//}
//
//void Player::Update() {
//	Move();
//	Jump();
//	JumpAtk();
//	UpdateAtkCollisionInfo();
//	UpdateCharaConCollisionInfo();
//	ManagePlayerState();
//	UpdateCharaPos();
//	m_playerModelRender->Update();
//}
//
//
//void Player::Render(RenderContext& rc) {
//	if (!m_playerModelRender) {
//		return;
//	}
//	if (m_isDraw) {
//		m_playerModelRender->Draw(rc);
//	}
//	
//}
//
//
//void Player::SetPlayerModel() {
//	//アニメーションの読み込み
//	for (int i = 0; i < enPlayerState_Num; i++) {
//		//アニメーションクリップの読み込み
//		m_playerAnimClips[i].Load(PlayerInfo[i].GetModelFullPath().c_str());
//		//ループ設定
//		if (i != enPlayerState_Jump) {
//			m_playerAnimClips[i].SetLoopFlag(true);
//			continue;
//		}
//		else {
//			m_playerAnimClips[i].SetLoopFlag(false);
//		}		
//	}
//	//モデルの初期化
//	ModelRender* model = new ModelRender;
//	model->Init(UNITY_MODEL, m_playerAnimClips, enPlayerState_Num, enModelUpAxisY);
//	m_position = START_POS;
//	model->SetTRS(m_position, m_rotation, Vector3::One);
//
//	m_playerModelRender = model;
//	m_playerModelRender->Update();
//	m_playerCharaCon.Init(CHARA_CON.x, CHARA_CON.y, m_position);
//	
//}
//
//
//void Player::SetAtkCollision() {
//	//攻撃コリジョンの生成
//	CollisionObject* collision = new CollisionObject;
//	//ボックスコリジョンを作成
//	collision->CreateBox(m_position, m_rotation, AtkInfo::ATK_COLLISION_SCL);
//	m_playerAtkCollision = collision;
//	UpdateAtkCollisionInfo();
//
//	m_isAtk = true;
//}
//
//
//void Player::SetCharaConCollision() {
//	CollisionObject* collision = new CollisionObject;
//
//	//カプセルコリジョンを作成	
//	collision->CreateCapsule(m_position, m_rotation, CHARA_CON.x * 1.01f, CHARA_CON.y);
//	m_playerCharaConCollision = collision;
//
//	m_isDraw = true;
//	UpdateCharaConCollisionInfo();
//}
//
//
//void Player::SetLifeAndInvincibleInfo() {
//	m_playerLife = LifeInfo::MAX_LIFE;
//	m_isInvincible = false;
//	m_invincibleFrameCount = 0.0f;
//}
//
//
//void Player::Move() {
//	//x,zの移動速度を初期化
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//	
//	
//	//左スティックの入力量を取得
//	Vector2 stickL;
//	stickL.x = g_pad[0]->GetLStickXF();
//	stickL.y = g_pad[0]->GetLStickYF();
//
//	//スティックの入力がなければ下の処理をしない
//	if (!IsStick(stickL)) {
//		return;
//	}
//
//	//カメラの前方向と右方向を取得
//	Vector3 forward = g_camera3D->GetForward();
//	Vector3 right = g_camera3D->GetRight();
//
//	//y成分を0にして水平移動のみにする
//	forward.y = 0.0f;
//	right.y = 0.0f;
//
//	//移動ステートに応じたスピードを取得
//	float speed = MoveInfo::MOVE_SPEED[m_moveState];
//
//	//移動速度を計算して加算
//	right *= stickL.x * speed;
//	forward *= stickL.y * speed;
//	m_moveSpeed += right + forward;
//	//回転処理
//	Rotate();
//}
//
//
//void Player::Rotate() {
//	//速度をもとに回転を設定
//	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
//	//モデルの回転を更新
//	m_playerModelRender->SetRotation(m_rotation);
//}
//
//
//void Player::Jump() {
//
//	//敵を倒した直後であれば
//	if (IsKillEnemy()) {
//		//敵を倒した後のジャンプ処理
//		JumpAfterKilledEnemy();
//		return;
//	}
//
//	//ジャンプ可能な状態でなければ
//	if (!CanJump()) {
//		//何もしない
//		return;
//	}
//	//次の段階のジャンプが可能でなければ
//	if (m_canNextJump) {
//		//次の段階のジャンプが不可能になれば
//		if (MeasureNextJumpFrameCount()) {
//			//ジャンプ状態を最初に戻す
//			m_jumpState = enJumpPower_First;
//			m_canNextJump = false;
//			return;
//		}
//	}
//	//ジャンプボタンが押されていなければ
//	if (!g_pad[0]->IsTrigger(enButtonB)) {
//		return;
//	}
//	//ジャンプ力を加算
//	float jumpPower = MoveInfo::JUMP_POWER[m_jumpState];
//	m_moveSpeed.y += jumpPower;
//
//	//ジャンプ状態を更新
//	m_jumpState = static_cast<EnJumpPower>((m_jumpState + 1) % enJumpPower_Num);
//	m_canNextJump = true;
//	//最初の段階のジャンプでなければ
//	if (m_jumpState != enJumpPower_First) {
//		return;
//	}
//	m_canNextJump = false;
//}
//
//
//void Player::JumpAtk() {
//	//ジャンプ中なら
//	if (m_playerState == enPlayerState_Jump) {
//		//当たり判定があれば
//		if (m_playerAtkCollision) {
//			//何もしない
//			return;
//		}
//		//攻撃中でなければ
//		if (!m_isAtk) {
//			//攻撃コリジョン生成
//			SetAtkCollision();
//		}
//	}
//	//ジャンプ中でなければ
//	else {
//		//攻撃コリジョンがなければ
//		if (!m_playerAtkCollision) {
//			//何もしない
//			return;
//		}
//		//攻撃コリジョン削除
//		delete m_playerAtkCollision;
//		m_playerAtkCollision = nullptr;
//		m_isAtk = false;
//	}
//}
//
//
//void Player::JumpAfterKilledEnemy() {
//	//地面についていれば
//	if (m_playerCharaCon.IsOnGround()) {
//		//敵を倒したフラグをリセット
//		SetFlagIsKillEnemy(false);
//		return;
//	}
//	//次のジャンプまでの猶予時間を計測
//	//規定時間たったら
//	if (MeasureNextJumpFrameCount()) {
//		//敵を倒したフラグをリセット
//		SetFlagIsKillEnemy(false);
//		//滞空時間をリセット
//		m_flyingTime = 0.0f;
//		//移動速度をリセット
//		m_moveSpeed.y = 0.0f;
//
//		//ジャンプ力を加算
//		float jumpPower = MoveInfo::JUMP_POWER[enJumpPower_First];
//		m_moveSpeed.y += jumpPower;
//		m_jumpState = enJumpPower_First;
//		m_canNextJump = false;
//
//		return;
//	}
//	//ジャンプボタンが押されていなければ
//	if (!g_pad[0]->IsTrigger(enButtonB)) {
//		return;
//	}
//	//敵を倒したフラグをリセット
//	SetFlagIsKillEnemy(false);
//	//滞空時間をリセット
//	m_flyingTime = 0.0f;
//	//移動速度をリセット
//	m_moveSpeed.y = 0.0f;
//
//	//ジャンプ力を加算
//	float jumpPower = MoveInfo::JUMP_POWER[m_jumpState];
//	m_moveSpeed.y += jumpPower;
//	//ジャンプ状態を更新
//	m_jumpState = static_cast<EnJumpPower>((m_jumpState + 1) % enJumpPower_Num);
//	m_canNextJump = false;
//}
//
//
//void Player::ManagePlayerState() {
//	m_playerState = enPlayerState_Idle;
//	
//	//移動中であれば
//	if (IsMove()) {
//		m_playerState = enPlayerState_Walk;
//		m_moveState = enPlayerMoveState_Walk;
//	}
//	//走っていれば
//	if (IsRun()) {
//		m_playerState = enPlayerState_Run;
//		m_moveState = enPlayerMoveState_Run;
//	}
//	//地面についていなければ
//	if (!m_playerCharaCon.IsOnGround()) {
//		m_playerState = enPlayerState_Jump;
//	}
//	//アニメーション再生
//	m_playerModelRender->PlayAnimation(m_playerState);
//}
//
//
//void Player::Invincible() {
//	//非アクティブであれば(無敵状態であれば)
//	if (!m_isInvincible) {
//		return;
//	}	
//
//	//無敵時間を制御するスレッドを生成
//	std::thread controlInvincibleFrameCountThread([&] {
//
//		//ローカル変数にポインタを代入
//		CollisionObject* collision = GetCharaConCollision();
//		float* frameCount = &m_invincibleFrameCount;
//		//点滅間隔用変数
//		float intervalBlinkingFrame = 0.0f;
//		const float oneFrame = GameInfo::ONE_FRAME;
//		//キャラコンコリジョンを無効化
//		collision->Deactivate();
//
//
//		//無敵時間が終了するまでループ
//		while (*frameCount < LifeInfo::INVINCIBLE_FRAME) {
//
//			//フレーム待機
//			//だんだん遅く点滅させる
//			//intervalBlinkingFrame += GameInfo::ONE_FRAME;
//			//float interval = intervalBlinkingFrame;
//			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(*frameCount * 1000.0f)));
//			//無敵時間をカウント
//			*frameCount += oneFrame;
//			
//			if (m_isDraw) {
//				m_isDraw = false;
//			}
//			else {
//				m_isDraw = true;
//			}
//		}
//
//
//		//無敵状態解除
//		m_isInvincible = false;
//		m_isDraw = true;
//		//キャラコンコリジョンを有効化
//		collision->Activate();
//		//無敵時間カウントリセット
//		*frameCount = 0.0f;
//
//		});
//
//	controlInvincibleFrameCountThread.detach();
//}
//
//
//void Player::UpdateCharaPos() {
//	//移動していなければ処理しない
//	if (!IsMove()) {
//		return;
//	}
//	//キャラコンに速度を加算して位置を更新
//	m_position = m_playerCharaCon.Execute(m_moveSpeed, GameInfo::ONE_FRAME);
//	//モデルの位置を更新
//	m_playerModelRender->SetPosition(m_position);
//}
//
//
//void Player::UpdateAtkCollisionInfo() {
//	CollisionObject* collision = m_playerAtkCollision;
//	if (!collision) {
//		return;
//	}
//	collision->SetPosition(m_position);
//	collision->SetRotation(m_rotation);
//	collision->Update();
//}
//
//
//void Player::UpdateCharaConCollisionInfo() {
//	CollisionObject* collision = m_playerCharaConCollision;
//	if (!collision) {
//		return;
//	}
//	//キャラコンのポジションに反映させる
//	Vector3 pos = m_playerCharaCon.GetPosition();
//	pos.y += CHARA_CON.y * (3.0f / 4.0f);
//
//	collision->SetPosition(pos);
//	collision->SetRotation(m_rotation);
//	collision->Update();
//}
//
//
//void Player::SetFlagIsKillEnemy(const bool isKill) {
//	m_isKillEnemy = isKill;
//}
//
//
//void Player::ReducePlayerLife() {
//	if (!m_isActive) {
//		m_playerLife--;
//	}	
//	if (m_playerLife <= 0) {
//		m_playerLife = 0;
//		DeleteGO(this);
//	}
//	m_isInvincible = true;
//
//	Invincible();
//}
//
//
//
///////////////////////////////////
//// ゲッター関数
///////////////////////////////////
//
//
//CollisionObject* Player::GetAtkCollision()const {
//	return m_playerAtkCollision;
//}
//
//
//CollisionObject* Player::GetCharaConCollision()const {
//	return m_playerCharaConCollision;
//}
//
//
//inline const bool Player::IsKillEnemy()const {
//	return m_isKillEnemy;
//}
//
//
//const bool Player::IsInvincible()const {
//	return m_isInvincible;
//}
//
//
//const Vector3& Player::GetPosition()const {
//	return m_position;
//}
//
//
//float Player::Gravity() {
//	m_flyingTime += GameInfo::ONE_FRAME * 5.0f;
//	return MoveInfo::GRAVITY * m_flyingTime;
//}
//
//
//bool Player::CanJump() {
//	//地面についていなかったら
//	if (!m_playerCharaCon.IsOnGround()) {
//		//重力を発生させる
//		m_moveSpeed.y += Gravity();		
//		return false;
//	}
//	//地面についているのでタイマーをリセット
//	m_flyingTime = 0.0f;
//	m_moveSpeed.y = 0.0f;
//	return true;
//}
//
//
//bool Player::MeasureNextJumpFrameCount() {
//	if (m_standingTime <= MoveInfo::CAN_NEXT_JUMP_FRAME) {
//		m_standingTime += GameInfo::ONE_FRAME;
//		return false;
//	}
//	//タイマーをリセット
//	m_standingTime = 0.0f;
//	return true;
//}
//
//
//bool Player::CanNextPowerJump() {
//	//空中にいるときにジャンプボタンを押したら
//	if (!CanJump()) {
//		if (g_pad[0]->IsTrigger(enButtonB)) {
//			m_jumpState = enJumpPower_First;
//		}
//		//ジャンプさせない
//		return false;
//	}
//	//地面についている時間をカウント
//	if (MeasureNextJumpFrameCount()) {
//		//ジャンプパワーを戻す
//		m_jumpState = enJumpPower_First;
//		//ジャンプさせない
//		return false;
//	}
//	return true;
//}
//
//
//bool Player::IsMove() {
//	for (int i = 0; i < 3; i++) {
//		if (m_moveSpeed.v[i] != 0.0f) {
//			return true;
//		}
//	}
//	return false;
//}
//
//
//bool Player::IsRun() {
//	if (!IsMove()) {
//		return false;
//	}
//	if (!g_pad[0]->IsPress(enButtonA)) {
//		return false;
//	}
//	return true;
//}
//
//
//bool Player::IsStick(const Vector2& stick) {
//	if (stick.x != 0.0f) {
//		return true;
//	}
//	if (stick.y != 0.0f) {
//		return true;
//	}
//	return false;
//}


namespace {
	//ファイルの場所
	const std::string PLAYER_FILEPATH = "Assets/animData/";
	//拡張子
	const std::string PLAYER_EXTENSTION = ".tka";

	struct PlayerAnimInfo{
		//ファイル名
		std::string fileName;

		//ファイルパスを取得
		std::string GetModelFullPath()const {
			return PLAYER_FILEPATH + fileName + PLAYER_EXTENSTION;
		}
	};


	const PlayerAnimInfo PlayerInfo[enPlayerState_Num] = {
		"idle",	"walk" , "run" , "jump"
	};
	const char* UNITY_MODEL = "Assets/modelData/unityChan.tkm";

	const Vector2 CHARA_CON = { 15.0f, 65.0f };
	const Vector3 START_POS = { 100.0f, 0.0f, 100.0f };

	
	
}

void Player::SetPlayerModel() {

}