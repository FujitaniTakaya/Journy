#include "stdafx.h"
#include "Player.h"

namespace {
	//ファイルの場所
	std::string PLAYER_FILEPATH = "Assets/animData/";
	//拡張子
	std::string PLAYER_EXTENSTION = ".tka";

	struct PlayerAnimInfo{
		//ファイル名
		std::string fileName;

		//ファイルパスを取得
		std::string GetModelFullPath()const {
			return PLAYER_FILEPATH + fileName + PLAYER_EXTENSTION;
		}
	};


	PlayerAnimInfo PlayerInfo[enPlayerState_Num] = {
		"idle",	"walk" , "run" , "jump"
	};
	const char* UNITY_MODEL = "Assets/modelData/unityChan.tkm";

	Vector2 CHARA_CON = { 25.0f, 75.0f };


	namespace MoveInfo {
		float MOVE_SPEED[Player::enPlayerMoveState_Num] = {
		200.0f, 400.0f
		};

		float CAN_NEXT_JUMP_FRAME = 0.2f;					//次の段のジャンプに切り替えれるまでの猶予時間

		float JUMP_POWER[Player::enJumpPower_Num] = {				//ジャンプパワーの配列
			200.0f, 400.0f, 600.0f
		};


		float MAX_FLYING_TIME = 0.5f;						//重力加速の最大フレーム数
		float GRAVITY = -9.8f;								//重力加速度
	}

	

}


Player::Player() {
	SetPlayerModel();
}


Player::~Player() {
	m_playerModelRender = nullptr;
}

void Player::Update() {
	Move();
	Jump();
	ManagePlayerState();
	CharaMove();
	m_playerModelRender->Update();
}


void Player::Render(RenderContext& rc) {
	if (!m_playerModelRender) {
		return;
	}
	m_playerModelRender->Draw(rc);
}


void Player::SetPlayerModel() {
	for (int i = 0; i < enPlayerState_Num; i++) {
		m_playerAnimClips[i].Load(PlayerInfo[i].GetModelFullPath().c_str());
		if (i != enPlayerState_Jump) {
			m_playerAnimClips[i].SetLoopFlag(true);
			continue;
		}
		else {
			m_playerAnimClips[i].SetLoopFlag(false);
		}		
	}

	m_playerModelRender = new ModelRender;
	m_playerModelRender->Init(UNITY_MODEL, m_playerAnimClips, enPlayerState_Num, enModelUpAxisY);
	m_playerModelRender->SetPosition(Vector3::Zero);
	m_playerModelRender->Update();
	m_playerCharaCon.Init(CHARA_CON.x, CHARA_CON.y, m_position);
	
}



bool Player::IsMove() {
	for (int i = 0; i < 3; i++) {
		if (m_moveSpeed.v[i] != 0.0f) {
			return true;
		}
	}
	return false;
}


bool Player::IsRun() {
	if (!IsMove()) {
		return false;
	}
	if (!g_pad[0]->IsPress(enButtonA)) {
		return false;
	}
	return true;
}


bool Player::IsStick(const Vector2& stick) {
	if (stick.x != 0.0f) {
		return true;
	}
	if (stick.y != 0.0f) {
		return true;
	}
	return false;
}


void Player::Move() {
	//x,zの移動速度を初期化
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	
	//左スティックの入力量を取得
	Vector2 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//スティックの入力がなければ下の処理をしない
	if (!IsStick(stickL)) {
		return;
	}

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	float speed = MoveInfo::MOVE_SPEED[m_moveState];

	right *= stickL.x * speed;
	forward *= stickL.y * speed;
	m_moveSpeed += right + forward;

	Rotate();
}


//ステート管理
//そのステートに当てはまるアニメーションを再生する
void Player::ManagePlayerState() {
	m_playerState = enPlayerState_Idle;
	
	if (IsMove()) {
		m_playerState = enPlayerState_Walk;
		m_moveState = enPlayerMoveState_Walk;
	}
	if (IsRun()) {
		m_playerState = enPlayerState_Run;
		m_moveState = enPlayerMoveState_Run;
	}
	if (!m_playerCharaCon.IsOnGround()) {
		m_playerState = enPlayerState_Jump;
	}
	
	m_playerModelRender->PlayAnimation(m_playerState);
}


void Player::Rotate() {
	m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	m_playerModelRender->SetRotation(m_rotation);
}



//重力を返す
float Player::Gravity() {
	m_flyingTime += ONE_FRAME * 5.0f;
	return MoveInfo::GRAVITY * m_flyingTime;
}


//ジャンプできるかどうか判定
//その時の重力も制御
bool Player::CanJump() {
	//地面についていなかったら
	if (!m_playerCharaCon.IsOnGround()) {
		//重力を発生させる
		m_moveSpeed.y += Gravity();
		return false;
	}
	m_flyingTime = 0.0f;
	m_moveSpeed.y = 0.0f;
	return true;
}


//規定時間たったかどうかを判定
bool Player::MeasureNextJumpFrameCount() {
	if (m_standingTime <= MoveInfo::CAN_NEXT_JUMP_FRAME) {
		m_standingTime += ONE_FRAME;
		return false;
	}
	//タイマーをリセット
	m_standingTime = 0.0f;
	return true;
}


bool Player::CanNextJump() {
	//空中にいるときにジャンプボタンを押したら
	if (!CanJump()) {
		if (g_pad[0]->IsTrigger(enButtonB)) {
			m_jumpState = enJumpPower_First;
		}
		//ジャンプさせない
		return false;
	}
	//地面についている時間をカウント
	if (MeasureNextJumpFrameCount()) {
		//ジャンプパワーを戻す
		m_jumpState = enJumpPower_First;
		//ジャンプさせない
		return false;
	}

	
	return true;
}


void Player::Jump() {
	if (!CanJump()) {
		return;
	}
	if (m_canNextJump) {
		if (MeasureNextJumpFrameCount()) {
			m_jumpState = enJumpPower_First;
			m_canNextJump = false;
			return;
		}
	}
	if (!g_pad[0]->IsTrigger(enButtonB)) {
		return;
	}
	float jumpPower = MoveInfo::JUMP_POWER[m_jumpState];
	m_moveSpeed.y += jumpPower;

	m_jumpState = static_cast<EnJumpPower>((m_jumpState + 1) % enJumpPower_Num);
	m_canNextJump = true;
	if (!(m_jumpState == enJumpPower_First)) {
		return;
	}
	m_canNextJump = false;
}


void Player::CharaMove() {
	if (!IsMove()) {
		return;
	}
	m_position = m_playerCharaCon.Execute(m_moveSpeed, ONE_FRAME);
	m_playerModelRender->SetPosition(m_position);
}