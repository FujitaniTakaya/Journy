#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"


GameCamera::GameCamera() {
	m_player = FindGO<Player>("player");

	m_toCameraPos.Set(0.0f, 125.0f, -125.0f);
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(10000.0f);
}


GameCamera::~GameCamera() {
	m_player = nullptr;
}


void GameCamera::Update() {
	Vector3 target = m_player->m_position;
	target.y += 80.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	Vector2 stickR = { Vector2::Zero };
	stickR.x = g_pad[0]->GetRStickXF();
	stickR.y = g_pad[0]->GetRStickYF();

	//YŽ²Žü‚è‚Ì‰ñ“]
	Quaternion qRot = { Quaternion::Identity };
	qRot.SetRotationDeg(Vector3::AxisY, 1.3f * stickR.x);
	qRot.Apply(m_toCameraPos);

	//XŽ²Žü‚è‚Ì‰ñ“]
	Vector3 axisX = { Vector3::Zero };
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.3f * stickR.y);
	qRot.Apply(m_toCameraPos);
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	
	
	if (toPosDir.y < -0.2f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.9f) {
		m_toCameraPos = toCameraPosOld;
	}

	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(pos);
	g_camera3D->Update();
}