#include "stdafx.h"
#include "Stage.h"


Stage::Stage() {
	SetStage();
}

void Stage::Render(RenderContext& rc) {
	if (!m_stageModelRender) {
		return;
	}
	m_stageModelRender->Draw(rc);
}


void Stage::SetStage() {
	m_stageModelRender = new ModelRender;
	m_stageModelRender->Init("Assets/stage/Stage.tkm");
	m_stageModelRender->SetPosition(Vector3::Zero);

	ModelRender* model = m_stageModelRender;


	m_stagePhysics.CreateFromModel(model->GetModel(), model->GetModel().GetWorldMatrix());

	//“–‚½‚è”»’è‚Ì‰ÂŽ‹‰»
	PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_stageModelRender->Update();
}