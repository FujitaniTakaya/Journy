#include "stdafx.h"
#include "ActorStatus.h"


ActorStatus::ActorStatus()
{
}


ActorStatus::~ActorStatus()
{
}


void ActorStatus::AddOneFrame(float& frameCount) {
	frameCount += one_frame;
}


void ActorStatus::ResetFlyingTime()
{
	m_flyingTime = 0.0f;
}


float ActorStatus::GetGravity() {
	AddOneFrame(m_flyingTime);
	m_flyingTime = std::min<float>(m_flyingTime, max_flying_time);
	return gravity * m_flyingTime * 2;
}


CharacterStatus::CharacterStatus(
	const int maxLife
	,const float walkSpeed
	,const float runSpeed
	) :
	m_maxLife(maxLife),
	m_life(maxLife),
	m_moveSpeed({
			walkSpeed, runSpeed
		})
{
}


CharacterStatus::~CharacterStatus()
{
}


const float& JumpInfo::GetJumpPower() const {
	return m_jumpPower;
}


const float& JumpInfo::GetJumpAnimSpeed() const {
	return m_jumpAnimSpeed;
}


PlayerStatus::PlayerStatus() :
	CharacterStatus(
		5,			//maxLife
		200.0f,		//walkSpeed
		500.0f		//runSpeed
	)

	,m_jumpInfo({
			{ 500.0f, 1.0f },
			{ 700.0f, 0.8f },
			{ 1000.0f, 0.3f }
	})

	,m_standingTime(0.0f)

{ 
}


PlayerStatus::~PlayerStatus()
{ 
}


bool PlayerStatus::CanStompJump() {
	AddOneFrame(m_standingTime);
	if (m_standingTime <= m_canStompJumpTime) { return true; }
	return false;
}


bool PlayerStatus::CanNextJump() {
	AddOneFrame(m_standingTime);
	//次の段階のジャンプに切り替え可能か
	if (m_standingTime <= m_canNextJumpTime) { return true; }
	return false;
}


NormalEnemyStatus::NormalEnemyStatus() : 
	CharacterStatus(
		1,			//maxLife
		50.0f,		//walkSpeed
		100.0f		//runSpeed
	)
	,m_rotateSpeed(1.5f)
	,m_frontAngle(0.9999f)	
{
}


NormalEnemyStatus::~NormalEnemyStatus()
{ 
}