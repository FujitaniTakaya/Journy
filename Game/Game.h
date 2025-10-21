#pragma once

//#include "Level3DRender/LevelRender.h"

class Stage;
class Player;
class GameCamera;
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
	GameCamera* m_gameCamera = nullptr;
	Enemy* m_enemy = nullptr;
};

