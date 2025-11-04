#pragma once
#include "Text.h"
#include <coroutine>
#include <optional>

class Player : public IGameObject{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();
	/// <summary>
	/// 更新処理
	/// 毎フレーム実行される
	/// </summary>
	void Update()override;
	/// <summary>
	/// 描画処理
	/// 毎フレーム実行される
	/// </summary>
	/// <param name="rc">レンダーコンテキスト</param>
	void Render(RenderContext& rc)override;
	

private:
	/// <summary>
	/// スティック入力があるかどうか
	/// </summary>
	/// <param name="stick">調べたいスティックを代入</param>
	/// <returns>スティック入力があればtrueを返す</returns>
	bool IsStick(const Vector2& stick);
	/// <summary>
	/// 移動しているかどうか
	/// </summary>
	/// <returns>移動中であればtrueを返す</returns>
	bool IsMove();
	/// <summary>
	/// 走っているかどうか
	/// </summary>
	/// <returns>走っていればtrueを返す</returns>
	bool IsRun();
	
	/// <summary>
	/// 重力を取得する
	/// 毎フレーム加算される（重力加速）
	/// </summary>
	/// <returns>現在の重力を返す</returns>
	float Gravity();
	/// <summary>
	/// ジャンプ可能な状態かどうか
	/// </summary>
	/// <returns>可能であればtrueを返す</returns>
	bool CanJump();	
	/// <summary>
	/// 次の段階のジャンプが可能かどうか
	/// </summary>
	/// <returns>可能であればtrueを返す</returns>
	bool CanNextPowerJump();
	/// <summary>
	/// 次の段階のジャンプが不可能になるまでの時間を計測
	/// </summary>
	/// <returns>時間が経ったらtrueを返す</returns>
	bool MeasureNextJumpFrameCount();
	

	/// <summary>
	/// プレイヤーのモデルをセットする
	/// </summary>
	void SetPlayerModel();
	/// <summary>
	/// 攻撃の当たり判定をセット
	/// </summary>
	void SetAtkCollision();
	/// <summary>
	/// ステート管理
	/// </summary>
	void ManagePlayerState();
	/// <summary>
	/// 攻撃判定の情報を更新
	/// </summary>
	void UpdateAtkCollisionInfo();
	/// <summary>
	/// 位置更新
	/// </summary>
	void UpdateCharaInfo();
	/// <summary>
	/// ジャンプの処理
	/// </summary>
	void Jump();
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 回転させる
	/// </summary>
	void Rotate();
	/// <summary>
	/// ジャンプ攻撃処理
	/// </summary>
	void JumpAtk();


public:
	/// <summary>
	/// プレイヤーの攻撃コリジョンを取得する
	/// </summary>
	/// <returns>コリジョンのポインタを返す</returns>
	CollisionObject* GetAtkCollision()const;


public:
	/// <summary>
	/// プレイヤーの現在地を取得する
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition()const;


public:
	enum EnPlayerMoveState {
		enPlayerMoveState_Walk,
		enPlayerMoveState_Run,
		enPlayerMoveState_Num
	};

	enum EnJumpPower {
		enJumpPower_First,
		enJumpPower_Second,
		enJumpPower_Third,
		enJumpPower_Num
	};

private:
	ModelRender* m_playerModelRender = nullptr;
	AnimationClip m_playerAnimClips[enPlayerState_Num];
	CharacterController m_playerCharaCon;
	CollisionObject* m_playerAtkCollision = nullptr;


private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;	
	Quaternion m_rotation = Quaternion::Identity;
	int m_moveState = enPlayerMoveState_Walk;
	int m_playerState = enPlayerState_Num;

	int m_jumpState = enJumpPower_First;
	float m_flyingTime = 0.0f;
	float m_standingTime = 0.0f;
	bool m_canNextJump = false;

	bool m_isAtk = false;
};

