#pragma once
#include "Level3DRender/LevelRender.h"



class Stage;
class Player;
class GameCamera;
class Enemy;
class UI;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start()override;
	void Render(RenderContext& rc)override;

private:
	Stage* m_firstStage = nullptr;
	Stage* m_goalPole = nullptr;
	std::array<Enemy*, 6> m_firstStageEnemies = { nullptr };
	int m_firstStageEnemyCount = 0;
	int m_floorCount = 0;
	Player* m_player = nullptr;
	GameCamera* m_gameCamera = nullptr;

	SkyCube* m_skyCube = nullptr;
	int m_skyCubeType = enSkyCubeType_Wild_2;
	
	LevelRender m_stageLevelRender;

	UI* m_ui = nullptr;
};

