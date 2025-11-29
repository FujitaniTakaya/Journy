#include "stdafx.h"
#include "NormalEnemy.h"
#include "Player.h"


namespace  {
	const Vector2 CHAR_CON_SCL = { 15.0f, 60.0f };
	

	const std::string CHAR_TYPE = "enemy/normalEnemy/";
	
	
	const std::string ANIM_FILE_NAME = "walk";
	constexpr int ANIM_NUM = 1;
	constexpr bool ANIM_LOOP_FLAG = true;
	constexpr float ANIM_SPEED[EnNormalEnemyState::enNormalEnemyState_Num] = {
		1.3f, 1.6f
	};

	const std::string MODEL_FILE_NAME = "normalEnemy";
}


NormalEnemy::NormalEnemy() {
}


NormalEnemy::~NormalEnemy() {
}


void NormalEnemy::LoadAnimationClips() {
	//m_animationClips.resize(ANIM_NUM);
	//m_animationClips[0].Load("Assets/modelData/enemy/normalEnemy/walk.tka");
	//m_animationClips[0].SetLoopFlag(true);

	//m_animationClips.resize(static_cast<uint8_t>(ANIM_NUM));
	//for (int i = 0; i < ANIM_NUM; i++) {
	//	auto* animationClip = new AnimationClip();
	//	animationClip->Load(nsAnim::GetFullPath(CHAR_TYPE, ANIM_FILE_NAME).c_str());
	//	animationClip->SetLoopFlag(ANIM_LOOP_FLAG);
	//	m_animationClips[i] = animationClip;
	//}

	m_animationClip.Load(nsAnim::GetFullPath(CHAR_TYPE, ANIM_FILE_NAME).c_str());
	m_animationClip.SetLoopFlag(true);
}


void NormalEnemy::SetUpModel() {

	//m_modelRender.Init(
	//	nsModel::GetFullPath(CHAR_TYPE, MODEL_FILE_NAME).c_str(),
	//	*m_animationClips.data(),
	//	ANIM_NUM, enModelUpAxisZ);
	//m_firstPos = m_transform.position;
	//m_characterController.Init(CHAR_CON_SCL.x, CHAR_CON_SCL.y, m_transform.position);
	m_modelRender.Init(
		nsModel::GetFullPath(CHAR_TYPE, MODEL_FILE_NAME).c_str(),
		&m_animationClip,
		ANIM_NUM, enModelUpAxisZ);
	m_firstPos = m_transform.position;
	m_characterController.Init(CHAR_CON_SCL.x, CHAR_CON_SCL.y, m_transform.position);
}


bool NormalEnemy::Start() {
	LoadAnimationClips();
	SetUpModel();
	GetOtherClassInfo();
	DecideToMovePos();
	
	if (!m_player) {
		return false;
	}
	return true;
}


void NormalEnemy::Update() {
	if (!IsStart()) return;

	//DrawVectorFront();
	//DrawVectorToMovePos();

	Move();
	Death();

	m_moveSpeed.y = 0.0f;
	m_modelRender.PlayAnimation(0);
	UpdateTRSInfo();


}


void NormalEnemy::Render(RenderContext& rc) {
	if (GetModelRender()) m_modelRender.Draw(rc);
}


void NormalEnemy::Move() {
	if (IsFoundPlayer()) {
		ChasePlayer(&m_normalEnemyStatus);
		return;
	}
	RandomWalkAround();
	//m_moveSpeed.y = 0.0f;
}


void NormalEnemy::RandomWait(std::atomic<bool>& waitFlag) {
	//ランダムな時間待機
	//300ms～3300ms
	int waitTime = rand() % 3001 + 300;
	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
	waitFlag = false;
}


void NormalEnemy::RandomWalkAround() {
	//目的地に到着していたら
	if (IsBeingToMovePos()) {
		//新しい目的地を決定
		DecideToMovePos();

		//待機開始
		m_isWait = true;
		std::thread waitThread([this]() {
			this->RandomWait(m_isWait);
			});
		//待機処理をデタッチして別スレッドで実行
		waitThread.detach();
	}

	//待機中だったら処理しない
	if (IsWait()) {
		return;
	}


	//移動速度をリセット(加速させないため)
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 dif = m_toMovePos - m_transform.position;
	dif.Normalize();
	Vector3 front = Vector3::AxisZ;
	front.Normalize();
	m_transform.rotation.Apply(front);
	//内積を求める
	float dot = Dot(front, dif);

	//ほぼ同じ方向を向いていれば回転しない
	if (dot < m_normalEnemyStatus.GetFrontAngle()) {
		//右回りか左回りか判定する
		Vector3 cross = Cross(front, dif);
		cross.Normalize();
		//0.0fより小さければ右回転
		if (cross.y < 0.0f) {
			//右回転
			m_transform.rotation.AddRotationDegY(-1 * m_normalEnemyStatus.GetRotateSpeed());
		}
		//0.0fより大きければ左回転
		else if (cross.y > 0.0f) {
			//左回転
			m_transform.rotation.AddRotationDegY(m_normalEnemyStatus.GetRotateSpeed());
		}
		return;
	}

	const Vector3 speed = dif * m_normalEnemyStatus.GetMoveSpeed(EnMoveState::enMoveState_Walk);
	m_moveSpeed += speed;
}



void NormalEnemy::DecideToMovePos() {
	m_toMovePos.x = rand() % 601 - 300;
	m_toMovePos.z = rand() % 601 - 300;
	m_toMovePos += m_firstPos;
	m_toMovePos.y = m_firstPos.y;
}


bool NormalEnemy::IsBeingToMovePos()const {
	Vector3 dif = m_toMovePos - m_transform.position;
	float speed = m_normalEnemyStatus.GetMoveSpeed(EnMoveState::enMoveState_Walk);
	if (dif.Length() >= speed * 1.2) return false;
	return true;
}