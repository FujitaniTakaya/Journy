#pragma once
#include "Character.h"
#include "ActorStatus.h"
#include <coroutine>
#include <optional>


class Player;
class UI;

class Enemy : public Character {
protected:	
	Player* m_player = nullptr;
	UI* m_ui = nullptr;
	Vector3 m_toMovePos = Vector3::Zero;
	std::atomic<bool> m_isWait = false;


public:
	Enemy() {}
	virtual ~Enemy()override{}
	virtual bool Start()override { return true; }
	virtual void Update() override {}
	virtual void Render(RenderContext& rc)override {}

	/**	それぞれのスタート処理で呼び出す関数*/
protected:
	
	/** アニメーションの初期化 */
	virtual void LoadAnimationClips()override;
	/** モデルの初期化 */
	virtual void SetUpModel()override;

	void GetOtherClassInfo();


	/**	エネミーの行動処理*/
protected:
	virtual void Move() = 0;


	/**	プレイヤーに追従*/
	void ChasePlayer(CharacterStatus* status);	

	/** 死亡させる */
	void Death();


protected:
	/**	プレイヤーを見つけたかどうか*/
	const bool IsFoundPlayer();

	/**	プレイヤー踏まれたかどうか*/
	bool IsStompedByPlayer();


protected:
	// ・ｽf・ｽo・ｽb・ｽO・ｽp
	void DrawVectorToMovePos();

	void DrawVectorFront();
};


class Gimmick : public Enemy {
public:
	~Gimmick() override{
	}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {}


private:
	//void InitializeCharacter()override;
	void Move()override;
};


class Boss : public Enemy {
public:
	~Boss() override{
	}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {}


private:
	//void InitializeCharacter()override;
	void Move()override;
};