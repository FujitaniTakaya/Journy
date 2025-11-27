#pragma once
#include "Enemy.h"
#include "ActorStatus.h"

class NormalEnemy :  public Enemy{
private:
	NormalEnemyStatus* m_normalEnemyStatus = nullptr;


public:
	NormalEnemy();
	~NormalEnemy() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;


private:
	//** アニメーションの初期化 */
	virtual void LoadAnimationClips();
	/** モデルの初期化 */
	virtual void SetUpModel();


private:
	void Move()override;
	

	/**	ランダムウォーク*/
	void RandomWalkAround();

	/** 次の目的地を決める*/
	void DecideToMovePos();


	void RandomWait(std::atomic<bool>& waitFlag);


	bool IsBeingToMovePos()const;

	inline const bool IsWait()const { return m_isWait; }
};

