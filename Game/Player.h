#pragma once
#include "Text.h"


class Player : public IGameObject{
public:
	Player();
	~Player();
	void Render(RenderContext& rc)override;
	void Update()override;

private:
	bool IsStick(const Vector2& stick);
	bool IsMove();
	bool IsRun();
	
	float Gravity();
	bool CanJump();	
	bool CanNextJump();
	bool MeasureNextJumpFrameCount();
	

	void SetPlayerModel();
	void ManagePlayerState();


	void Jump();
	void Move();
	void Rotate();
private:
	ModelRender* m_playerModelRender = nullptr;
	AnimationClip m_playerAnimClips[enPlayerState_Num];
	CharacterController m_playerCharaCon;


	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	
	int m_jumpState = enJumpPower_First;
	float m_flyingTime = 0.0f;
	float m_standingTime = 0.0f;
	bool m_canNextJump = true;

	int m_playerState = enPlayerState_Idle;
};

