#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"


bool Game::Start()
{
	m_stage = NewGO<Stage>(0, "stage");
	m_player = NewGO<Player>(0, "player");
	return true;
}