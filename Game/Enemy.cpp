#include "stdafx.h"
#include "Enemy.h"

namespace {
	//ファイルの場所
	std::string FILE_PATH = "Assets/enemy/";
	//拡張子
	std::string FILE_EXTENSTION = ".tkm";

	struct EnemyInfo {
		//フォルダ名
		std::string folderName = "folderName";
		//ファイル名
		std::string fileName = "fileName";

		Vector3 modelScale;
		Vector2 charConScale;

		//ファイルパスを取得
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


//ノーマルエネミーの初期化
bool Normal::Start() {
	SetEnemyModel(enEnemy_Normal);
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


//ギミックエネミーの初期化
bool Gimmick::Start() {
	SetEnemyModel(enEnemy_Gimmick);
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


//ボスエネミーの初期化
bool Boss::Start() {
	SetEnemyModel(enEnemy_Boss);
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}


//エネミーを描画
void Enemy::Render(RenderContext& rc) {
	if (!IsModel(m_enemyModelRender)) {
		return;
	}
	m_enemyModelRender->Draw(rc);
}


//エネミーのモデルを初期化する
void Enemy::SetEnemyModel(int enemyNum) {
	//メンバ変数へ代入
	ModelRender* model = new ModelRender;
	std::string filePath = EnemiesModel[enemyNum].GetFullPath();
	Vector3 scale = EnemiesModel[enemyNum].modelScale;
	Vector2 collisionScl = EnemiesModel[enemyNum].charConScale;	

	//モデルとコリジョンを初期化
	model->Init(filePath.c_str());
	model->SetScale(scale);
	model->SetPosition(m_enemyPos);
	m_enemyModelRender = model;
	m_enemyModelRender->Update();
	m_enemyCharaCon.Init(collisionScl.x, collisionScl.y, m_enemyPos);
}


//モデルが空かどうか判定
bool Enemy::IsModel(ModelRender* model) {
	if (!model) {
		return false;
	}
	return true;
}


void Enemy::RandomWalk() {

}


