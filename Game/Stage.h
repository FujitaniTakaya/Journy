#pragma once

class Enemy;

class Stage : public IGameObject{
protected:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rotation =Quaternion::Identity;
	ModelRender m_modelRender;
	PhysicsStaticObject m_stagePhysics;
	Enemy* m_enemy = nullptr;


public:
	Stage(){}
	virtual ~Stage() {}
	virtual bool Start()override = 0;
	virtual void Update()override = 0;
	virtual void Render(RenderContext& rc)override = 0;


public:
	inline void SetPosition(const Vector3& pos) { m_position = pos; }
	inline void SetScale(const Vector3& scl) { m_scale = scl; }
	inline void SetRotation(const Quaternion& rot) { m_rotation = rot; }


	inline void SetTRS(const Vector3& pos, const Quaternion& rot, const Vector3& scl) {
		m_position = pos;
		m_scale = scl;
		m_rotation = rot;
	}

	inline ModelRender* GetModelRender() { return &m_modelRender; }


protected:
	inline void SetStage(const std::string filePath) {
		m_modelRender.Init(("Assets/stage/" + filePath + ".tkm").c_str());
		m_modelRender.SetTRS(m_position, m_rotation, m_scale);
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



//class StageGroundParts : public Stage {
//public:
//	StageGroundParts(){}
//	~StageGroundParts(){}
//	bool Start()override;
//	void Update()override;
//	void Render(RenderContext& rc)override;
//};
//
//
//
//class StageGroundPartsDiagonalOnHalf : public Stage {
//public:
//	StageGroundPartsDiagonalOnHalf(){}
//	~StageGroundPartsDiagonalOnHalf(){}
//	bool Start()override;
//	void Update()override;
//	void Render(RenderContext& rc)override;	
//};
//
//
//
//class StageHoveringGround : public Stage {
//	public:
//	StageHoveringGround(){}
//	~StageHoveringGround(){}
//	bool Start()override;
//	void Update()override;
//	void Render(RenderContext& rc)override;
//};
//


class GoalPole : public Stage {
public:
	GoalPole(){}
	~GoalPole(){}
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;

private:


private:
	CollisionObject* m_collisionObject = nullptr;
};