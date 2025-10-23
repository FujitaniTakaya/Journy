#include "stdafx.h"
#include "Enemy.h"
#include "Text.h"
#include <time.h>
#include <thread>



namespace {
	//�t�@�C���̏ꏊ
	std::string FILE_PATH = "Assets/enemy/";
	//�g���q
	std::string FILE_EXTENSTION = ".tkm";

	struct EnemyInfo {
		//�t�H���_��
		std::string folderName = "folderName";
		//�t�@�C����
		std::string fileName = "fileName";

		Vector3 modelScale;
		Vector2 charConScale;

		//�t�@�C���p�X���擾
		std::string GetModelFullPath() {
			return FILE_PATH + folderName + fileName + FILE_EXTENSTION;
		}
	};

	EnemyInfo EnemiesModel[Enemy::enEnemy_Num] = {
		{"normalEnemy/", "NormalEnemy", {3.0f, 3.0f, 3.5f}, {25.0f, 20.0f}},
		{ "gimmickEnemy/","GimmickEnemy", {2.8f, 2.0f, 2.8f}, {25.0f, 30.0f}},
		{ "bossEnemy/","BossEnemy" , {1.0f, 1.2f, 1.0f}, {50.0f, 45.0f}}
	};

	float WALK_SPEED = 40.0f;
}


//�m�[�}���G�l�~�[�̏�����
bool Normal::Start() {
	SetEnemyModel(enEnemy_Normal);
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


//�M�~�b�N�G�l�~�[�̏�����
bool Gimmick::Start() {
	SetEnemyModel(enEnemy_Gimmick);
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


//�{�X�G�l�~�[�̏�����
bool Boss::Start() {
	SetEnemyModel(enEnemy_Boss);
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


void Enemy::Update() {
	RandomWalk();
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
void Enemy::SetEnemyModel(int enemyNum) {
	//�����_�����m��
	srand(time(nullptr));

	//�����o�ϐ��֑��
	ModelRender* model = new ModelRender;
	std::string filePath = EnemiesModel[enemyNum].GetModelFullPath();
	Vector3 scale = EnemiesModel[enemyNum].modelScale;
	Vector2 collisionScl = EnemiesModel[enemyNum].charConScale;	

	//���f���ƃR���W������������
	model->Init(filePath.c_str());
	model->SetScale(scale);
	model->SetPosition(m_enemyPos);

	float rotation = rand() % 360;

	m_enemyRotate.SetRotationDegY(rotation);
	model->SetRotation(m_enemyRotate);
	
	m_enemyModelRender = model;
	m_enemyModelRender->Update();
	m_enemyCharaCon.Init(collisionScl.x, collisionScl.y, m_enemyPos);
}


//���f�����󂩂ǂ�������
bool Enemy::IsModel(ModelRender* model) {
	if (!model) {
		return false;
	}
	return true;
}


void Enemy::DecideToMovePos() {
	m_toMovePos.x = rand() % 401 - 100;
	m_toMovePos.z = rand() % 401 - 100;
	m_toMovePos += m_firstEnemyPos;
	m_toMovePos.y = 0.0f;

	m_isEndWaitTime = false;
}


bool Enemy::IsBeingMovePos() {
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
	m_isEndWaitTime = true;
	if (IsBeingMovePos()) {		
		DecideToMovePos();
		std::thread waitThread([this]() {
			this->RandomWait(this->m_isEndWaitTime);
			});
		//std::thread waitThread(RandomWait, canMove);
		waitThread.detach();

	}
	
	if (!m_isEndWaitTime) {
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


void Enemy::RandomWait(bool& moveFlag) {
	int waitTime = rand() % 3000 + 300;
	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
	moveFlag = true;
}





