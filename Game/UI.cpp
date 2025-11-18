#include "stdafx.h"
#include "UI.h"
#include "Player.h"


bool UI::Start() {
	m_player = FindGO<Player>("player");

	for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
		SpriteRender* lifePtr = &m_life[i].spriteRender;
		lifePtr->Init("Assets/UI/life/life.dds", 50.0f, 50.0f);
		lifePtr->SetPosition({ -700.0f - (i * 40.0f), 400.0f, 0.0f });
		lifePtr->Update();
	}

	UpdateLife();


	UpdateTimerText();
	m_timerFontRender.SetText(m_timerText.data());
	m_timerFontRender.SetPosition({ 600.0f, 40.0f, 0.0f });


	
	
	return true;
}


void UI::Update() {
	m_gameTimer += g_gameTime->GetFrameDeltaTime();
	UpdateSecond();
	UpdateMinute();
	UpdateTimerText();
}


void UI::UpdateLife() {
	int hp = m_player->GetStatus()->GetLife();
	for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
		if (i < hp) continue;
		m_life[i].isActive = false;
	}
}