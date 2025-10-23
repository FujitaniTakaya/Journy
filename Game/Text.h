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

