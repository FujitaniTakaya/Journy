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
//	//ƒfƒoƒbƒO—pƒxƒNƒgƒ‹•`‰æ
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
//	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
//	ModelRender* model = new ModelRender;
//	std::string filePath = EnemiesModel[enemyNum].GetModelFullPath();
//	model->Init(filePath.c_str());
//
//	//ƒ‚ƒfƒ‹‚ÌˆÊ’uA‰ñ“]AƒXƒP[ƒ‹‚ğİ’è
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
//	//ƒvƒŒƒCƒ„[‚Ìî•ñ‚ğæ“¾
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
//	//–Ú“I’n‚É“’…‚µ‚Ä‚¢‚½‚ç
//	if (IsBeingToMovePos()) {
//		//V‚µ‚¢–Ú“I’n‚ğŒˆ’è
//		DecideToMovePos();
//
//		//‘Ò‹@ŠJn
//		StartWaitTime(m_isWait);
//		std::thread waitThread([this]() {
//			this->RandomWait(this->m_isWait);
//			});
//		//‘Ò‹@ˆ—‚ğƒfƒ^ƒbƒ`‚µ‚Ä•ÊƒXƒŒƒbƒh‚ÅÀs
//		waitThread.detach();
//	}
//
//	//‘Ò‹@’†‚¾‚Á‚½‚ç
//	if (IsWait()) {
//		return;
//	}
//
//	//ˆÚ“®‘¬“x‚ğƒŠƒZƒbƒg(‰Á‘¬‚³‚¹‚È‚¢‚½‚ß)
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//
//	//‘O•ûŒü‚Æ–Ú“I’n‚Ì•ûŒü‚ğ”ä‚×‚Ä‰ñ“]‚³‚¹‚é
//	if (WhichRotateMovePos() != EnEnemyRot::enEnemyRot_None) {
//		RotToMoveDirection();
//		return;
//	}
//
//	//–Ú“I’n‚Ì•ûŒü‚ğæ“¾
//	Vector3 dif = m_toMovePos - m_enemyPos;
//	dif.Normalize();
//	
//	m_moveSpeed += dif * WALK_SPEED;
//
//	//ƒGƒlƒ~[‚ÌˆÊ’u‚ğXV
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
//	//¶‰E‚Ç‚¿‚ç‚É‰ñ“]‚·‚ê‚Î‚¢‚¢‚©”»’è
//	EnEnemyRot rotateDir = WhichRotateMovePos();
//
//	if (rotateDir == EnEnemyRot::enEnemyRot_Right) {
//		//‰E‰ñ“]
//		rotAmount = -ROTATE_SPEED;
//	}
//	if (rotateDir == EnEnemyRot::enEnemyRot_Left) {
//		//¶‰ñ“]
//		rotAmount = ROTATE_SPEED;
//	}
//	m_enemyRotate.AddRotationDegY(rotAmount);
//	//ƒGƒlƒ~[‚Ìî•ñ‚ğXV
//	UpdateEnemyInfo();
//}
//
//
//void Enemy::ChasePlayer() {
//	//ƒvƒŒƒCƒ„[‚ÌˆÊ’u‚ğæ“¾
//	Vector3 playerPos = m_player->GetPosition();
//	//ƒvƒŒƒCƒ„[‚Ì•ûŒüƒxƒNƒgƒ‹‚ğæ“¾
//	Vector3 toPlayerVec = playerPos - m_enemyPos;
//	toPlayerVec.Normalize();
//	toPlayerVec.y = 0.0f;
//
//	//ˆÚ“®‘¬“x‚ğƒŠƒZƒbƒg(‰Á‘¬‚³‚¹‚È‚¢‚½‚ß)
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//	m_moveSpeed += toPlayerVec * CHASE_SPEED;
//	
//	m_enemyRotate.SetRotationYFromDirectionXZ(m_moveSpeed);
//	//ƒGƒlƒ~[‚Ìî•ñ‚ğXV
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
//	//ƒGƒlƒ~[‚ğíœ
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
//	//ƒGƒlƒ~[‚©‚çƒvƒŒƒCƒ„[‚Ö‚ÌƒxƒNƒgƒ‹‚ğæ“¾
//	Vector3 toPlayerVec = playerPos - m_enemyPos;
//	//ƒvƒŒƒCƒ„[‚Ü‚Å‚Ì‹——£‚ğæ“¾
//	float distance = toPlayerVec.Length();
//	
//	toPlayerVec.Normalize();
//	
//	
//	//ƒGƒlƒ~[‚Ì‘O•ûŒüƒxƒNƒgƒ‹‚ğæ“¾
//	Vector3 front = Vector3::AxisZ;
//	m_enemyRotate.Apply(front);
//	front.Normalize();
//		
//	
//	//“àÏ‚ğ‹‚ß‚é
//	float dot = Dot(front, toPlayerVec);
//	
//	//‹——£‚ª‰“‚·‚¬‚½‚ç”­Œ©‚µ‚È‚¢
//	if (distance > 300.0f) {
//		return false;
//	}
//	//‘O•ûŒü‚É‚¢‚È‚¯‚ê‚Î”­Œ©‚µ‚È‚¢
//	if (dot < 0.6f) {
//		return false;
//	}
//	return true;
//}
//
//
//const bool Enemy::IsHitPlayerAtkCollision() {
//	//ƒvƒŒƒCƒ„[‚ÌUŒ‚ƒRƒŠƒWƒ‡ƒ“‚ğæ“¾
//	CollisionObject* collision = m_player->GetAtkCollision();
//	if (!collision) {
//		return false;
//	}
//	//ƒGƒlƒ~[‚ÌƒLƒƒƒ‰ƒRƒ“‚ÆƒvƒŒƒCƒ„[‚ÌUŒ‚ƒRƒŠƒWƒ‡ƒ“‚ª“–‚½‚Á‚Ä‚¢‚½‚ç
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
//	//ƒGƒlƒ~[‚ÌƒLƒƒƒ‰ƒRƒ“‚ÆƒvƒŒƒCƒ„[‚ÌƒLƒƒƒ‰ƒRƒ“‚ª“–‚½‚Á‚Ä‚¢‚½‚ç
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
//	//ŠOÏ‚ğ‹‚ß‚é
//	//‰E‰ñ‚è‚©¶‰ñ‚è‚©”»’è‚·‚é‚½‚ß
//	Vector3 cross = Cross(front, toMoveVec);
//	cross.Normalize();
//	
//	//“àÏ‚ğ‹‚ß‚é
//	float dot = Dot(front, toMoveVec);
//	
//	//‚Ù‚Ú“¯‚¶•ûŒü‚ğŒü‚¢‚Ä‚¢‚ê‚Î‰ñ“]‚µ‚È‚¢
//	if (dot > FRONT_ANGLE) {
//		return EnEnemyRot::enEnemyRot_None;
//	}
//	//0.0f‚æ‚è¬‚³‚¯‚ê‚Î‰E‰ñ“]
//	if (cross.y < 0.0f) {
//		return EnEnemyRot::enEnemyRot_Right;
//	}
//	//0.0f‚æ‚è‘å‚«‚¯‚ê‚Î¶‰ñ“]
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

	//ï¿½sï¿½ï¿½ï¿½pï¿½^ï¿½[ï¿½ï¿½
	Move();
	//ï¿½ï¿½ï¿½Sï¿½ï¿½ï¿½ï¿½
	Death();

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


void Normal::Update() {
	if (!IsStart()) return;

	//s“®ƒpƒ^[ƒ“
	Move();
	//€–S”»’è
	Death();

	UpdateTRSInfo();
	UpdateCollisionInfo();

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

	//ƒ‚ƒfƒ‹‚Ì‰Šú‰»
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
}


void Enemy::Death() {
	if (!IsStompedByPlayer()) return;

	//ƒvƒŒƒCƒ„[‚ÌƒLƒ‹ƒtƒ‰ƒO‚ğ—§‚Ä‚é
	m_player->SetIsKillEnemy(true);
	//ƒGƒlƒ~[‚ğíœ
	DeleteGO(this);
}


void Enemy::RandomWalkAround() {
	//–Ú“I’n‚É“’…‚µ‚Ä‚¢‚½‚ç
	if (IsBeingToMovePos()) {
		//V‚µ‚¢–Ú“I’n‚ğŒˆ’è
		DecideToMovePos();

		//‘Ò‹@ŠJn
		m_isWait = true;
		std::thread waitThread([this]() {
			this->RandomWait(m_isWait);
			});
		//‘Ò‹@ˆ—‚ğƒfƒ^ƒbƒ`‚µ‚Ä•ÊƒXƒŒƒbƒh‚ÅÀs
		waitThread.detach();
	}

	//‘Ò‹@’†‚¾‚Á‚½‚çˆ—‚µ‚È‚¢
	if (IsWait()) {	
		return;
	}


	//ˆÚ“®‘¬“x‚ğƒŠƒZƒbƒg(‰Á‘¬‚³‚¹‚È‚¢‚½‚ß)
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.y = 0.0f;

	Vector3 dif = m_toMovePos - m_position;
	dif.Normalize();
	Vector3 front = Vector3::AxisZ;
	front.Normalize();
	m_rotation.Apply(front);
	//“àÏ‚ğ‹‚ß‚é
	float dot = Dot(front, dif);

	//‚Ù‚Ú“¯‚¶•ûŒü‚ğŒü‚¢‚Ä‚¢‚ê‚Î‰ñ“]‚µ‚È‚¢
	if (dot < EnemyStatus::FRONT_ANGLE) {
		//‰E‰ñ‚è‚©¶‰ñ‚è‚©”»’è‚·‚é
		Vector3 cross = Cross(front, dif);
		cross.Normalize();
		//0.0f‚æ‚è¬‚³‚¯‚ê‚Î‰E‰ñ“]
		if (cross.y < 0.0f) {
			//‰E‰ñ“]
			m_rotation.AddRotationDegY(-EnemyStatus::ROTATE_SPEED);
		}
		//0.0f‚æ‚è‘å‚«‚¯‚ê‚Î¶‰ñ“]
		else if (cross.y > 0.0f) {
			//¶‰ñ“]
			m_rotation.AddRotationDegY(EnemyStatus::ROTATE_SPEED);
		}		
		return;
	}


	

	
	const Vector3 speed = dif * m_status.GetWalkSpeed(m_enemyType);
	m_moveSpeed += speed;
}


void Enemy::ChasePlayer() {
	//ƒvƒŒƒCƒ„[‚ÌˆÊ’u‚ğæ“¾
	Vector3 playerPos = m_player->GetPosition();
	//ƒvƒŒƒCƒ„[‚Ì•ûŒüƒxƒNƒgƒ‹‚ğæ“¾
	Vector3 toPlayerVec = playerPos - m_position;
	toPlayerVec.Normalize();
	//Yï¿½Ìï¿½ï¿½ï¿½ï¿½Kï¿½vï¿½È‚ï¿½
	//toPlayerVec.y = m_firstPos.y;

	//ˆÚ“®‘¬“x‚ğƒŠƒZƒbƒg(‰Á‘¬‚³‚¹‚È‚¢‚½‚ß)
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += toPlayerVec * EnemyStatus::CHASE_SPEED;
	
	RotateToMoveDirection();
	//ƒGƒlƒ~[‚Ìî•ñ‚ğXV

}


const bool Enemy::IsFoundPlayer() {
	Vector3 playerPos = m_player->GetPosition();
	//ƒGƒlƒ~[‚©‚çƒvƒŒƒCƒ„[‚Ö‚ÌƒxƒNƒgƒ‹‚ğæ“¾
	Vector3 toPlayerVec = playerPos - m_position;
	//ƒvƒŒƒCƒ„[‚Ü‚Å‚Ì‹——£‚ğæ“¾
	float distance = toPlayerVec.Length();
	
	toPlayerVec.Normalize();
	
	
	//ƒGƒlƒ~[‚Ì‘O•ûŒüƒxƒNƒgƒ‹‚ğæ“¾
	Vector3 front = Vector3::AxisZ;
	m_rotation.Apply(front);
	front.Normalize();
		
	
	//“àÏ‚ğ‹‚ß‚é
	float dot = Dot(front, toPlayerVec);
	
	//‹——£‚ª‰“‚·‚¬‚½‚ç”­Œ©‚µ‚È‚¢
	if (distance > 300.0f) {
		return false;
	}
	//‘O•ûŒü‚É‚¢‚È‚¯‚ê‚Î”­Œ©‚µ‚È‚¢
	if (dot < 0.6f) {
		return false;
	}
	return true;
}


bool Enemy::IsStompedByPlayer() {
	//ƒvƒŒƒCƒ„[‚ÌUŒ‚ƒRƒŠƒWƒ‡ƒ“‚ğæ“¾
	CollisionObject* charCon = m_player->GetAtkCollision();
	//ƒRƒŠƒWƒ‡ƒ“‚ª‚È‚¯‚ê‚Îˆ—‚µ‚È‚¢
	if (!charCon) {
		return false;
	}

	//ƒGƒlƒ~[‚ÌƒLƒƒƒ‰ƒRƒ“‚ÆƒvƒŒƒCƒ„[‚ÌUŒ‚ƒRƒŠƒWƒ‡ƒ“‚ª“–‚½‚Á‚Ä‚¢‚½‚ç
	if (!charCon->IsHit(m_characterController)) {
		return false;
	}

	//ƒvƒŒƒCƒ„[‚Ì‚‚³‚ÆƒGƒlƒ~[‚Ì“ª‚Ì‚‚³‚ğ”äŠr
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
