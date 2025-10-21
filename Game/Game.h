#pragma once

//#include "Level3DRender/LevelRender.h"

class Player;
class Stage;
class Enemy;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start()override;

private:
	Stage* m_stage = nullptr;
	Player* m_player = nullptr;
	Enemy* m_enemy = nullptr;
};

