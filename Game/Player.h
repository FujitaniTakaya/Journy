#pragma once
#include "Character.h"
#include "ActorStatus.h"



enum EnPlayerState {
	enPlayerState_Idle,
	enPlayerState_Walk,
	enPlayerState_Run,
	enPlayerState_Jump,
	enPlayerState_Num
};

/**
* @brief プレイヤークラス
*/
class Player : public Character {
private:
	
	EnPlayerState m_state = EnPlayerState::enPlayerState_Idle;
	EnMoveState m_moveState = EnMoveState::enMoveState_Walk;
	EnJumpPower m_jumpPowerState = EnJumpPower::enJumpPower_First;
	CollisionObject* m_atkCollision = nullptr;
	PlayerStatus* m_playerStatus = nullptr;
	bool m_isKillEnemy = false;
	bool m_isNearCamera = false;


public:
	Player();
	~Player()override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

	
public:
	//ゲッター・セッター系
	inline CollisionObject* GetAtkCollision()const { return m_atkCollision; }

	inline void SetIsKillEnemy(const bool isKill) { m_isKillEnemy = isKill; }

	inline void SetIsNearCamera(const bool isNear) { m_isNearCamera = isNear; }

	inline PlayerStatus* GetStatus()const { return m_playerStatus; }



/** このクラスの中だけで使う	*/

	/**	モデルの初期化	*/
private:
	//void InitializeCharacter()override;
	//void InitializeModel();	
	void LoadAnimationClips()override;
	void SetUpModel()override;
	void InitializeCollisionObject();
	void InitializeStatusInfo();


	/**	攻撃コリジョン情報更新	*/
	void UpdateAtkCollisionInfo();


	/**	行動系	*/
private:
	void Move();

	void Jump();
	
	void TripleJump();

	void StompJump();

	void ManageStateAndAnimation();

	/**	行動フラグ系	*/
private:

	inline bool IsRun() {
		if (!IsMove() || !g_pad[0]->IsPress(enButtonB)) return false;

		return true;
	}


private:
	/**	ジャンプパワーステートの調整*/
	inline const void AdjustNextJumpState() {
		uint8_t nextState = static_cast<uint8_t>(m_jumpPowerState) + 1;
		//ジャンプ力状態を次に進める
		m_jumpPowerState = static_cast<EnJumpPower>((nextState) % EnJumpPower::enJumpPower_Num);
		if (m_jumpPowerState == EnJumpPower::enJumpPower_Num) {
			m_jumpPowerState = EnJumpPower::enJumpPower_First;
		}
	}
};