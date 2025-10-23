#pragma once
#include "camera/SpringCamera.h"



namespace {
	struct CameraInfo {
		Vector3 toCameraPos;
		float cameraRotateSpeed;
		float maxCameraSpeed;
		float cameraCollisionScl;
	};	

	const CameraInfo cameraInfo = {
		{0.0f, 125.0f, -125.0f}, 2.0f, 1000.0f, 5.0f
	};
}

class Player;

class GameCamera : public IGameObject{
public:
	GameCamera();
	~GameCamera();
	void Update()override;
	
private:
	void SetCamera(const CameraInfo& camera);

private:
	

	Player* m_player = nullptr;
	Vector3 m_toCameraPos = Vector3::Zero;
	SpringCamera m_springCamera;
};

