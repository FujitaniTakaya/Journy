#include "stdafx.h"
#include "Enemy.h"
#include "Text.h"
#include <random>
#include <thread>



namespace {
	//�t�@�C���̏ꏊ
	const std::string FILE_PATH = "Assets/enemy/";
	//�g���q
	const std::string FILE_EXTENSTION = ".tkm";

	struct EnemyInfo {
		//�t�H���_��
		std::string folderName = "folderName";
		//�t�@�C����
		std::string fileName = "fileName";

		Vector3 modelScale;
		Vector2 charConScale;

		//�t�@�C���p�X���擾
		const std::string GetModelFullPath()const {
			return FILE_PATH + folderName + fileName + FILE_EXTENSTION;
		}
	};

	const EnemyInfo EnemiesModel[static_cast<int>(Enemy::EnEnemy::enEnemy_Num)] = {
		{"normalEnemy/", "NormalEnemy", {3.0f, 3.0f, 3.5f}, {25.0f, 20.0f}},
		{ "gimmickEnemy/","GimmickEnemy", {2.8f, 2.0f, 2.8f}, {25.0f, 30.0f}},
		{ "bossEnemy/","BossEnemy" , {1.0f, 1.2f, 1.0f}, {50.0f, 45.0f}}
	};

	const float WALK_SPEED = 40.0f;
}


//�m�[�}���G�l�~�[�̏�����
bool Normal::Start() {
	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Normal));
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}

	

	return true;
}


//�M�~�b�N�G�l�~�[�̏�����
bool Gimmick::Start() {
	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Gimmick));
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


//�{�X�G�l�~�[�̏�����
bool Boss::Start() {
	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Boss));
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


void Enemy::Update() {
	if (!IsStart()) {
		return;
	}
	RandomWalk();

	Vector3 front = Vector3::AxisZ;

	m_enemyRotate.Apply(front);
	/*front.x = 1.0f;
	front.y = 1.0f;*/
	//front.z = m_enemyRotate.z * 1;
	front.Normalize();
	front *= 200.0f;
	Vector3 origin = m_enemyPos;
	origin.y += 80.0f;
	g_k2Engine->DrawVector(front, origin);
	g_k2Engine->DrawVector(Vector3::AxisY*50.0f, Vector3::Zero);

	
	g_k2Engine->SetDrawVectorEnable();

}


//�G�l�~�[��`��
void Enemy::Render(RenderContext& rc) {
	if (!IsModel(m_enemyModelRender)) {
		return;
	}
	m_enemyModelRender->Draw(rc);
}


void Enemy::UpdateEnemyPos() {
	m_enemyPos = m_enemyCharaCon.Execute(m_moveSpeed, ONE_FRAME);
	m_enemyModelRender->SetPosition(m_enemyPos);
	m_enemyModelRender->Update();
}


//�G�l�~�[�̃��f��������������
void Enemy::SetEnemyModel(const int enemyNum) {
	//�����o�ϐ��֑��
	ModelRender* model = new ModelRender;
	std::string filePath = EnemiesModel[enemyNum].GetModelFullPath();
	Vector3 scale = EnemiesModel[enemyNum].modelScale;
	Vector2 collisionScl = EnemiesModel[enemyNum].charConScale;	
	float rot = 0.0f;
	rot = rand() % 360;
	m_enemyRotate.SetRotationDegY(rot);
	//���f���ƃR���W������������
	model->Init(filePath.c_str());
	model->SetTRS(m_enemyPos, m_enemyRotate, scale);
	model->SetScale(scale);
	model->SetPosition(m_enemyPos);

	//float rotation = rand() % 360;
	//m_enemyRotate.SetRotationDegY(rotation);
	//model->SetRotation(m_enemyRotate);
	
	m_enemyModelRender = model;
	m_enemyModelRender->Update();
	m_enemyCharaCon.Init(collisionScl.x, collisionScl.y, m_enemyPos);
}


//���f�����󂩂ǂ�������
bool Enemy::IsModel(const ModelRender* model) {
	if (!model) {
		return false;
	}
	return true;
}





void Enemy::StartWaitTime(std::atomic<bool>& waitFlag) {
	waitFlag = true;
}


void Enemy::DecideToMovePos() {
	m_toMovePos.x = rand() % 401 - 200;
	m_toMovePos.z = rand() % 401 - 200;
	m_toMovePos += m_firstEnemyPos;
	m_toMovePos.y = 0.0f;
}


bool Enemy::IsBeingMovePos()const {
	Vector3 dif = m_toMovePos - m_enemyPos;
	
	if (dif.Length() >= WALK_SPEED * 1.2) {
		return false;
	}	
	return true;
}



bool Enemy::IsRotateMovePos() {
	
	return true;
}



//�G�l�~�[�̃����_���E�H�[�N
void Enemy::RandomWalk() {
	if (IsBeingMovePos()) {		
		DecideToMovePos();
		StartWaitTime(m_isWait);
		std::thread waitThread([this]() {
			this->RandomWait(this->m_isWait);
			});
		//std::thread waitThread(RandomWait, canMove);
		waitThread.detach();
	}

	//�ҋ@����������
	if (IsWait()) {
		return;
	}

	Vector3 dif = m_toMovePos - m_enemyPos;
	dif.Normalize();
	
	//�ړ����x�����Z�b�g(���������Ȃ�����)
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += dif * WALK_SPEED;

	UpdateEnemyPos();
}


void Enemy::RandomWait(std::atomic<bool>& waitFlag) {
	static std::mt19937 rang(std::random_device{}());
	std::uniform_int_distribution<int> dist(300, 3299);

	int waitTime = dist(rang);
	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
	waitFlag = false;
}


const bool Enemy::IsWait()const {
	return m_isWait;
}


const Vector3* Enemy::GetPosition()const {
	return &m_enemyPos;
}












