#include "stdafx.h"
#include "Player.h"

namespace {
	//�t�@�C���̏ꏊ
	std::string PLAYER_FILEPATH = "Assets/animData/";
	//�g���q
	std::string PLAYER_EXTENSTION = ".tka";

	struct PlayerAnimInfo{
		//�t�@�C����
		std::string fileName;

		//�t�@�C���p�X���擾
		std::string GetFullPath()const {
			return PLAYER_FILEPATH + fileName + PLAYER_EXTENSTION;
		}
	};


	PlayerAnimInfo PlayerInfo[enPlayerState_Num] = {
		"idle",	"walk" , "run" , "jump"
	};
	const char* UNITY_MODEL = "Assets/modelData/unityChan.tkm";

	float ONE_FRAME = 1.0f / 60.0f;

	Vector2 CHARA_CON = { 25.0f, 75.0f };


	float WALK_SPEED = 200.0f;							//�����X�s�[�h
	float DASH_SPEED = WALK_SPEED * 2;					//����X�s�[�h

	float CAN_NEXT_JUMP_FRAME = 0.1f;					//���̒i�̃W�����v�ɐ؂�ւ����܂ł̗P�\����

	float JUMP_POWER[enJumpPower_Num] = {				//�W�����v�p���[�̔z��
		200.0f, 220.0f, 300.0f
	};


	float MAX_FLYING_TIME = 0.5f;						//�d�͉����̍ő�t���[����
	float GRAVITY = -9.8f;								//�d�͉����x

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
		m_playerAnimClips[i].Load(PlayerInfo[i].GetFullPath().c_str());
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

	m_playerCharaCon.Init(CHARA_CON.x, CHARA_CON.y, m_position);

	m_playerModelRender->SetPosition(Vector3::Zero);

	m_playerModelRender->Update();
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
	//x,z�̈ړ����x��������
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	
	
	//���X�e�B�b�N�̓��͗ʂ��擾
	Vector2 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�X�e�B�b�N�̓��͂��Ȃ���Ή��̏��������Ȃ�
	if (!IsStick(stickL)) {
		return;
	}
	

	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	forward.y = 0.0f;
	right.y = 0.0f;

	right *= stickL.x * WALK_SPEED;
	forward *= stickL.y * WALK_SPEED;

	m_moveSpeed += right + forward;


	Rotate();

	m_position = m_playerCharaCon.Execute(m_moveSpeed, ONE_FRAME);
	m_playerModelRender->SetPosition(m_position);	
}


//�X�e�[�g�Ǘ�
//���̃X�e�[�g�ɓ��Ă͂܂�A�j���[�V�������Đ�����
void Player::ManagePlayerState() {
	m_playerState = enPlayerState_Idle;

	if (IsMove()) {
		m_playerState = enPlayerState_Walk;
	}
	if (IsRun()) {
		m_playerState = enPlayerState_Run;
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



//�d�͂�Ԃ�
float Player::Gravity() {
	m_flyingTime += g_gameTime->GetFrameDeltaTime();
	return GRAVITY * m_flyingTime;
}


//�W�����v�ł��邩�ǂ�������
//���̎��̏d�͂�����
bool Player::CanJump() {
	//�n�ʂɂ��Ă��Ȃ�������
	if (!m_playerCharaCon.IsOnGround()) {
		//�d�͂𔭐�������
		m_moveSpeed.y += Gravity();
		return false;
	}
	m_flyingTime = 0.0f;
	m_moveSpeed.y = 0.0f;
	return true;
}


//�K�莞�Ԃ��������ǂ����𔻒�
bool Player::MeasureNextJumpFrameCount() {
	if (m_standingTime <= CAN_NEXT_JUMP_FRAME) {
		return false;
	}
	//�^�C�}�[�����Z�b�g
	m_standingTime = 0.0f;
	return true;
}


bool Player::CanNextJump() {
	//�󒆂ɂ���Ƃ��ɃW�����v�{�^������������
	if (!CanJump()) {
		if (g_pad[0]->IsTrigger(enButtonB)) {
			m_jumpState = enJumpPower_First;
		}
		//�W�����v�����Ȃ�
		return false;
	}
	//�n�ʂɂ��Ă��鎞�Ԃ��J�E���g
	if (MeasureNextJumpFrameCount()) {
		//�W�����v�p���[��߂�
		m_jumpState = enJumpPower_First;
		//�W�����v�����Ȃ�
		return false;
	}

	
	return true;
}


void Player::Jump() {
	//�W�����v�ł��邩����
	if (!CanJump()) {
		return;
	}

	if (m_jumpState != enJumpPower_Third) {
		if (!CanNextJump()) {
			return;
		}
	}

	//B�{�^����������Ă��邩����
	if (!g_pad[0]->IsTrigger(enButtonB)) {
		return;
	}	
	m_moveSpeed.y += JUMP_POWER[m_jumpState];
	m_jumpState = static_cast<EnJumpPower>((m_jumpState + 1) % enJumpPower_Num);
}