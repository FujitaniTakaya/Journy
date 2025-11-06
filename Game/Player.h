#pragma once
#include "Character.h"


//#include "Text.h"
//#include <coroutine>
//#include <optional>
//
//
//enum EnPlayerMoveState {
//	enPlayerMoveState_Walk,
//	enPlayerMoveState_Run,
//	enPlayerMoveState_Num
//};
//
//enum EnJumpPower {
//	enJumpPower_First,
//	enJumpPower_Second,
//	enJumpPower_Third,
//	enJumpPower_Num
//};
//
//
//class Player : public IGameObject{
//public:
//	/// <summary>
//	/// コンストラクタ
//	/// </summary>
//	Player();
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~Player();
//	/// <summary>
//	/// 更新処理
//	/// 毎フレーム実行される
//	/// </summary>
//	void Update()override;
//	/// <summary>
//	/// 描画処理
//	/// 毎フレーム実行される
//	/// </summary>
//	/// <param name="rc">レンダーコンテキスト</param>
//	void Render(RenderContext& rc)override;
//	
//
///////////////////////////////////////////
///// 移動関連のフラグゲッター関数
///////////////////////////////////////////
//
//private:
//	/// <summary>
//	/// スティック入力があるかどうか
//	/// </summary>
//	/// <param name="stick">調べたいスティックを代入</param>
//	/// <returns>スティック入力があればtrueを返す</returns>
//	bool IsStick(const Vector2& stick);
//	/// <summary>
//	/// 移動しているかどうか
//	/// </summary>
//	/// <returns>移動中であればtrueを返す</returns>
//	bool IsMove();
//	/// <summary>
//	/// 走っているかどうか
//	/// </summary>
//	/// <returns>走っていればtrueを返す</returns>
//	bool IsRun();
//	
//
//
////////////////////////////////////////////
///// ジャンプ関連のフラグゲッター関数
////////////////////////////////////////////
//
//private:
//	/// <summary>
//	/// 重力を取得する
//	/// 毎フレーム加算される（重力加速）
//	/// </summary>
//	/// <returns>現在の重力を返す</returns>
//	float Gravity();
//	/// <summary>
//	/// ジャンプ可能な状態かどうか
//	/// </summary>
//	/// <returns>可能であればtrueを返す</returns>
//	bool CanJump();	
//	/// <summary>
//	/// 次の段階のジャンプが可能かどうか
//	/// </summary>
//	/// <returns>可能であればtrueを返す</returns>
//	bool CanNextPowerJump();
//	/// <summary>
//	/// 次の段階のジャンプが不可能になるまでの時間を計測
//	/// </summary>
//	/// <returns>時間が経ったらtrueを返す</returns>
//	bool MeasureNextJumpFrameCount();
//
//
///////////////////////////////////////////
///// 戦闘関連のフラグゲッター関数
///////////////////////////////////////////
//
//private:
//	/// <summary>
//	/// 敵を倒した直後かどうか
//	/// </summary>
//	/// <returns>倒した直後であればtrueを返す</returns>
//	inline const bool IsKillEnemy()const;
//	/// <summary>
//	/// 現在無敵かどうか判定
//	/// </summary>
//	/// <returns>無敵であればtrueを返す</returns>
//	const bool IsInvincible()const;
//
//
////////////////////////////////////////////
///// 初期化用セッター関数
////////////////////////////////////////////
//
//private:
//	/// <summary>
//	/// プレイヤーのモデルをセットする
//	/// </summary>
//	void SetPlayerModel();
//	/// <summary>
//	/// 攻撃の当たり判定をセット
//	/// </summary>
//	void SetAtkCollision();
//	/// <summary>
//	/// プレイヤー自身の当たり判定をセット
//	/// </summary>
//	void SetCharaConCollision();
//	/// <summary>
//	/// 残機と無敵情報をセット
//	/// </summary>
//	void SetLifeAndInvincibleInfo();
//
//
////////////////////////////////////////////
///// プレイヤー情報更新用関数
////////////////////////////////////////////
//
//private:
//	
//	/// <summary>
//	/// 攻撃判定の情報を更新
//	/// </summary>
//	void UpdateAtkCollisionInfo();
//	/// <summary>
//	/// プレイヤー自身の当たり判定の情報を更新
//	/// </summary>
//	void UpdateCharaConCollisionInfo();
//	/// <summary>
//	/// 位置更新
//	/// </summary>
//	void UpdateCharaPos();
//
//
///////////////////////////////////////////
///// プレイヤー動作処理関数
///////////////////////////////////////////
//
//private:
//	/// <summary>
//	/// ジャンプの処理
//	/// </summary>
//	void Jump();
//	/// <summary>
//	/// 移動処理
//	/// </summary>
//	void Move();
//	/// <summary>
//	/// 回転させる
//	/// </summary>
//	void Rotate();
//	/// <summary>
//	/// ジャンプ攻撃処理
//	/// </summary>
//	void JumpAtk();
//	/// <summary>
//	/// 敵を倒した後のジャンプ処理
//	/// </summary>
//	void JumpAfterKilledEnemy();
//	/// <summary>
//	/// ステート管理
//	/// </summary>
//	void ManagePlayerState();
//	/// <summary>
//	/// 無敵処理
//	/// </summary>
//	void Invincible();
//
//
////////////////////////////////////////////
///// プレイヤー情報ゲッター関数
////////////////////////////////////////////
//
//public:
//	/// <summary>
//	/// 攻撃コリジョンを取得する
//	/// </summary>
//	/// <returns>攻撃の当たり判定のポインタを返す</returns>
//	CollisionObject* GetAtkCollision()const;
//	/// <summary>
//	/// 自身の当たり判定を取得する
//	/// </summary>
//	/// <returns>プレイヤー自身の当たり判定のポインタを返す</returns>
//	CollisionObject* GetCharaConCollision()const;
//	/// <summary>
//	/// プレイヤーの現在地を取得する
//	/// </summary>
//	/// <returns></returns>
//	const Vector3& GetPosition()const;
//	
//
////////////////////////////////////////////
///// プレイヤー情報セッター関数
////////////////////////////////////////////
//
//public:
//	/// <summary>
//	///	敵を倒したフラグをセットする
//	/// </summary>
//	/// <param name="isKill">セットするフラグ</param>
//	void SetFlagIsKillEnemy(const bool isKill);
//	/// <summary>
//	/// ライフを減らす
//	/// </summary>
//	void ReducePlayerLife();
//		
//
//private:
//	ModelRender* m_playerModelRender = nullptr;
//	AnimationClip m_playerAnimClips[enPlayerState_Num];
//	CharacterController m_playerCharaCon;
//	CollisionObject* m_playerCharaConCollision = nullptr;
//	CollisionObject* m_playerAtkCollision = nullptr;
//
//
//private:
//	Vector3 m_position = Vector3::Zero;
//	Vector3 m_moveSpeed = Vector3::Zero;	
//	Quaternion m_rotation = Quaternion::Identity;
//	int m_moveState = enPlayerMoveState_Walk;
//	int m_playerState = enPlayerState_Num;
//
//private:
//	int m_jumpState = enJumpPower_First;
//	float m_flyingTime = 0.0f;
//	float m_standingTime = 0.0f;
//	bool m_canNextJump = false;
//
//private:
//	bool m_isAtk = false;
//	bool m_isKillEnemy = false;
//
//private:
//	int m_playerLife = 0;
//	bool m_isInvincible = false;
//	bool m_isDraw = false;
//	float m_invincibleFrameCount = 0.0f;
//};


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
};;


namespace PlayerInfo {
	//ファイルの場所
	const std::string PLAYER_FILEPATH = "Assets/animData/";
	//拡張子
	const std::string PLAYER_EXTENSTION = ".tka";

	struct PlayerAnimInfo {
		//ファイル名
		std::string fileName;

		float playAnimSpeed;

		//ファイルパスを取得
		std::string GetAnimFullPath()const {
			return PLAYER_FILEPATH + fileName + PLAYER_EXTENSTION;
		}
	};


	const PlayerAnimInfo playerInfo[enCharaState_Num] = {
		{"idle", 1.0f},
		{"walk", 1.2f},
		{"run", 1.5f},
		{"jump",1.0f},
	};

	const float ANIMATION_SPEED = 1.5f;

	const char* const UNITY_FILE_PATH = "Assets/modelData/unityChan.tkm";

	const Vector2 CHARA_CON = { 15.0f, 65.0f };
	const Vector3 START_POS = { 100.0f, 0.0f, 100.0f };


	namespace MoveInfo {
		const float MOVE_SPEED[enMoveState_Num] = {
			200.0f, 400.0f
		};
	}


	namespace JumpInfo {
		const float JUMP_POWER[enJumpPower_Num] = {
			200.0f, 400.0f, 600.0f
		};


		const float CAN_NEXT_JUMP_FRAME = 0.1f;					//次の段のジャンプに切り替えれるまでの猶予時間
		const float MAX_FLYING_TIME = 0.5f;						//重力加速の最大フレーム数
		const float GRAVITY = -49.0f;							//重力加速度
	}
}



/**
* @brief プレイヤークラス
*/
class Player : public Character {
private:
	AnimationClip m_animationClips[enCharaState_Num];
	EnCharaState m_state = enCharaState_Num;
	EnMoveState m_moveState = enMoveState_Num;
	EnJumpPower m_jumpPowerState = enJumpPower_First;

	float m_flyingTime = 0.0f;
	float m_standingTime = 0.0f;


public:
	Player(){}
	~Player(){}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;


	/** このクラスの中だけで使う	*/
private:
	/**	モデルの初期化	*/
	void InitializeModel();

	/**	モデル情報の更新	*/
	void UpdateTRSInfo();
	


	/**	行動系	*/
private:
	void Move();

	void Jump();
	
	inline void AddGravity() {
		//滞空時間を加算
		GameInfo::AddOneFrame(m_flyingTime);
		m_flyingTime = min(m_flyingTime, PlayerInfo::JumpInfo::MAX_FLYING_TIME);
		const float gravity = PlayerInfo::JumpInfo::GRAVITY * m_flyingTime;
		//重力加算
		AddMoveSpeedY(gravity);
	}

	inline void Rotate() {	
		m_rotation.SetRotationYFromDirectionXZ(GetMoveSpeed());
	}

	inline std::thread animationThread() {
		return std::thread([this]() {
			this->ManageStateAndAnimation();
			});
	}

	void ManageStateAndAnimation();

	/**	行動フラグ系	*/
private:

	inline bool IsRun() {
		if (!IsMove()) {
			return false;
		}
		if (!g_pad[0]->IsPress(enButtonA)) {
			return false;
		}
		return true;
	}

	bool CanNextJump();
};