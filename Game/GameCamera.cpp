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
	m_springCamera.SetNear(1.0f);
	m_springCamera.SetFar(10000000000.0f);
}


GameCamera::GameCamera() {
	m_player = FindGO<Player>("player");
	SetCamera(cameraInfo);
}


GameCamera::~GameCamera() {
	m_player = nullptr;
}


void GameCamera::Update() {
	if (!m_player) return;
	Vector3 target = m_player->GetTRSIns().GetPosition();
	target.y += 80.0f;
	target += g_camera3D->GetForward() * 40.0f;

	Vector3 toCameraPosOld = m_toCameraPos;

	Vector2 stickR = Vector2::Zero;
	stickR.x = g_pad[0]->GetRStickXF();
	stickR.y = g_pad[0]->GetRStickYF();

	//Y軸周りの回転
	Quaternion qRot = Quaternion::Identity;
	qRot.SetRotationDeg(Vector3::AxisY, 2.0f * stickR.x);
	qRot.Apply(m_toCameraPos);

	//X軸周りの回転
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

	IsNearPlayer();
}


void GameCamera::IsNearPlayer()  {
	if (!m_player) return;
	Vector3 cameraPos = g_camera3D->GetPosition();
	Vector3 playerPos = m_player->GetTRSIns().GetPosition();
	//プレイヤーからカメラのベクトルを取り、距離を計算
	float dis = (cameraPos - playerPos).Length();
	//距離が100未満であれば近い
	bool isNear = true;
	if (dis < 100.0f) {
		m_player->SetIsNearCamera(isNear);
	}
	else {
		m_player->SetIsNearCamera(!isNear);
	}
}