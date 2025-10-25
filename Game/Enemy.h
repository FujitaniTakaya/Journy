#pragma once
#include <coroutine>
#include <optional>
#include "stdint.h"

class Enemy : public IGameObject{
protected:
	void Update()override;
	void UpdateEnemyPos();

	void Render(RenderContext& rc)override;

	void SetEnemyModel(const int enemyNum);
	bool IsModel(const ModelRender* model);


	//エネミーをランダムに動かす
	void RandomWalk();
	void RandomWait(std::atomic<bool>& waitFlag);

	//目的地の方向を向いているかどうか
	bool IsRotateMovePos();
	//目的地にいるかどうか
	bool IsBeingMovePos()const;
	//次の目的地を決める
	void DecideToMovePos();


private:
/// <summary>
/// /ゲッター
/// </summary>
	
	
	const bool IsWait()const;		//今待っているかどうか

	const Vector3* GetPosition()const;




private:
	//待機時間のタイマーをスタートする
	void StartWaitTime(std::atomic<bool>& waitFlag);

public:
	enum class EnEnemy : uint8_t
	{
		enEnemy_Normal,
		enEnemy_Gimmick,
		enEnemy_Boss,
		enEnemy_Num
	};
	SpriteRender a[static_cast<int>(EnEnemy::enEnemy_Num)];
private:
	std::atomic<bool> m_isWait = true;

protected:
	ModelRender* m_enemyModelRender = nullptr;
	Vector3 m_firstEnemyPos = Vector3::Zero;
	Vector3 m_enemyPos = Vector3::Zero;
	Vector3 m_moveSpeed =  Vector3::Zero;	
	Vector3 m_toMovePos = Vector3::Zero;
	Quaternion m_enemyRotate = Quaternion::Identity;
	CharacterController m_enemyCharaCon;
};

class Normal : public Enemy {
public:
	bool Start()override;
};

class Gimmick : public Enemy {
public:
	bool Start()override;
};

class Boss : public Enemy {
public:
	bool Start()override;
};