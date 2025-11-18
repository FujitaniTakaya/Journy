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
//	/// ƒfƒXƒgƒ‰ƒNƒ^
//	/// </summary>
//	~Enemy();
//	/// <summary>
//	///@XVˆ—
//	/// –ˆƒtƒŒ[ƒ€Às‚³‚ê‚é
//	/// </summary>
//	void Update()override;	
//	/// <summary>
//	/// •`‰æˆ—
//	/// –ˆƒtƒŒ[ƒ€Às‚³‚ê‚é
//	/// </summary>
//	/// <param name="rc"></param>
//	void Render(RenderContext& rc)override;
//
//
//protected:
//	/// <summary>
//	/// ‘¼ƒNƒ‰ƒX‚Ìî•ñ‚ğæ“¾‚·‚é
//	/// </summary>
//	void GetOtherClassInfo();
//
//
//protected:
//	/// <summary>
//	/// ƒGƒlƒ~[‚Ìî•ñ‚ğXV‚·‚é
//	/// </summary>
//	void UpdateEnemyInfo();
//	/// <summary>
//	/// ƒGƒlƒ~[‚Ìƒ‚ƒfƒ‹‚ğ‰Šú‰»‚·‚é
//	/// ˆø”‚É‰Šú‰»‚µ‚½‚¢ƒGƒlƒ~[‚Ìí—Ş”Ô†‚ğ“n‚·
//	/// </summary>
//	/// <param name="enemyNum">ƒGƒlƒ~[”Ô†</param>
//	void SetEnemyModel(const int enemyNum);
//	/// <summary>
//	/// ƒ‚ƒfƒ‹‚ª‚ ‚é‚©‚Ç‚¤‚©”»’è
//	/// nullƒ`ƒFƒbƒN
//	/// </summary>
//	/// <param name="model">’²‚×‚½‚¢ƒ‚ƒfƒ‹‚Ìƒ|ƒCƒ“ƒ^</param>
//	/// <returns>nullptr‚Å‚È‚¯‚ê‚Îtrue‚ğ•Ô‚·</returns>
//	bool IsModel(const ModelRender* model);
//	
//	
//private:
//	/// <summary>
//	/// ƒGƒlƒ~[‚Ìs“®ˆ—
//	/// </summary>
//	void Move();
//
//
//protected:
//	/// <summary>
//	/// ƒ‰ƒ“ƒ_ƒ€ƒEƒH[ƒN
//	/// </summary>
//	void RandomWalkAround();
//
//
//protected:
//	/// <summary>
//	/// Ÿ‚Ì–Ú“I’n‚Ì•ûŒü‚ğŒü‚­
//	/// </summary>
//	void RotToMoveDirection();
//
//
//private:
//	/// <summary>
//	/// Ÿ‚Ì–Ú“I’n‚ğŒˆ’è‚·‚é
//	/// </summary>
//	void DecideToMovePos();
//
//
//private:
//	/// <summary>
//	/// ‘Ò‹@ˆ—‚ğŠJn‚·‚é
//	/// </summary>
//	/// <param name="waitFlag">‘Ò‹@ƒtƒ‰ƒO‚ğ‘ã“ü</param>
//	void StartWaitTime(std::atomic<bool>& waitFlag);
//	/// <summary>
//	/// ƒ‰ƒ“ƒ_ƒ€‚ÈŠÔ‚Å‘Ò‹@‚·‚é
//	/// </summary>
//	/// <param name="waitFlag">‘Ò‚Â‚©‚Ç‚¤‚©‚ğŠÇ—‚·‚éƒtƒ‰ƒO‚ğ‘ã“ü</param>
//	void RandomWait(std::atomic<bool>& waitFlag);
//
//
//protected:
//	/// <summary>
//	/// –Ú“I’n‚Ì•ûŒü‚ğŒü‚¢‚Ä‚¢‚é‚©‚Ç‚¤‚©
//	/// </summary>
//	/// <returns>–Ú“I’n‚Ì•ûŒü‚ğŒü‚¢‚Ä‚¢‚ê‚ÎenEnemyRot_None‚ğ•Ô‚·</returns>
//	const EnEnemyRot WhichRotateMovePos();
//	/// <summary>
//	/// Ÿ‚Ì–Ú“I’n‚É‚¢‚é‚©‚Ç‚¤‚©
//	/// </summary>
//	/// <returns>–Ú“I’n‚É“’…‚µ‚Ä‚¢‚ê‚Îtrue‚ğ•Ô‚·</returns>
//	bool IsBeingToMovePos()const;
//	
//
//private:
//	/// <summary>
//	/// ‘Ò‹@’†‚©‚Ç‚¤‚©
//	/// </summary>
//	/// <returns>‘Ò‹@’†‚Å‚ ‚ê‚Îtrue‚ğ•Ô‚·</returns>
//	const bool IsWait()const;
//	/// <summary>
//	/// ƒGƒlƒ~[‚ÌŒ»İ’n‚ğæ“¾‚·‚é
//	/// </summary>
//	/// <returns></returns>
//	const Vector3* GetPosition()const;
//
//
//protected:
//	/// <summary>
//	///	ƒvƒŒƒCƒ„[‚ğ”­Œ©‚µ‚½‚©‚Ç‚¤‚©
//	/// </summary>
//	/// <returns>”­Œ©‚µ‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·</returns>
//	const bool IsFoundPlayer();
//	/// <summary>
//	/// ƒvƒŒƒCƒ„[‚ğ’Ç]‚·‚é
//	/// </summary>
//	void ChasePlayer();
//
//protected:
//	/// <summary>
//	/// Ÿ‚Ì–Ú“I’n‚Ö‚ÌƒxƒNƒgƒ‹‚ğ‰Â‹‰»
//	/// </summary>
//	void DrawVectorToMovePos();
//	/// <summary>
//	/// ƒGƒlƒ~[‚Ìƒ‚ƒfƒ‹‚Ì‘O•ûŒüƒxƒNƒgƒ‹‚ğ‰Â‹‰»
//	/// </summary>
//	void DrawVectorFront();
//
//
//private:
//	/// <summary>
//	/// ƒvƒŒƒCƒ„[‚ÌUŒ‚ƒRƒŠƒWƒ‡ƒ“‚É“–‚½‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©
//	/// </summary>
//	/// <returns>“–‚½‚Á‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·</returns>
//	const bool IsHitPlayerAtkCollision();
//	/// <summary>
//	/// ©g‚ª€–S‚·‚éˆ—
//	/// </summary>
//	void Death();
//	/// <summary>
//	/// ƒvƒŒƒCƒ„[©g‚É“–‚½‚Á‚½‚©‚Ç‚¤‚©
//	/// </summary>
//	/// <returns>“–‚½‚Á‚Ä‚¢‚½‚çtrue‚ğ•Ô‚·</returns>
//	const bool IsHitPlayerCharaConCollision();
//	/// <summary>
//	/// ƒvƒŒƒCƒ„[‚ğ“|‚·ˆ—
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
//	Player* m_player = nullptr;								//ƒvƒŒƒCƒ„[‚Ìƒ|ƒCƒ“ƒ^
//
//
//private:
//	std::atomic<bool> m_isWait = true;						//‘Ò‹@’†‚©‚Ç‚¤‚©‚Ìƒtƒ‰ƒO
//
//	EnEnemy m_enemyType = EnEnemy::enEnemy_Num;				//ƒGƒlƒ~[‚Ìí—Ş
//
//protected:
//	ModelRender* m_enemyModelRender = nullptr;				//ƒGƒlƒ~[‚Ìƒ‚ƒfƒ‹‚ğŠi”[‚·‚éƒ|ƒCƒ“ƒ^
//	Vector3 m_firstEnemyPos = Vector3::Zero;				//‰ŠúÀ•W(ƒXƒ|[ƒ“’n“_)
//	Vector3 m_enemyPos = Vector3::Zero;						//Œ»İÀ•W
//	Vector3 m_moveSpeed = Vector3::Zero;					//ˆÚ“®‘¬“x
//	Vector3 m_toMovePos = Vector3::Zero;					//Ÿ‚Ì–Ú“I’n
//	Quaternion m_enemyRotate = Quaternion::Identity;		//‰ñ“]î•ñ
//	CharacterController m_enemyCharaCon;					//ƒLƒƒƒ‰ƒRƒ“(“–‚½‚è”»’è)
//};
//
//class Normal : public Enemy {
//public:
//	/// <summary>
//	/// ƒm[ƒ}ƒ‹ƒGƒlƒ~[‚ÌƒXƒ^[ƒgˆ—
//	/// </summary>
//	/// <returns></returns>
//	bool Start()override;
//};
//
//class Gimmick : public Enemy {
//public:
//	/// <summary>
//	/// ƒMƒ~ƒbƒNƒGƒlƒ~[‚ÌƒXƒ^[ƒgˆ—
//	/// </summary>
//	/// <returns></returns>
//	bool Start()override;
//};
//
//class Boss : public Enemy {
//public:
//	/// <summary>
//	/// ƒ{ƒXƒGƒlƒ~[‚ÌƒXƒ^[ƒgˆ—
//	/// </summary>
//	/// <returns></returns>
//	bool Start()override;
//};


class Player;

class Enemy : public Character {
private:
								//ƒvƒŒƒCƒ„[‚Ìƒ|ƒCƒ“ƒ^

	EnemyStatus m_status;

protected:	
	Player* m_player = nullptr;

	Vector3 m_toMovePos = Vector3::Zero;
	EnEnemy m_enemyType = EnEnemy::enEnemy_Num;
	std::atomic<bool> m_isWait = false;


public:
	Enemy() {}
	virtual ~Enemy(){}
	virtual bool Start()override = 0;
	virtual void Update() override = 0;
	virtual void Render(RenderContext& rc)override = 0;

	/**	‚»‚ê‚¼‚ê‚ÌƒXƒ^[ƒgˆ—‚ÅŒÄ‚Ño‚·ŠÖ”*/
protected:
	void InitializeCharacter() override;


	/**	‰Šú‰»‚·‚éŠÖ”‚½‚¿*/
private:
	void InitializeModel();

	void InitializeCollisionObject();

	void InitializeGetOtherClassInfo();


protected:
	inline void SetEnemyType(const EnEnemy enemyType) { m_enemyType = enemyType; }
	inline const EnEnemy& GetEnemyType()const { return m_enemyType; }


	/**	ƒGƒlƒ~[‚Ìs“®ˆ—*/
protected:
	void Move();


	/**	ƒvƒŒƒCƒ„[‚É’Ç]*/
	void ChasePlayer();

	/**	ƒ‰ƒ“ƒ_ƒ€ƒEƒH[ƒN*/
	void RandomWalkAround();

	/** Ÿ‚Ì–Ú“I’n‚ğŒˆ‚ß‚é*/
	inline void DecideToMovePos() {
		m_toMovePos.x = rand() % 601 - 300;
		m_toMovePos.z = rand() % 601 - 300;
		m_toMovePos += m_firstPos;
		m_toMovePos.y = m_firstPos.y;
	}

	inline std::thread waitThread() {
		this->RandomWait(m_isWait);
		return std::thread();
	}

	inline void RandomWait(std::atomic<bool>& waitFlag) {
		//ƒ‰ƒ“ƒ_ƒ€‚ÈŠÔ‘Ò‹@
		//300ms`3300ms
		int waitTime = rand() % 3001 + 300;
		std::this_thread::sleep_for(std::chrono::milliseconds(waitTime));
		waitFlag = false;
	}


	void Death();


	/** ƒtƒ‰ƒOƒQƒbƒ^[EƒZƒbƒ^[*/
private:
	inline bool IsBeingToMovePos()const {
		Vector3 dif = m_toMovePos - m_position;
		if (dif.Length() >= m_status.GetWalkSpeed(m_enemyType) * 1.2) {
			return false;
		}
		return true;
	}

	inline const bool IsWait()const { return m_isWait; }


	/**	ƒvƒŒƒCƒ„[‚ğŒ©‚Â‚¯‚½‚©‚Ç‚¤‚©*/
	const bool IsFoundPlayer();

	/**	ƒvƒŒƒCƒ„[“¥‚Ü‚ê‚½‚©‚Ç‚¤‚©*/
	bool IsStompedByPlayer();


protected:
	// ï¿½fï¿½oï¿½bï¿½Oï¿½p
	void DrawVectorToMovePos();

	void DrawVectorFront();
};


class Normal : public Enemy {
public:
	~Normal() override{
		DeleteCollision();
	}
	bool Start()override;
	void Update()override;
};

class Gimmick : public Enemy {
public:
	~Gimmick() override{
		DeleteCollision();
	}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {}
};

class Boss : public Enemy {
public:
	~Boss() override{
		DeleteCollision();
	}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {}
};