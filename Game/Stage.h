#pragma once
class Stage : public IGameObject{
public:
	Stage();
	void Render(RenderContext& rc)override;

private:
	void SetStage();

private:
	PhysicsStaticObject m_stagePhysics;

	ModelRender* m_stageModelRender = nullptr;
};

