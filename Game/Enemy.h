#pragma once
#include "Character.h"
#include "Status.h"
#include <coroutine>
#include <optional>


//class Player;
//
//class Enemy : public IGameObject{
//public:
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~Enemy();
//	/// <summary>
//	///　更新処理
//	/// 毎フレーム実行される
//	/// </summary>
//	void Update()override;	
//	/// <summary>
//	/// 描画処理
//	/// 毎フレーム実行される
//	/// </summary>
//	/// <param name="rc"></param>
//	void Render(RenderContext& rc)override;
//
//
//protected:
//	/// <summary>
//	/// 他クラスの情報を取得する
//	/// </summary>
//	void GetOtherClassInfo();
//
//
//protected:
//	/// <summary>
//	/// エネミーの情報を更新する
//	/// </summary>
//	void UpdateEnemyInfo();
//	/// <summary>
//	/// エネミーのモデルを初期化する
//	/// 引数に初期化したいエネミーの種類番号を渡す
//	/// </summary>
//	/// <param name="enemyNum">エネミー番号</param>
//	void SetEnemyModel(const int enemyNum);
//	/// <summary>
//	/// モデルがあるかどうか判定
//	/// nullチェック
//	/// </summary>
//	/// <param name="model">調べたいモデルのポインタ</param>
//	/// <returns>nullptrでなければtrueを返す</returns>
//	bool IsModel(const ModelRender* model);
//	
//	
//private:
//	/// <summary>
//	/// エネミーの行動処理
//	/// </summary>
//	void Move();
//
//
//protected:
//	/// <summary>
//	/// ランダムウォーク
//	/// </summary>
//	void RandomWalkAround();
//
//
//protected:
//	/// <summary>
//	/// 次の目的地の方向を向く
//	/// </summary>
//	void RotToMoveDirection();
//
//
//private:
//	/// <summary>
//	/// 次の目的地を決定する
//	/// </summary>
//	void DecideToMovePos();
//
//
//private:
//	/// <summary>
//	/// 待機処理を開始する
//	/// </summary>
//	/// <param name="waitFlag">待機フラグを代入</param>
//	void StartWaitTime(std::atomic<bool>& waitFlag);
//	/// <summary>
//	/// ランダムな時間で待機する
//	/// </summary>
//	/// <param name="waitFlag">待つかどうかを管理するフラグを代入</param>
//	void RandomWait(std::atomic<bool>& waitFlag);
//
//
//protected:
//	/// <summary>
//	/// 目的地の方向を向いているかどうか
//	/// </summary>
//	/// <returns>目的地の方向を向いていればenEnemyRot_Noneを返す</returns>
//	const EnEnemyRot WhichRotateMovePos();
//	/// <summary>
//	/// 次の目的地にいるかどうか
//	/// </summary>
//	/// <returns>目的地に到着していればtrueを返す</returns>
//	bool IsBeingToMovePos()const;
//	
//
//private:
//	/// <summary>
//	/// 待機中かどうか
//	/// </summary>
//	/// <returns>待機中であればtrueを返す</returns>
//	const bool IsWait()const;
//	/// <summary>
//	/// エネミーの現在地を取得する
//	/// </summary>
//	/// <returns></returns>
//	const Vector3* GetPosition()const;
//
//
//protected:
//	/// <summary>
//	///	プレイヤーを発見したかどうか
//	/// </summary>
//	/// <returns>発見していたらtrueを返す</returns>
//	const bool IsFoundPlayer();
//	/// <summary>
//	/// プレイヤーを追従する
//	/// </summary>
//	void ChasePlayer();
//
//protected:
//	/// <summary>
//	/// 次の目的地へのベクトルを可視化
//	/// </summary>
//	void DrawVectorToMovePos();
//	/// <summary>
//	/// エネミーのモデルの前方向ベクトルを可視化
//	/// </summary>
//	void DrawVectorFront();
//
//
//private:
//	/// <summary>
//	/// プレイヤーの攻撃コリジョンに当たっているかどうか
//	/// </summary>
//	/// <returns>当たっていたらtrueを返す</returns>
//	const bool IsHitPlayerAtkCollision();
//	/// <summary>
//	/// 自身が死亡する処理
//	/// </summary>
//	void Death();
//	/// <summary>
//	/// プレイヤー自身に当たったかどうか
//	/// </summary>
//	/// <returns>当たっていたらtrueを返す</returns>
//	const bool IsHitPlayerCharaConCollision();
//	/// <summary>
//	/// プレイヤーを倒す処理
//	/// </summary>
//	void KillPlayer();
//
//
//private:
//
//	inline const EnEnemy& GetEnemyType()const;
//
//
//protected:
//	Player* m_player = nullptr;								//プレイヤーのポインタ
//
//
//private:
//	std::atomic<bool> m_isWait = true;						//待機中かどうかのフラグ
//
//	EnEnemy m_enemyType = EnEnemy::enEnemy_Num;				//エネミーの種類
//
//protected:
//	ModelRender* m_enemyModelRender = nullptr;				//エネミーのモデルを格納するポインタ
//	Vector3 m_firstEnemyPos = Vector3::Zero;				//初期座標(スポーン地点)
//	Vector3 m_enemyPos = Vector3::Zero;						//現在座標
//	Vector3 m_moveSpeed = Vector3::Zero;					//移動速度
//	Vector3 m_toMovePos = Vector3::Zero;					//次の目的地
//	Quaternion m_enemyRotate = Quaternion::Identity;		//回転情報
//	CharacterController m_enemyCharaCon;					//キャラコン(当たり判定)
//};
//
//class Normal : public Enemy {
//public:
//	/// <summary>
//	/// ノーマルエネミーのスタート処理
//	/// </summary>
//	/// <returns></returns>
//	bool Start()override;
//};
//
//class Gimmick : public Enemy {
//public:
//	/// <summary>
//	/// ギミックエネミーのスタート処理
//	/// </summary>
//	/// <returns></returns>
//	bool Start()override;
//};
//
//class Boss : public Enemy {
//public:
//	/// <summary>
//	/// ボスエネミーのスタート処理
//	/// </summary>
//	/// <returns></returns>
//	bool Start()override;
//};


class Player;

class Enemy : public Character {
private:
	Player* m_player = nullptr;								//プレイヤーのポインタ

	EnemyStatus m_status;

protected:	
	Vector3 m_toMovePos = Vector3::Zero;
	EnEnemy m_enemyType = EnEnemy::enEnemy_Num;
	EnEnemyRot m_enemyRotDir = EnEnemyRot::enEnemyRot_Num;
	bool m_isWait = true;



public:
	Enemy() {}
	~Enemy() {}
	virtual bool Start()override { return true; }
	virtual void Update() override {};
	void Render(RenderContext& rc)override;

	/**	それぞれのスタート処理で呼び出す関数*/
protected:
	void InitializeCharacter() override;


	/**	初期化する関数たち*/
private:
	void InitializeModel();

	void InitializeCollisionObject();

protected:
	inline void SetEnemyType(const EnEnemy enemyType) { m_enemyType = enemyType; }
	inline const EnEnemy& GetEnemyType()const { return m_enemyType; }


	/**	エネミーの行動処理*/
protected:
	void Move();

	/**	ランダムウォーク系処理*/
private:
	void RandomWalk();

	inline void DecideToMovePos() {
		m_toMovePos.x = rand() % 401 - 200;
		m_toMovePos.z = rand() % 401 - 200;
		m_toMovePos += GetFirstPosition();
		m_toMovePos.y = 0.0f;
	}

	inline void RandomWait() {
		m_isWait= true;
		int waitTime = rand() % 3001 + 300;
		std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
		m_isWait = false;
	}


	/**	プレイヤーに追従*/
private:
	void ChasePlayer();


	/** ランダムウォークフラグゲッター・セッター*/
private:
	inline bool IsBeingToMovePos()const {
		Vector3 dif = m_toMovePos - m_position;
		if (dif.Length() >= m_status.GetWalkSpeed(m_enemyType) * 1.2) return false;

		return true;
	}

	inline const bool IsWait()const { return m_isWait; }
};


class Normal : public Enemy {
public:
	bool Start()override;
	void Update()override;
};

class Gimmick : public Enemy {
public:
	bool Start()override;
	void Update()override;
};

class Boss : public Enemy {
public:
	bool Start()override;
	void Update()override;
};