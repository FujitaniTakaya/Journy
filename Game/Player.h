#pragma once
#include "Character.h"
#include "Status.h"

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



/**
* @brief プレイヤークラス
*/
class Player : public Character {
private:
	std::unique_ptr<PlayerStatus> m_status;
	std::array<AnimationClip, static_cast<size_t>(EnCharState::enCharState_Num)> m_animationClips;
	EnCharState m_state = EnCharState::enCharState_Idle;
	EnMoveState m_moveState = EnMoveState::enMoveState_Walk;
	EnJumpPower m_jumpPowerState = EnJumpPower::enJumpPower_First;
	CollisionObject* m_atkCollision = nullptr;

	bool m_isKillEnemy = false;
	bool m_isNearCamera = false;


public:
	Player() : m_status(std::make_unique<PlayerStatus>()) {}
	~Player(){}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;



	
public:
	//ゲッター・セッター系
	inline CollisionObject* GetAtkCollision()const { return m_atkCollision; }

	inline void SetIsKillEnemy(const bool isKill) { m_isKillEnemy = isKill; }

	inline void SetIsNearCamera(const bool isNear) { m_isNearCamera = isNear; }


	inline PlayerStatus* GetStatus()const { return m_status.get(); }





/** このクラスの中だけで使う	*/

	/**	モデルの初期化	*/
private:
	void InitializeCharacter()override;
	void InitializeModel();	
	void InitializeCollisionObject();
	void InitializeStatusInfo();


	/**	攻撃コリジョン情報更新	*/
	inline void UpdateAtkCollisionInfo() {
		m_atkCollision->SetPosition(m_position);
		m_atkCollision->SetRotation(m_rotation);
		m_atkCollision->Update();
	}


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