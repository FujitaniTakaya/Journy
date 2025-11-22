#pragma once
#include "camera/SpringCamera.h"
#include "Actor.h"


namespace {
	struct CameraInfo {
		Vector3 toCameraPos;
		float cameraRotateSpeed;
		float maxCameraSpeed;
		float cameraCollisionScl;
	};	

	const CameraInfo cameraInfo = {
		{0.0f, 125.0f,500.0f}, 2.0f, 1000.0f, 5.0f
	};
}

class Player;

class GameCamera : public Actor{
private:
	Player* m_player = nullptr;
	Vector3 m_toCameraPos = Vector3::Zero;
	SpringCamera m_springCamera;


public:
	GameCamera();
	~GameCamera();
	bool Start()override { return true; }
	void Update()override;
	void Render(RenderContext& rc)override {}

private:
	void SetCamera(const CameraInfo& camera);

	void IsNearPlayer();
};

