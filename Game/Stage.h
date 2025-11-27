#pragma once
#include "Actor.h"

class Enemy;

class Stage : public Actor{
protected:
	PhysicsStaticObject m_stagePhysics;
	Enemy* m_enemy = nullptr;


public:
	Stage(){}
	virtual ~Stage() {}
	virtual bool Start()override { return true; }
	virtual void Update()override{}
	virtual void Render(RenderContext& rc)override{}

protected:
	inline void SetStage(const std::string filePath) {
		m_modelRender.Init(("Assets/stage/" + filePath + ".tkm").c_str());
		m_modelRender.SetTRS(m_transform.position, m_transform.rotation, m_transform.scale);
		m_modelRender.Update();
		m_stagePhysics.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	}
};


class First : public Stage {
public:
	First(){}
	~First()override{}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;	
};


class GoalPole : public Stage {
private:
	CollisionObject* m_collisionObject = nullptr;


public:
	GoalPole(){}
	~GoalPole()override{}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};