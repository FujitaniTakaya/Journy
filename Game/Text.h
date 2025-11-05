#pragma once
#include "stdint.h"

enum EnPlayerState {
	enPlayerState_Idle,
	enPlayerState_Walk,
	enPlayerState_Run,
	enPlayerState_Jump,
	enPlayerState_Num
};


namespace GameInfo {
	constexpr float ONE_FRAME = 1.0f / 60.0f;
}


enum class EnEnemyRot : uint8_t{
	enEnemyRot_Left,
	enEnemyRot_Right,
	enEnemyRot_None,
	enEnemyRot_Num
};


enum class EnEnemy : uint8_t
{
	enEnemy_Normal,
	enEnemy_Gimmick,
	enEnemy_Boss,
	enEnemy_Num
};