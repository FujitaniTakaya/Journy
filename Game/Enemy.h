#pragma once
class Enemy : public IGameObject{
public:




protected:
	void Render(RenderContext& rc)override;

	void SetEnemyModel(int enemyNum);
	bool IsModel(ModelRender* model);


	void RandomWalk();


public:
	enum EnEnemy {
		enEnemy_Normal,
		enEnemy_Gimmick,
		enEnemy_Boss,
		enEnemy_Num
	};
	
protected:
	ModelRender* m_enemyModelRender = nullptr;

	Vector3 m_enemyPos = { Vector3::Zero };
	Vector3 m_moveSpeed = { Vector3::Zero };
	Quaternion m_enemyRotate{ Quaternion::Identity };
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