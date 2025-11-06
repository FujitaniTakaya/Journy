#pragma once
#include "stdint.h"

enum EnCharaState {
	enCharaState_Idle,
	enCharaState_Walk,
	enCharaState_Run,
	enCharaState_Jump,
	enCharaState_Num
};


namespace GameInfo {
	constexpr float ONE_FRAME = 1.0f / 60.0f;
	static inline void AddOneFrame(float& frameCount) {
		frameCount += ONE_FRAME;
	}
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