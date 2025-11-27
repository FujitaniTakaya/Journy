#include "stdafx.h"
#include "Game.h"
#include "Stage.h"
#include "Player.h"
#include "GameCamera.h"
#include "NormalEnemy.h"
#include "UI.h"

bool Game::Start()
{
	StartGame();
	return true;
}


void Game::Render(RenderContext& rc) {
	m_stageLevelRender.Draw(rc);
}


void Game::StartGame() {
	m_stageLevelRender.Init("Assets/stage/firstStage/stage.tkl", [&](LevelObjectData& objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			m_player = NewGO<Player>(0, "player");
			m_player->GetTRSIns().SetTransform(objData.position, objData.rotation, objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"firstStageGround")) {
			m_firstStage = NewGO<First>(0, "firstStage");
			m_firstStage->GetTRSIns().SetTransform(objData.position, objData.rotation, objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"goalPole")) {
			m_goalPole = NewGO<GoalPole>(0, "goalPole");
			m_goalPole->GetTRSIns().SetTransform(objData.position, objData.rotation, objData.scale);
			return true;
		}
		if (objData.EqualObjectName(L"normalEnemy")) {
			m_firstStageEnemyCount;
			auto enemy = m_firstStageEnemies;
			enemy[m_firstStageEnemyCount] = NewGO<NormalEnemy>(0, "enemy");
			enemy[m_firstStageEnemyCount]->GetTRSIns().SetTransform(objData.position, objData.rotation, objData.scale);
			m_firstStageEnemyCount++;
			return true;
		}

		});

	m_player->GetTRSIns().GetPosition();

	m_ui = NewGO<UI>(1, "ui");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(5, "skyCube");
	m_skyCube->SetType(static_cast<EnSkyCubeType>(m_skyCubeType));
	m_skyCube->SetScale(5000.0f);
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 1.0f);
}