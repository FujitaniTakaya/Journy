#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"


void GameCamera::SetCamera(const CameraInfo& camera) {
	m_toCameraPos.Set(camera.toCameraPos);
	m_springCamera.Init(
		*g_camera3D,
		camera.maxCameraSpeed,
		true,
		camera.cameraCollisionScl
		);
}


GameCamera::GameCamera() {
	m_player = FindGO<Player>("player");
	SetCamera(cameraInfo);
}


GameCamera::~GameCamera() {
	m_player = nullptr;
}


void GameCamera::Update() {
	Vector3 target = m_player->m_position;
	target.y += 80.0f;
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	Vector2 stickR = Vector2::Zero;
	stickR.x = g_pad[0]->GetRStickXF();
	stickR.y = g_pad[0]->GetRStickYF();

	//YŽ²Žü‚è‚Ì‰ñ“]
	Quaternion qRot = Quaternion::Identity;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * stickR.x);
	qRot.Apply(m_toCameraPos);

	//XŽ²Žü‚è‚Ì‰ñ“]
	Vector3 axisX = Vector3::Zero;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 2.0f * stickR.y);
	qRot.Apply(m_toCameraPos);
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	
	
	if (toPosDir.y < -0.5f) {
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		m_toCameraPos = toCameraPosOld;
	}

	Vector3 pos = target + m_toCameraPos;

	m_springCamera.SetTarget(target);
	m_springCamera.SetPosition(pos);
	m_springCamera.Update();
}