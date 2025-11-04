#pragma once


enum EnPlayerState {
	enPlayerState_Idle,
	enPlayerState_Walk,
	enPlayerState_Run,
	enPlayerState_Jump,
	enPlayerState_Num
};
namespace {
	float ONE_FRAME = 1 / 60.0f;
}



enum class EnEnemy : uint8_t
{
	enEnemy_Normal,
	enEnemy_Gimmick,
	enEnemy_Boss,
	enEnemy_Num
};