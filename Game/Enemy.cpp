#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "UI.h"
#include <random>
#include <thread>


//void Enemy::InitializeAnimationClips(const ActorStatus& status) {
//	//アニメーションの初期化
//	m_animationClips = new AnimationClip[status.GetAnimNum()];
//
//	for (size_t i = 0; i < status.GetAnimNum(); i++) {
//		const AnimInfo& anim = status.GetAnimInfo(i);
//		
//		const std::string animFilePath = anim.GetAnimFullPath();
//		const bool isLoop = anim.IsLoop();
//		m_animationClips[i].Load(animFilePath.c_str());
//		m_animationClips[i].SetLoopFlag(isLoop);
//	}
//}


//void Enemy::InitializeModel(const ActorStatus& status) {
//	InitializeAnimationClips(status);
//	const ModelInfo& modelInfo = status.GetModelInfo();
//	const std::string filePath = modelInfo.GetModelFullPath();
//	const int animNum = status.GetAnimNum();
//	m_charConScl = status.GetCharConScale();
//	m_modelRender.Init(filePath.c_str(), m_animationClips, animNum);
//	m_firstPos = m_transform.position;
//	m_characterController.Init(m_charConScl.x, m_charConScl.y, m_transform.position);
//	UpdateTRSInfo();
//}


void Enemy::LoadAnimationClips() {
	//各エネミーで実装
}

void Enemy::SetUpModel() {
	//各エネミーで実装
}


bool Gimmick::Start() {
	if (!m_player) {
		return false;
	}
	return true;
}


bool Boss::Start() {
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
}


void Enemy::GetOtherClassInfo() {
	m_player = FindGO<Player>("player");
	m_ui = FindGO<UI>("ui");
}


void Enemy::Death() {
	if (!IsStompedByPlayer()) return;

	//プレイヤーのキルフラグを立てる
	m_player->SetIsKillEnemy(true);

	//スコアを加算
	m_ui->AddScore(nsUI::Score::TYPE[enScoreType_NormalEnemy]);

	//エネミーを削除
	DeleteGO(this);
}


void Gimmick::Move(){}


void Boss::Move() {}

void Enemy::ChasePlayer(CharacterStatus* status) {
	//プレイヤーの位置を取得
	Vector3 playerPos = m_player->GetTRSIns().GetPosition();
	//プレイヤーの方向ベクトルを取得
	Vector3 toPlayerVec = playerPos - m_transform.position;
	toPlayerVec.Normalize();
	//Y・ｽﾌ擾ｿｽ・ｽ・ｽ・ｽK・ｽv・ｽﾈゑｿｽ
	//toPlayerVec.y = m_firstPos.y;

	//移動速度をリセット(加速させないため)
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
	m_moveSpeed += toPlayerVec * status->GetMoveSpeed(EnMoveState::enMoveState_Run);
	
	RotateToMoveDirection();
	//エネミーの情報を更新

}


const bool Enemy::IsFoundPlayer() {
	Vector3 playerPos = m_player->GetTRSIns().GetPosition();
	//エネミーからプレイヤーへのベクトルを取得
	Vector3 toPlayerVec = playerPos - m_transform.position;
	//プレイヤーまでの距離を取得
	float distance = toPlayerVec.Length();
	
	toPlayerVec.Normalize();
	
	
	//エネミーの前方向ベクトルを取得
	Vector3 front = Vector3::AxisZ;
	m_transform.rotation.Apply(front);
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
	const float playerHight = m_player->GetTRSIns().GetPosition().y;
	const float enemyHedHight = m_transform.position.y + (m_charConScl.y * 2);

	if (playerHight <= enemyHedHight) {
		return false;
	}

	return true;	
}


void Enemy::DrawVectorToMovePos() {
	Vector3 toMoveVec = m_toMovePos - m_transform.position;

	toMoveVec.Normalize();
	toMoveVec *= 100.0f;
	Vector3 origin = m_transform.position;
	origin.y = m_transform.position.y + 50.0f;

	g_k2Engine->DrawVector(toMoveVec, origin);
}


void Enemy::DrawVectorFront() {
	Vector3 front = Vector3::AxisZ;
	m_transform.rotation.Apply(front);
	front.Normalize();
	front *= 100.0f;
	Vector3 origin = m_transform.position;
	origin.y = m_transform.position.y + 50.0f;
	g_k2Engine->DrawVector(front, origin);
}