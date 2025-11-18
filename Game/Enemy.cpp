#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include <random>
#include <thread>


//
//
//
//Enemy::~Enemy() {
//}
//
//
//bool Normal::Start() {
//	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Normal));
//	GetOtherClassInfo();
//	if (!IsModel(m_enemyModelRender)) {
//		return false;
//	}
//
//	
//
//	return true;
//}
//
//
//
//bool Gimmick::Start() {
//	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Gimmick));
//	GetOtherClassInfo();
//	if (!IsModel(m_enemyModelRender)) {
//		return false;
//	}
//	return true;
//}
//
//
//
//bool Boss::Start() {
//	SetEnemyModel(static_cast<int>(EnEnemy::enEnemy_Boss));
//	GetOtherClassInfo();
//	if (!IsModel(m_enemyModelRender)) {
//		return false;
//	}
//	return true;
//}
//
//
//void Enemy::Update() {
//	if (!IsStart()) {
//		return;
//	}
//	//RandomWalkAround();
//
//	Move();
//
//	//デバッグ用ベクトル描画
//	//DrawVectorFront();
//	//DrawVectorToMovePos();
//
//	Death();
//	KillPlayer();
//}
//
//
//void Enemy::Render(RenderContext& rc) {
//	if (!IsModel(m_enemyModelRender)) {
//		return;
//	}
//	m_enemyModelRender->Draw(rc);
//}
//
//
//void Enemy::UpdateEnemyInfo() {
//	m_enemyPos = m_enemyCharaCon.Execute(m_moveSpeed, GameInfo::ONE_FRAME);
//	m_enemyModelRender->SetPosition(m_enemyPos);
//	m_enemyModelRender->SetRotation(m_enemyRotate);
//	m_enemyModelRender->Update();
//}
//
//
//void Enemy::SetEnemyModel(const int enemyNum) {
//	//モデルの初期化
//	ModelRender* model = new ModelRender;
//	std::string filePath = EnemiesModel[enemyNum].GetModelFullPath();
//	model->Init(filePath.c_str());
//
//	//モデルの位置、回転、スケールを設定
//	Vector3 scale = EnemiesModel[enemyNum].modelScale;
//	Vector2 collisionScl = EnemiesModel[enemyNum].charConScale;
//	m_enemyRotate.SetRotationDegY(rand() % 360);	
//	model->SetTRS(m_enemyPos, m_enemyRotate, scale);
//	
//	m_enemyModelRender = model;
//	m_enemyModelRender->Update();
//	m_enemyCharaCon.Init(collisionScl.x, collisionScl.y, m_enemyPos);
//
//	m_enemyType = static_cast<EnEnemy>(enemyNum);
//}
//
//
//void Enemy::GetOtherClassInfo() {
//	//プレイヤーの情報を取得
//	m_player = FindGO<Player>("player");
//}
//
//
//void Enemy::Move() {
//	if (IsFoundPlayer()) {
//		ChasePlayer();
//		return;
//	}
//
//	RandomWalkAround();
//}
//
//
//
//void Enemy::StartWaitTime(std::atomic<bool>& waitFlag) {
//	waitFlag = true;
//}
//
//
//void Enemy::DecideToMovePos() {
//	m_toMovePos.x = rand() % 401 - 200;
//	m_toMovePos.z = rand() % 401 - 200;
//	m_toMovePos += m_firstEnemyPos;
//	m_toMovePos.y = 0.0f;
//}
//
//
//void Enemy::RandomWalkAround() {
//	//目的地に到着していたら
//	if (IsBeingToMovePos()) {
//		//新しい目的地を決定
//		DecideToMovePos();
//
//		//待機開始
//		StartWaitTime(m_isWait);
//		std::thread waitThread([this]() {
//			this->RandomWait(this->m_isWait);
//			});
//		//待機処理をデタッチして別スレッドで実行
//		waitThread.detach();
//	}
//
//	//待機中だったら
//	if (IsWait()) {
//		return;
//	}
//
//	//移動速度をリセット(加速させないため)
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//
//	//前方向と目的地の方向を比べて回転させる
//	if (WhichRotateMovePos() != EnEnemyRot::enEnemyRot_None) {
//		RotToMoveDirection();
//		return;
//	}
//
//	//目的地の方向を取得
//	Vector3 dif = m_toMovePos - m_enemyPos;
//	dif.Normalize();
//	
//	m_moveSpeed += dif * WALK_SPEED;
//
//	//エネミーの位置を更新
//	UpdateEnemyInfo();
//
//}
//
//
//void Enemy::RandomWait(std::atomic<bool>& waitFlag) {
//	int waitTime = rand() % 3000 + 300;
//	std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
//	waitFlag = false;
//}
//
//
//void Enemy::RotToMoveDirection() {
//	float rotAmount = 0.0f;
//
//	//左右どちらに回転すればいいか判定
//	EnEnemyRot rotateDir = WhichRotateMovePos();
//
//	if (rotateDir == EnEnemyRot::enEnemyRot_Right) {
//		//右回転
//		rotAmount = -ROTATE_SPEED;
//	}
//	if (rotateDir == EnEnemyRot::enEnemyRot_Left) {
//		//左回転
//		rotAmount = ROTATE_SPEED;
//	}
//	m_enemyRotate.AddRotationDegY(rotAmount);
//	//エネミーの情報を更新
//	UpdateEnemyInfo();
//}
//
//
//void Enemy::ChasePlayer() {
//	//プレイヤーの位置を取得
//	Vector3 playerPos = m_player->GetPosition();
//	//プレイヤーの方向ベクトルを取得
//	Vector3 toPlayerVec = playerPos - m_enemyPos;
//	toPlayerVec.Normalize();
//	toPlayerVec.y = 0.0f;
//
//	//移動速度をリセット(加速させないため)
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//	m_moveSpeed += toPlayerVec * CHASE_SPEED;
//	
//	m_enemyRotate.SetRotationYFromDirectionXZ(m_moveSpeed);
//	//エネミーの情報を更新
//	UpdateEnemyInfo();
//
//}
//
//
//void Enemy::Death() {
//	if (!IsHitPlayerAtkCollision()) {
//		return;
//	}
//	m_player->SetFlagIsKillEnemy(true);
//	//エネミーを削除
//	DeleteGO(this);
//}
//
//
//void Enemy::KillPlayer() {
//	if (!IsHitPlayerCharaConCollision()) {
//		return;
//	}
//	m_player->ReducePlayerLife();
//}
//
//
//const bool Enemy::IsFoundPlayer() {
//	Vector3 playerPos = m_player->GetPosition();
//	//エネミーからプレイヤーへのベクトルを取得
//	Vector3 toPlayerVec = playerPos - m_enemyPos;
//	//プレイヤーまでの距離を取得
//	float distance = toPlayerVec.Length();
//	
//	toPlayerVec.Normalize();
//	
//	
//	//エネミーの前方向ベクトルを取得
//	Vector3 front = Vector3::AxisZ;
//	m_enemyRotate.Apply(front);
//	front.Normalize();
//		
//	
//	//内積を求める
//	float dot = Dot(front, toPlayerVec);
//	
//	//距離が遠すぎたら発見しない
//	if (distance > 300.0f) {
//		return false;
//	}
//	//前方向にいなければ発見しない
//	if (dot < 0.6f) {
//		return false;
//	}
//	return true;
//}
//
//
//const bool Enemy::IsHitPlayerAtkCollision() {
//	//プレイヤーの攻撃コリジョンを取得
//	CollisionObject* collision = m_player->GetAtkCollision();
//	if (!collision) {
//		return false;
//	}
//	//エネミーのキャラコンとプレイヤーの攻撃コリジョンが当たっていたら
//	if (!collision->IsHit(m_enemyCharaCon)) {
//		return false;
//	}
//	const float playerHight = m_player->GetPosition().y;
//	const float enemyHedHight = m_enemyPos.y + (EnemiesModel[static_cast<int>(GetEnemyType())].charConScale.y * 2);
//	if (playerHight <= enemyHedHight) {
//		return false;
//	}
//
//	return true;
//}
//
//
//const bool Enemy::IsHitPlayerCharaConCollision() {
//	CollisionObject* collision = m_player->GetCharaConCollision();
//	if (!collision) {
//		return false;
//	}
//	//エネミーのキャラコンとプレイヤーのキャラコンが当たっていたら
//	if (!collision->IsHit(m_enemyCharaCon)) {
//		return false;
//	}
//	return true;
//}
//
//
//const bool Enemy::IsWait()const {
//	return m_isWait;
//}
//
//
//const Vector3* Enemy::GetPosition()const {
//	return &m_enemyPos;
//}
//
//
//bool Enemy::IsModel(const ModelRender* model) {
//	if (!model) {
//		return false;
//	}
//	return true;
//}
//
//
//inline const EnEnemy& Enemy::GetEnemyType()const {
//	return m_enemyType;
//}
//
//
//bool Enemy::IsBeingToMovePos()const {
//	Vector3 dif = m_toMovePos - m_enemyPos;
//
//	if (dif.Length() >= WALK_SPEED * 1.2) {
//		return false;
//	}
//	return true;
//}
//
//
//
//const EnEnemyRot Enemy::WhichRotateMovePos() {
//	Vector3 toMoveVec = m_toMovePos - m_enemyPos;
//	toMoveVec.y = 0.0f;
//	toMoveVec.Normalize();
//
//	Vector3 front = Vector3::AxisZ;
//	m_enemyRotate.Apply(front);
//	front.y = 0.0f;
//	front.Normalize();
//
//	//外積を求める
//	//右回りか左回りか判定するため
//	Vector3 cross = Cross(front, toMoveVec);
//	cross.Normalize();
//	
//	//内積を求める
//	float dot = Dot(front, toMoveVec);
//	
//	//ほぼ同じ方向を向いていれば回転しない
//	if (dot > FRONT_ANGLE) {
//		return EnEnemyRot::enEnemyRot_None;
//	}
//	//0.0fより小さければ右回転
//	if (cross.y < 0.0f) {
//		return EnEnemyRot::enEnemyRot_Right;
//	}
//	//0.0fより大きければ左回転
//	if (cross.y > 0.0f) {
//		return EnEnemyRot::enEnemyRot_Left;
//	}
//}


bool Normal::Start() {
	m_enemyType = EnEnemy::enEnemy_Normal;
	InitializeCharacter();
	DecideToMovePos();
	if (!m_player) {
		return false;
	}
	return true;
}


void Normal::Update() {
	if (!IsStart()) return;

	DrawVectorFront();
	DrawVectorToMovePos();

	Move();
	Death();

	m_moveSpeed.y = 0.0f;

	UpdateTRSInfo();	
	UpdateCollisionInfo();
}

bool Gimmick::Start() {
	m_enemyType = EnEnemy::enEnemy_Gimmick;
	InitializeCharacter();
	if (!m_player) {
		return false;
	}
	return true;
}


bool Boss::Start() {
	m_enemyType = EnEnemy::enEnemy_Boss;
	InitializeCharacter();
	if (!m_player) {
		return false;
	}
	return true;
}


void Gimmick::Update() {
	Move();
	UpdateTRSInfo();
}


void Boss::Update() {
	Move();
	UpdateTRSInfo();
	UpdateCollisionInfo();
}


void Normal::Render(RenderContext& rc) {
	if (GetModelRender()) m_modelRender.Draw(rc);
}


void Enemy::InitializeCharacter() {
	InitializeModel();
	//InitializeCollisionObject();
	InitializeGetOtherClassInfo();
}


void Enemy::InitializeModel() {

	//モデルの初期化
	const std::string filePath = m_status.GetEnemyInfo(m_enemyType).GetModelFullPath();
	m_modelRender.Init(filePath.c_str());
	m_charConScl = m_status.GetEnemyInfo(m_enemyType).GetCharConScale();
	m_characterController.Init(m_charConScl.x, m_charConScl.y, m_position);

	//m_position.y += 30.0f;
	UpdateTRSInfo();
}


void Enemy::InitializeCollisionObject() {
	m_characterCollision = new CollisionObject;
	
	m_characterCollision->CreateCapsule(m_position, m_rotation, m_charConScl.x, m_charConScl.y);
}


void Enemy::InitializeGetOtherClassInfo() {
	m_player = FindGO<Player>("player");
}


void Enemy::Move() {
	if (IsFoundPlayer()) {
		ChasePlayer();
		return;
	}
	RandomWalkAround();
	//m_moveSpeed.y = 0.0f;
}


void Enemy::Death() {
	if (!IsStompedByPlayer()) return;

	//プレイヤーのキルフラグを立てる
	m_player->SetIsKillEnemy(true);
	//エネミーを削除
	DeleteGO(this);
}


void Enemy::RandomWalkAround() {
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

	Vector3 dif = m_toMovePos - m_position;
	dif.Normalize();
	Vector3 front = Vector3::AxisZ;
	front.Normalize();
	m_rotation.Apply(front);
	//内積を求める
	float dot = Dot(front, dif);

	//ほぼ同じ方向を向いていれば回転しない
	if (dot < EnemyStatus::FRONT_ANGLE) {
		//右回りか左回りか判定する
		Vector3 cross = Cross(front, dif);
		cross.Normalize();
		//0.0fより小さければ右回転
		if (cross.y < 0.0f) {
			//右回転
			m_rotation.AddRotationDegY(-EnemyStatus::ROTATE_SPEED);
		}
		//0.0fより大きければ左回転
		else if (cross.y > 0.0f) {
			//左回転
			m_rotation.AddRotationDegY(EnemyStatus::ROTATE_SPEED);
		}		
		return;
	}


	

	
	const Vector3 speed = dif * m_status.GetWalkSpeed(m_enemyType);
	m_moveSpeed += speed;
}


void Enemy::ChasePlayer() {
	//プレイヤーの位置を取得
	Vector3 playerPos = m_player->GetPosition();
	//プレイヤーの方向ベクトルを取得
	Vector3 toPlayerVec = playerPos - m_position;
	toPlayerVec.Normalize();
	//Y・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽK・ｽv・ｽﾈゑｿｽ
	//toPlayerVec.y = m_firstPos.y;

	//移動速度をリセット(加速させないため)
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += toPlayerVec * EnemyStatus::CHASE_SPEED;
	
	RotateToMoveDirection();
	//エネミーの情報を更新

}


const bool Enemy::IsFoundPlayer() {
	Vector3 playerPos = m_player->GetPosition();
	//エネミーからプレイヤーへのベクトルを取得
	Vector3 toPlayerVec = playerPos - m_position;
	//プレイヤーまでの距離を取得
	float distance = toPlayerVec.Length();
	
	toPlayerVec.Normalize();
	
	
	//エネミーの前方向ベクトルを取得
	Vector3 front = Vector3::AxisZ;
	m_rotation.Apply(front);
	front.Normalize();
		
	
	//内積を求める
	float dot = Dot(front, toPlayerVec);
	
	//距離が遠すぎたら発見しない
	if (distance > 300.0f) {
		return false;
	}
	//前方向にいなければ発見しない
	if (dot < 0.6f) {
		return false;
	}
	return true;
}


bool Enemy::IsStompedByPlayer() {
	//プレイヤーの攻撃コリジョンを取得
	CollisionObject* charCon = m_player->GetAtkCollision();
	//コリジョンがなければ処理しない
	if (!charCon) {
		return false;
	}

	//エネミーのキャラコンとプレイヤーの攻撃コリジョンが当たっていたら
	if (!charCon->IsHit(m_characterController)) {
		return false;
	}

	//プレイヤーの高さとエネミーの頭の高さを比較
	const float playerHight = m_player->GetPosition().y;
	const float enemyHedHight = m_position.y + (m_charConScl.y * 2);

	if (playerHight <= enemyHedHight) {
		return false;
	}

	return true;	
}


void Enemy::DrawVectorToMovePos() {
	Vector3 toMoveVec = m_toMovePos - m_position;

	toMoveVec.Normalize();
	toMoveVec *= 100.0f;
	Vector3 origin = m_position;
	origin.y = m_position.y + 50.0f;

	g_k2Engine->DrawVector(toMoveVec, origin);
}


void Enemy::DrawVectorFront() {
	Vector3 front = Vector3::AxisZ;
	m_rotation.Apply(front);
	front.Normalize();
	front *= 100.0f;
	Vector3 origin = m_position;
	origin.y = m_position.y + 50.0f;
	g_k2Engine->DrawVector(front, origin);
}
