#include "stdafx.h"
#include "UI.h"
#include "Player.h"

#include <algorithm>

bool UI::Start() {
	m_player = FindGO<Player>("player");

	for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
		SpriteRender* lifePtr = &m_life[i].lifeSpriteRender;
		lifePtr->Init("Assets/UI/life/life.dds", 50.0f, 50.0f);
		lifePtr->SetPosition({ -700.0f - (i * 40.0f), 400.0f, 0.0f });
		lifePtr->Update();
	}
	UpdateLife();	

	MeasureNowTime();
	UpdateTimer();
	return true;
}


void UI::Update() {
	MeasureNowTime();
}


void UI::UpdateLife() {
	int hp = m_player->GetStatus()->GetLife();
	for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
		if (i < hp) continue;
		m_life[i].isActive = false;
	}
}


void UI::MeasureNowTime() {
	//現時点での秒数を保存
	int oldSecond = m_timer[enTimer_OneSecond].nowTime;

	//一フレーム加算
	m_gameTimer += g_gameTime->GetFrameDeltaTime();
	//経ったフレーム分の時間を引く
	m_nowTime = UIInfo::Timer::TIME_LIMIT - m_gameTimer;
	//0秒以下にはしない
	m_nowTime = max(0.0f, m_nowTime);


	//100の位の計算
	//現在の残り時間を100で割った値を格納
	m_timer[enTimer_HanSecond].nowTime = m_nowTime / UIInfo::Timer::HAN_SECOND;
	
	//残り何100秒か格納
	float hanSec = UIInfo::Timer::HAN_SECOND * m_timer[enTimer_HanSecond].nowTime;
	
	//現在の残り時間から100の位を引いた値を10で割った値を格納
	m_timer[enTimer_TenSecond].nowTime = (m_nowTime - hanSec) / UIInfo::Timer::TEN_SECOND;
	
	//残り何10秒か格納
	float tenSec = UIInfo::Timer::TEN_SECOND * m_timer[enTimer_TenSecond].nowTime;
	
	//現在の残り時間から100と10の位を引いた値を1で割った値を格納
	m_timer[enTimer_OneSecond].nowTime = (m_nowTime - hanSec - tenSec);

	if (oldSecond != m_timer[enTimer_OneSecond].nowTime) {
		UpdateTimer();
	}
	//UpdateTimer();
}


void UI::UpdateTimer() {
	for (int i = 0; i < enTimer_Num; i++) {
		std::string fileName = std::to_string(m_timer[i].nowTime);
		m_timer[i].timerSpriteRender.Init(("Assets/font/number/pngFold/" + fileName + ".DDS").c_str(), 30.0f, 50.0f);
		m_timer[i].timerSpriteRender.SetPosition(UIInfo::TIMER_POS[i]);
		//m_timer[i].timerSpriteRender.SetScale({ 10.0f, 10.0f, 10.0f });
		m_timer[i].timerSpriteRender.Update();
	}
}