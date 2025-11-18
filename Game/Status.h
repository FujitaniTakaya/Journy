#pragma once
#include "stdafx.h"
#include "stdint.h"

enum EnCharState {
	enCharState_Idle,
	enCharState_Walk,
	enCharState_Run,
	enCharState_Jump,
	enCharState_Num,
};


enum EnEnemy {
	enEnemy_Normal = 0,
	enEnemy_Gimmick,
	enEnemy_Boss,
	enEnemy_Num
};


enum EnMoveState {
	enMoveState_Walk,
	enMoveState_Run,
	enMoveState_Num
};


enum EnJumpPower {
	enJumpPower_First,
	enJumpPower_Second,
	enJumpPower_Third,
	enJumpPower_Num
};
/*******************************/


struct GameStatus{
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
	void AddOneFrame(float& frameCount) {
		frameCount += one_frame;
	}

	/**
	* @brief 1フレーム分の時間を取得する
	*/
	static float AddOneFrame() { return one_frame; }
	
	
	/**
	* @brief 重力を取得する
	*/
	float GetGravity() {
		AddOneFrame(m_flyingTime);
		m_flyingTime = std::min<float>(m_flyingTime, max_flying_time);
		return gravity * m_flyingTime * 2;
	}
	

	/**	滞空時間をリセット*/
	void ResetFlyingTime() { m_flyingTime = 0.0f; }
};


struct PlayerStatus : public GameStatus {
public:
	static constexpr const char* const unity_file_path = "Assets/modelData/unityChan.tkm";		//!	ユニティちゃんのファイルパス

private:
	static constexpr float invincible_time = 2.0f;												//!	無敵時間	
	static constexpr const char* animation_file_path = "Assets/animData/";						//!	ファイルの場所
	static constexpr const char* animation_file_extension = ".tka";								//!	拡張子

	static constexpr float can_next_jump_time = 0.25f;					//!	次の段のジャンプに切り替えれるまでの猶予時間	
	static constexpr float can_stomp_jump_time = 0.1f;


private:
	/**
	*	@brief アニメーション情報構造体
	*/
	struct PlayerAnimInfo {		
	private:
		std::string fileName;			//!ファイル名
		float playAnimSpeed;			//!アニメーションの再生速度

	public:
		/**	コンストラクタ*/
		PlayerAnimInfo(
			const std::string fileName,
			const float playAnimSpeed):
			fileName(fileName),
			playAnimSpeed(playAnimSpeed)
		{}

	/**	ゲッター*/
	public:

		/**
		*  @brief アニメーションファイルのフルパスを取得		
		*/
		const std::string GetAnimFullPath()const {

			return std::string(PlayerStatus::animation_file_path) +
				fileName +
				std::string(PlayerStatus::animation_file_extension);
		}

		/**	アニメーション再生速度取得*/
		const float& GetPlayAnimSpeed()const { return playAnimSpeed; }
	};

private:
	/**
	*	 @brief ジャンプ情報構造体
	*/
	struct JumpInfo {
	private:
		float jumpPower = 0.0f;			//!ジャンプパワー
		float jumpAnimSpeed = 0.0f;		//!ジャンプアニメーションの再生速度


		/**	コンストラクタ*/
	public:
		/**	配列作成時に使用*/
		JumpInfo(const float jumpPower, const float jumpAnimSpeed) : 
			jumpPower(jumpPower), 
			jumpAnimSpeed(jumpAnimSpeed) 
		{}

		/**	ゲッター*/
	public:
		/**	ジャンプパワー取得*/
		const float& GetJumpPower()const { return jumpPower; }

		/**	アニメーション再生速度取得*/
		const float& GetJumpAnimSpeed()const { return jumpAnimSpeed; }
	};

	//!	キャラクターコントローラーのサイズ
	const Vector2 character_controller = {
		15.0, 65.0f 
	};

	//!	プレイヤーの開始位置
	const Vector3 start_pos = { 
		100.0f,	0.0f, 100.0f
	};

	//!	移動速度の配列
	const std::array<float,EnMoveState::enMoveState_Num> move_speed = {
		200.0f,	500.0f 		
	};
	
	//!	ジャンプ情報の配列
	std::array<std::unique_ptr<JumpInfo>, EnJumpPower::enJumpPower_Num> m_jump_info = { nullptr };

	//!	アニメーション情報の配列
	std::array<std::unique_ptr<PlayerAnimInfo>, EnCharState::enCharState_Num> m_animation_info = { nullptr };

	float m_standingTime = 0.0f;							//!	着地時間
	float m_invincibleTime = 0.0f;							//!	無敵時間
	int m_maxLife;											//!	最大ライフ
	int m_life;												//!	現在のライフ

	/**
	*	@brief コンストラクタ
	*/
	PlayerStatus(int maxLife, int standingTime) :
		m_maxLife(maxLife), 
		m_life(maxLife), 
		m_standingTime(standingTime) 
	{}


/**	コンストラクタ*/
public:
	PlayerStatus() :
		m_jump_info({
		std::make_unique<JumpInfo>(320.0, 1.0f),
		std::make_unique<JumpInfo>(500.0, 0.8f),
		std::make_unique<JumpInfo>(800.0, 0.3f)
		}),

		m_animation_info({
		std::make_unique<PlayerAnimInfo>("idle", 1.0f),
		std::make_unique<PlayerAnimInfo>("walk", 1.3f),
		std::make_unique<PlayerAnimInfo>("run", 1.5f),
		std::make_unique<PlayerAnimInfo>("jump", 1.0f)
		}),

		m_maxLife(3), 
		m_life(m_maxLife), 
		m_standingTime(0.0f)
	{}


/**	プレイヤーステータスゲッター関数*/
public:
	/**
	*	@brief 次の段階のジャンプに切り替え可能かどうか
	*/
	bool CanNextJump() {
		AddOneFrame(m_standingTime);
		//次の段階のジャンプに切り替え可能か
		if (m_standingTime <= can_next_jump_time) { return true; }
		return false;
	}


	/**
	*	@brief 踏みつけジャンプが可能かどうか
	*/
	bool CanStompJump() {
		AddOneFrame(m_standingTime);
		if (m_standingTime <= can_stomp_jump_time) { return true; }
		//if (m_standingTime <= can_stomp_jump_time) { return true; }
		return false;
	}


	/**
	* @brief ジャンプ情報を取得する
	* @param jumpPower 取得したいジャンプの段数
	*/
	const JumpInfo& GetJumpInfo(const EnJumpPower jumpPower)const {
		return *m_jump_info[static_cast<size_t>(jumpPower)];
	}
	
/**	モデル系*/
public:
	/**
	* @brief アニメーション情報を取得する
	* @param state 取得したいアニメーションの状態
	*/
	const PlayerAnimInfo& GetAnimInfo(const EnCharState state) {
		return *m_animation_info[static_cast<size_t>(state)];
	}

	/**	ユニティちゃんのファイルパスを取得*/
	//static const char* GetUnityFilePath() { return unity_file_path; }

	/** キャラコン情報を取得*/
	const Vector2& GetCharConInfo() const { return character_controller; }


/**	位置情報などのゲッター*/
public:
	/** 初期地点を取得*/
	const Vector3& GetStartPos() const { return start_pos; }

	/** ステートに応じた移動速度を取得*/
	const float& GetMoveSpeed(const EnMoveState moveState) const {
		return move_speed[static_cast<size_t>(moveState)];
	}

public:
	/**	着地時間をリセット*/
	void ResetStandingTime() { m_standingTime = 0.0f; }
};


struct EnemyStatus {
	//ファイルの場所
	static constexpr const char* const FILE_PATH = "Assets/enemy/";
	//拡張子
	static constexpr const char* const FILE_EXTENSTION = ".tkm";

	struct EnemyInfo {
	private:
		//ファイル名
		std::string fileName;
		//キャラコンのスケール
		Vector2 charConScale;

	public:
		EnemyInfo(
			const std::string fileName,
			const float charConX,
			const float charConY) :
			fileName(fileName),
			charConScale(charConX, charConY)
		{}

		EnemyInfo(){}

		/// <summary>
		/// エネミーモデルのファイルパスを取得
		/// </summary>
		const std::string GetModelFullPath()const {
			return std::string(FILE_PATH) + fileName + std::string(FILE_EXTENSTION);
		}
		/**	キャラコンのスケールを取得*/
		const Vector2& GetCharConScale()const { return charConScale; }
	};
	


public:
	static constexpr float CHASE_SPEED = 100.0f;				//プレイヤーを追従するスピード
	static constexpr float ROTATE_SPEED = 1.5f;				//回転するスピード
	static constexpr float FRONT_ANGLE = 0.9999f;			//正面方向の許容値(コサイン値)

private:
	std::array<float, EnEnemy::enEnemy_Num> walk_speed;
	std::array<std::unique_ptr<EnemyInfo>, EnEnemy::enEnemy_Num> enemy_info = { nullptr };


public:
	EnemyStatus() : 
		enemy_info({
		std::make_unique<EnemyInfo>("normalEnemy/NormalEnemy",25.0f, 20.0f),
		std::make_unique<EnemyInfo>("gimmickEnemy/GimmickEnemy",25.0f, 30.0f),	
		std::make_unique<EnemyInfo>("bossEnemy/BossEnemy",50.0f, 45.0f)
		}),


		/*m_animation_info({
		std::make_unique<PlayerAnimInfo>("idle", 1.0f),
		std::make_unique<PlayerAnimInfo>("walk", 1.3f),
		std::make_unique<PlayerAnimInfo>("run", 1.5f),
		std::make_unique<PlayerAnimInfo>("jump", 1.0f)
			}),*/

		walk_speed({
			20.0f, 30.0f, 40.0f
		})
	{}


	const EnemyInfo& GetEnemyInfo(const EnEnemy enemyType)const {
		return *enemy_info[enemyType];
	}

	/**	ステートに応じて歩く速度を取得*/
	const float& GetWalkSpeed(const EnEnemy enemyType)const {
		return walk_speed[enemyType];
	}

};


struct NormaStatus : public EnemyStatus {


};


struct GimmickStatus : public EnemyStatus {
};


struct BossStatus : public EnemyStatus {
};