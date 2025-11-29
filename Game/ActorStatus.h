#pragma once
#include "Text.h"
class ActorStatus
{
private:
	static constexpr float one_frame = 1.0f / 60.0f;		//1フレーム分の時間
	static constexpr float max_flying_time = 0.5f;			//重力加速の最大フレーム数
	static constexpr float gravity = -19.8f;				//重力加速度

	float m_flyingTime = 0.0f;								//滞空時間


public:

	/**
	 * @brief フレームカウントを1フレーム分加算する
	 * @param frameCount 足したいフレームカウント
	 */
	void AddOneFrame(float& frameCount);

	/**
	 * @brief 重力を取得する
	 */
	float GetGravity();


	/**	滞空時間をリセット*/
	void ResetFlyingTime();

public:
	ActorStatus();
	virtual ~ActorStatus();
};


class CharacterStatus : public ActorStatus {
protected:
	int m_maxLife;					//!	最大ライフ
	int m_life;						//!	現在のライフ
	std::array<float, EnMoveState::enMoveState_Num> m_moveSpeed;	//!	移動速度の配列


public:
	/** 現在のライフを取得 */
	const int& GetLife() const { return m_life; }
	/** ライフを任意の数値分回復 */
	void HealLife(const int heal) {
		m_life = std::min<int>(m_life + heal, m_maxLife);
	}


	/** ステートに応じた移動速度を取得*/
	const float& GetMoveSpeed(const EnMoveState moveState) const {
		return m_moveSpeed[static_cast<size_t>(moveState)];
	}


public:
	CharacterStatus(
		const int maxLife,
		const float walkSpeed,
		const float runSpeed
	);
	virtual ~CharacterStatus()override;
};



/**
 *	 @brief ジャンプ情報のクラス
 */
class JumpInfo {
private:
	float m_jumpPower = 0.0f;			//!ジャンプパワー
	float m_jumpAnimSpeed = 0.0f;		//!ジャンプアニメーションの再生速度


public:
	JumpInfo(
		const float jumpPower,
		const float jumpAnimSpeed
	) :
		m_jumpPower(jumpPower),
		m_jumpAnimSpeed(jumpAnimSpeed)
	{
	}

	/**	ジャンプパワー取得*/
	const float& GetJumpPower()const;

	/**	アニメーション再生速度取得*/
	const float& GetJumpAnimSpeed()const;
};


class ModelInfo {
private:
	std::string m_modelFilePath;			//!	モデルファイルのパス


public:
	ModelInfo(
		const std::string& modelFilePath
	) :
		m_modelFilePath(modelFilePath)
	{
	}

	void SetModelFilePath(const std::string& path) {
		m_modelFilePath = path;
	}

	const std::string GetModelFullPath()const {
		return m_modelFilePath;
	}
};


class AnimInfo {
private:
	std::string m_animFilePath;			//!	アニメーションファイルのパス
	float m_playAnimSpeed;				//!	アニメーションの再生速度
	bool m_isLoop;

public:
	AnimInfo();
	
	
	AnimInfo(
		const std::string& animFilePath,
		const float playAnimSpeed,
		const bool isLoop
	) :
		m_animFilePath(animFilePath),
		m_playAnimSpeed(playAnimSpeed),
		m_isLoop(isLoop)
	{
	}


public:
	/**	アニメーションファイルのフルパスのゲッター*/
	const std::string GetAnimFullPath()const {
		return m_animFilePath;
	}
	
	
	/**	アニメーション再生速度のゲッター*/
	const float& GetPlayAnimSpeed()const {
		return m_playAnimSpeed;
	}


	/**	ループ状態ののゲッター*/
	const bool& IsLoop()const {
		return m_isLoop;
	}	


public:
	/**	アニメーションファイルパスのセッター*/
	void SetAnimFilePath(const std::string& path) {
		m_animFilePath = path;
	}


	/**	アニメーション再生速度のセッター*/
	void SetPlayAnimSpeed(const float speed) {
		m_playAnimSpeed = speed;
	}


	/**	ループ状態のセッター*/
	void SetIsLoop(const bool isLoop) {
		m_isLoop = isLoop;
	}
};


class PlayerStatus : public CharacterStatus
{
private:

	static constexpr float m_canNextJumpTime = 0.15f;					//!	次の段のジャンプに切り替えれるまでの猶予時間	
	static constexpr float m_canStompJumpTime = 0.1f;					//! 踏みつけジャンプが可能な猶予時間


private:
	std::array<JumpInfo, EnJumpPower::enJumpPower_Num> m_jumpInfo;	//!	ジャンプ情報の配列
	float m_standingTime = 0.0f;							//!	着地時間
	float m_invincibleTime = 0.0f;							//!	無敵時間



/**	プレイヤーステータスゲッター関数*/
public:


	/** 次のジャンプに切り替え可能か */
	bool CanNextJump();

	/**	踏みつけジャンプが可能か */
	bool CanStompJump();


	/**
	 * @brief ジャンプ情報を取得する
	 * @param jumpState 取得したいジャンプの段数
	 */
	const JumpInfo& GetJumpInfo(EnJumpPower jumpState)const {
		return m_jumpInfo[static_cast<size_t>(jumpState)];
	}


public:
	/**	着地時間をリセット*/
	void ResetStandingTime() { m_standingTime = 0.0f; }


public:
	PlayerStatus();
	~PlayerStatus()override;
};


class NormalEnemyStatus : public CharacterStatus
{
private:
	float m_rotateSpeed = 1.5f;
	float m_frontAngle = 0.9999f;
	


public:
	const float& GetRotateSpeed() const { return m_rotateSpeed; }
	const float& GetFrontAngle() const { return m_frontAngle; }


public:
	NormalEnemyStatus();
	virtual ~NormalEnemyStatus()override;
};