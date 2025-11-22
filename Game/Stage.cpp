#include "stdafx.h"
#include "Stage.h"


bool First::Start(){
	SetStage("firstStage/ground/firstStageGround");
	return true;
}


void First::Update() {}


void First::Render(RenderContext& rc) {
	if (GetModelRender()) m_modelRender.Draw(rc);
}



bool GoalPole::Start() {
	SetStage("goalPole/goalPole");

	//“–‚½‚è”»’è‚Ìì¬
	m_collisionObject = new CollisionObject;
	m_collisionObject->CreateCapsule(m_transform.position, m_transform.rotation, 10.0f, 30.0f);
	if (!m_collisionObject) return false;
	return true;
}


void GoalPole::Update() {

}


void GoalPole::Render(RenderContext& rc) {
	if (&m_modelRender) m_modelRender.Draw(rc);
}