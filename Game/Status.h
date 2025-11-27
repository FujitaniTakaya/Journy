#pragma once
#include "stdafx.h"
#include "stdint.h"


enum EnEnemyType {
	enEnemyType_Normal = 0,
	enEnemyType_Gimmick,
	enEnemyType_Boss,
	enEnemyType_Num
};


enum EnJumpPower {
	enJumpPower_First,
	enJumpPower_Second,
	enJumpPower_Third,
	enJumpPower_Num
};


enum EnCharType {
	enCharType_Player,
	enCharType_NormalEnemy,
	enCharType_GimmickEnemy,
	enCharType_BossEnemy,
	enCharType_Num
};

/*******************************/


//
//struct PlayerStatus : public GameStatus {
//private:
//	static constexpr float invincible_time = 2.0f;
//
//	static constexpr float can_next_jump_time = 0.15f;					//!	次の段のジャンプに切り替えれるまでの猶予時間	
//	static constexpr float can_stomp_jump_time = 0.1f;
//
//
//private:
//	/**
//	*	 @brief ジャンプ情報構造体
//	*/
//	struct JumpInfo {
//	private:
//		float jumpPower = 0.0f;			//!ジャンプパワー
//		float jumpAnimSpeed = 0.0f;		//!ジャンプアニメーションの再生速度
//
//
//		/**	コンストラクタ*/
//	public:
//		/**	配列作成時に使用*/
//		JumpInfo(const float jumpPower, const float jumpAnimSpeed) : 
//			jumpPower(jumpPower), 
//			jumpAnimSpeed(jumpAnimSpeed) 
//		{}
//
//		/**	ゲッター*/
//	public:
//		/**	ジャンプパワー取得*/
//		const float& GetJumpPower()const { return jumpPower; }
//
//		/**	アニメーション再生速度取得*/
//		const float& GetJumpAnimSpeed()const { return jumpAnimSpeed; }
//	};
//
//	//!	キャラクターコントローラーのサイズ
//	const Vector2 character_controller = {
//		15.0, 65.0f 
//	};
//
//	//!	移動速度の配列
//	const std::array<float,EnMoveState::enMoveState_Num> move_speed = {
//		200.0f,	500.0f 		
//	};
//	
//	//!	ジャンプ情報の配列
//	std::array<std::unique_ptr<JumpInfo>, EnJumpPower::enJumpPower_Num> m_jump_info;
//
//	//!	アニメーション情報の配列
//	std::array<std::unique_ptr<AnimInfo>, EnCharState::enCharState_Num> anim_info;
//
//	std::unique_ptr<ModelInfo> model_info;
//
//	float m_standingTime = 0.0f;							//!	着地時間
//	float m_invincibleTime = 0.0f;							//!	無敵時間
//	int m_maxLife;											//!	最大ライフ
//	int m_life;												//!	現在のライフ
//
//
///**	コンストラクタ*/
//public:
//	PlayerStatus() :
//		m_jump_info({
//		std::make_unique<JumpInfo>(500.0, 1.0f),
//		std::make_unique<JumpInfo>(700.0, 0.8f),
//		std::make_unique<JumpInfo>(1000.0, 0.3f)
//		}),
//
//		anim_info({
//		std::make_unique<AnimInfo>("idle", 1.0f, true),
//		std::make_unique<AnimInfo>("walk", 1.3f, true),
//		std::make_unique<AnimInfo>("run", 1.5f, true),
//		std::make_unique<AnimInfo>("jump", 1.0f, false)
//		}),
//
//		model_info(std::make_unique<ModelInfo>(model_file_path)	),
//
//		m_maxLife(5), 
//		m_life(3), 
//		m_standingTime(0.0f)
//	{}
//
//
///**	プレイヤーステータスゲッター関数*/
//public:
//	const int& GetLife() const { return m_life; }
//
//	void HealLife(const int heal) {
//		m_life = std::min<int>(m_life + heal, m_maxLife);
//	}
//
//
//	/**
//	*	@brief 次の段階のジャンプに切り替え可能かどうか
//	*/
//	bool CanNextJump() {
//		AddOneFrame(m_standingTime);
//		//次の段階のジャンプに切り替え可能か
//		if (m_standingTime <= can_next_jump_time) { return true; }
//		return false;
//	}
//
//
//	/**
//	*	@brief 踏みつけジャンプが可能かどうか
//	*/
//	bool CanStompJump() {
//		AddOneFrame(m_standingTime);
//		if (m_standingTime <= can_stomp_jump_time) { return true; }
//		//if (m_standingTime <= can_stomp_jump_time) { return true; }
//		return false;
//	}
//
//
//	/**
//	* @brief ジャンプ情報を取得する
//	* @param jumpPower 取得したいジャンプの段数
//	*/
//	const JumpInfo& GetJumpInfo(const EnJumpPower jumpPower)const {
//		return *m_jump_info[static_cast<size_t>(jumpPower)];
//	}
//	
///**	モデル系*/
//public:
//
//	const ModelInfo& GetModelInfo()const {
//		return *model_info;
//	}
//
//
//	/**
//	* @brief アニメーション情報を取得する
//	* @param state 取得したいアニメーションの状態
//	*/
//	const AnimInfo& GetAnimInfo(size_t animIndex)const {
//		return *anim_info.at(animIndex);
//	}
//
//	/**	ユニティちゃんのファイルパスを取得*/
//	//static const char* GetUnityFilePath() { return unity_file_path; }
//
//	/** キャラコン情報を取得*/
//	const Vector2& GetCharConInfo() const { return character_controller; }
//
//
///**	位置情報などのゲッター*/
//public:
//	/** 初期地点を取得*/
//	const Vector3& GetStartPos() const { return start_pos; }
//
//	/** ステートに応じた移動速度を取得*/
//	const float& GetMoveSpeed(const EnMoveState moveState) const {
//		return move_speed[static_cast<size_t>(moveState)];
//	}
//
//public:
//	/**	着地時間をリセット*/
//	void ResetStandingTime() { m_standingTime = 0.0f; }
//
//
//
//};
//


//struct EnemyStatus {
//public:
//	static constexpr float CHASE_SPEED = 100.0f;				//プレイヤーを追従するスピード
//	static constexpr float ROTATE_SPEED = 1.5f;				//回転するスピード
//	static constexpr float FRONT_ANGLE = 0.9999f;			//正面方向の許容値(コサイン値)
//
//protected:
//	float walk_speed;
//	Vector2 charConScale;
//	std::unique_ptr<ModelInfo> model_info;
//	std::vector<std::unique_ptr<AnimInfo>> anim_info;
//
//public:
//	EnemyStatus(
//		ModelInfo modelInfo
//		, std::vector<std::unique_ptr<AnimInfo>> anim_infos
//		, const Vector2& charConScale
//		, float walkSpeed
//	) :
//		model_info(std::make_unique<ModelInfo>(modelInfo))
//		, anim_info(std::move(anim_infos))
//		, charConScale(charConScale)
//		, walk_speed(walkSpeed)
//	{
//		//anim_info.reserve(anim_infos.size());
//		//for (auto& anim : anim_infos) {
//		//	anim_info.emplace_back(std::make_unique<AnimInfo>(*anim));
//		//}
//	}
//
//	/**	キャラコンのスケールを取得*/
//	const Vector2& GetCharConScale()const { return charConScale; }
//	/**	歩行速度を取得*/
//	const float& GetWalkSpeed()const { return walk_speed; }
//	/** モデル情報を取得*/
//	const ModelInfo& GetModelInfo()const { return *model_info; }
//	/** アニメーション情報を取得*/
//	const AnimInfo& GetAnimInfo(size_t animIndex)const { 
//		return *anim_info.at(animIndex); 
//	}
//
//	/** アニメーションの数を取得 */
//	size_t GetAnimNum()const {
//		return anim_info.size();
//	}
//};


//struct NormalStatus : public EnemyStatus {
//private:
//	const std::string model_file_path =
//		nsAssetFilePath::asset_file_path
//		+ nsCharFilePath::model_path
//		+ nsAssetFilePath::char_type[EnCharType::enCharType_NormalEnemy]
//		+ nsCharFilePath::enemy_type[EnEnemyType::enEnemyType_Normal]
//		+ nsCharFilePath::model_extension;
//
//	const std::string anim_file_path =
//		nsAssetFilePath::asset_file_path
//		+ nsAnimFilePath::anim_path
//		+ nsAssetFilePath::char_type[EnCharType::enCharType_NormalEnemy]
//		+ nsCharFilePath::enemy_type[EnEnemyType::enEnemyType_Normal]
//		+ nsAnimFilePath::anim_type[EnCharState::enCharState_Walk]
//		+ nsAnimFilePath::anim_file_extension;
//
//public:
//	NormalStatus() :
//		EnemyStatus(
//			ModelInfo(model_file_path),
//			std::move(std::make_unique<AnimInfo>(anim_file_path, 1.3f, true)),
//
//			Vector2(15.0f, 60.0f),
//			50.0f
//		)
//	{
//	}
//};