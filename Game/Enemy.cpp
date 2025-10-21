#include "stdafx.h"
#include "Enemy.h"

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
		std::string GetFullPath() {
			return FILE_PATH + folderName +fileName + FILE_EXTENSTION;
		}
	};

	EnemyInfo EnemiesModel[Enemy::enEnemy_Num] = {
		{"normalEnemy/", "NormalEnemy", {3.0f, 3.0f, 3.5f}, {25.0f, 20.0f}},
		{ "gimmickEnemy/","GimmickEnemy", {2.8f, 2.0f, 2.8f}, {25.0f, 30.0f}},
		{ "bossEnemy/","BossEnemy" , {1.0f, 1.2f, 1.0f}, {50.0f, 45.0f}}
	};
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


//�G�l�~�[��`��
void Enemy::Render(RenderContext& rc) {
	if (!IsModel(m_enemyModelRender)) {
		return;
	}
	m_enemyModelRender->Draw(rc);
}


//�G�l�~�[�̃��f��������������
void Enemy::SetEnemyModel(int enemyNum) {
	//�����o�ϐ��֑��
	ModelRender* model = new ModelRender;
	std::string filePath = EnemiesModel[enemyNum].GetFullPath();
	Vector3 scale = EnemiesModel[enemyNum].modelScale;
	Vector2 collisionScl = EnemiesModel[enemyNum].charConScale;	

	//���f���ƃR���W������������
	model->Init(filePath.c_str());
	model->SetScale(scale);
	model->SetPosition(m_enemyPos);
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


void Enemy::RandomWalk() {

}


