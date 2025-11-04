#include "stdafx.h"
#include "Enemy.h"
#include <random>
#include <thread>



namespace {
	//ファイルの場所
	const std::string FILE_PATH = "Assets/enemy/";
	//拡張子
	const std::string FILE_EXTENSTION = ".tkm";

	struct EnemyInfo {
		//フォルダ名
		std::string folderName = "folderName";
		//ファイル名
		std::string fileName = "fileName";
		//モデルのスケール
		Vector3 modelScale;
		//キャラコンのスケール
		Vector2 charConScale;

		/// <summary>
		/// エネミーモデルのファイルパスを取得
		/// </summary>
		const std::string GetModelFullPath()const {
			return FILE_PATH + folderName + fileName + FILE_EXTENSTION;
		}
	};

	const EnemyInfo EnemiesModel[static_cast<int>(EnEnemy::enEnemy_Num)] = {
		{"normalEnemy/", "NormalEnemy", {3.0f, 3.0f, 3.5f}, {25.0f, 20.0f}},
		{ "gimmickEnemy/","GimmickEnemy", {2.8f, 2.0f, 2.8f}, {25.0f, 30.0f}},
		{ "bossEnemy/","BossEnemy" , {1.0f, 1.2f, 1.0f}, {50.0f, 45.0f}}
	};

	const float WALK_SPEED = 40.0f;
}



bool Normal::Start() {
	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Normal));
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}

	

	return true;
}



bool Gimmick::Start() {
	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Gimmick));
	if (!IsModel(m_enemyModelRender)) {
		return false;
	}
	return true;
}



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
	RandomWalkAround();

	//デバッグ用ベクトル描画

	DrawVectorFront();
	DrawVectorToMovePos();
}


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


void Enemy::SetEnemyModel(const int enemyNum) {
	//メンバ変数へ代入
	ModelRender* model = new ModelRender;
	std::string filePath = EnemiesModel[enemyNum].GetModelFullPath();
	Vector3 scale = EnemiesModel[enemyNum].modelScale;
	Vector2 collisionScl = EnemiesModel[enemyNum].charConScale;	
	float rot = 0.0f;
	rot = rand() % 360;
	m_enemyRotate.SetRotationDegY(rot);
	//モデルとコリジョンを初期化
	model->Init(filePath.c_str());
	model->SetTRS(m_enemyPos, m_enemyRotate, scale);

	//float rotation = rand() % 360;
	//m_enemyRotate.SetRotationDegY(rotation);
	//model->SetRotation(m_enemyRotate);
	
	m_enemyModelRender = model;
	m_enemyModelRender->Update();
	m_enemyCharaCon.Init(collisionScl.x, collisionScl.y, m_enemyPos);
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


void Enemy::RandomWalkAround() {
	if (IsBeingToMovePos()) {		
		DecideToMovePos();
		StartWaitTime(m_isWait);
		std::thread waitThread([this]() {
			this->RandomWait(this->m_isWait);
			});
		//std::thread waitThread(RandomWait, canMove);
		waitThread.detach();
	}

	//待機中だったら
	if (IsWait()) {
		return;
	}

	Vector3 dif = m_toMovePos - m_enemyPos;
	dif.Normalize();
	
	//移動速度をリセット(加速させないため)
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


void Enemy::DrawVectorFront() {
	Vector3 front = Vector3::AxisZ;

	m_enemyRotate.Apply(front);
	front.Normalize();
	front *= 200.0f;
	Vector3 origin = m_enemyPos;
	origin.y += 80.0f;
	g_k2Engine->DrawVector(front, origin);
}


void Enemy::DrawVectorToMovePos() {
	Vector3 toMoveVec = m_toMovePos - m_enemyPos;
	toMoveVec.Normalize();
	toMoveVec *= 200.0f;
	Vector3 origin = m_enemyPos;
	origin.y += 100.0f;
	g_k2Engine->DrawVector(toMoveVec, origin);
}


const bool Enemy::IsWait()const {
	return m_isWait;
}


const Vector3* Enemy::GetPosition()const {
	return &m_enemyPos;
}


bool Enemy::IsModel(const ModelRender* model) {
	if (!model) {
		return false;
	}
	return true;
}



bool Enemy::IsBeingToMovePos()const {
	Vector3 dif = m_toMovePos - m_enemyPos;

	if (dif.Length() >= WALK_SPEED * 1.2) {
		return false;
	}
	return true;
}



bool Enemy::IsRotateMovePos() {

	return true;
}








