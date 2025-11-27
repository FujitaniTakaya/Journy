#include "stdafx.h"
#include "NormalEnemy.h"
#include "Player.h"


namespace nsNormalEnemy {
	const Vector2 CHAR_CON_SCL = { 15.0f, 60.0f };

	const ModelInfo MODEL_INFO = {
		"Assets/modelData/enemy/normalEnemy/normalEnemy.tkm"
	};


	const int ANIM_NUM = 1;
	const AnimInfo ANIM_INFO = {
		"Assets/modelData/enemy/normalEnemy/walk.tka",1.3f,true
	};
}


NormalEnemy::NormalEnemy() {
}


NormalEnemy::~NormalEnemy() {
}


void NormalEnemy::LoadAnimationClips() {
	//アニメーションの初期化
	m_animationClips.reserve(nsNormalEnemy::ANIM_NUM);
	for (auto& clip : m_animationClips) {
		clip =  new AnimationClip;
		const AnimInfo& anim = nsNormalEnemy::ANIM_INFO;
		clip->Load(anim.GetAnimFullPath().c_str());
		clip->SetLoopFlag(anim.IsLoop());
	}
}


void NormalEnemy::SetUpModel() {
	const ModelInfo& modelInfo = nsNormalEnemy::MODEL_INFO;
	m_modelRender.Init(modelInfo.GetModelFullPath().c_str(), m_animationClips.front(), nsNormalEnemy::ANIM_NUM, enModelUpAxisY);
	m_firstPos = m_transform.position;
	Vector2 charConScl = nsNormalEnemy::CHAR_CON_SCL;
	m_characterController.Init(charConScl.x, charConScl.y, m_transform.position);
}


bool NormalEnemy::Start() {
	m_normalEnemyStatus = new NormalEnemyStatus;
	//m_status = m_normalEnemyStatus;
	//InitializeCharacter();
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
		ChasePlayer(m_normalEnemyStatus);
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
	if (dot < m_normalEnemyStatus->GetFrontAngle()) {
		//右回りか左回りか判定する
		Vector3 cross = Cross(front, dif);
		cross.Normalize();
		//0.0fより小さければ右回転
		if (cross.y < 0.0f) {
			//右回転
			m_transform.rotation.AddRotationDegY(-1 * m_normalEnemyStatus->GetRotateSpeed());
		}
		//0.0fより大きければ左回転
		else if (cross.y > 0.0f) {
			//左回転
			m_transform.rotation.AddRotationDegY(m_normalEnemyStatus->GetRotateSpeed());
		}
		return;
	}

	const Vector3 speed = dif * m_normalEnemyStatus->GetMoveSpeed(EnMoveState::enMoveState_Walk);
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
	float speed = m_normalEnemyStatus->GetMoveSpeed(EnMoveState::enMoveState_Walk);
	if (dif.Length() >= speed * 1.2) return false;
	return true;
}