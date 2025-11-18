#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "GameCamera.h"
#include "Enemy.h"

bool Game::Start()
{
	m_stageLevelRender.Init("Assets/level/attachEnemy.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			m_player = NewGO<Player>(0, "player");
			m_player->SetTRS(objData.position,objData.rotation,objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"stageGround")) {
			m_firstStage = NewGO<First>(0);
			m_firstStage->SetTRS(objData.position, objData.rotation, objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"goalPole")) {
			m_goalPole = NewGO<GoalPole>(0);
			m_goalPole->SetTRS(objData.position, objData.rotation, objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"normalEnemy")) {
			for (auto enemy : m_firstStageEnemies) {
				enemy = NewGO<Normal>(0, "enemy");
				enemy->SetFirstPosition(objData.position);
				enemy->SetTRS(objData.position, objData.rotation, objData.scale);
			}
			return true;
		}

	});
	
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(5, "skyCube");
	m_skyCube->SetType(static_cast<EnSkyCubeType>(m_skyCubeType));
	m_skyCube->SetScale(5000.0f);
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(),1.0f);
	return true;
}


void Game::Render(RenderContext& rc) {
	m_stageLevelRender.Draw(rc);
}