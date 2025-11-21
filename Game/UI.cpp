#include "stdafx.h"
#include "UI.h"
#include "Player.h"

#include <algorithm>


namespace {
	std::string GetNumberFilePath(int number)
	{
		return "Assets/font/number/pngFold/" + std::to_string(number) + ".DDS";
	}
}


void UI::InitializeTimer() {
	m_nowTime = nsUI::Timer::LIMIT;
	m_timer[0].nowTime = 0;
	m_timer[1].nowTime = 0;
	m_timer[2].nowTime = 3;


	for (int i = 0; i < enTimer_Num; i++) {
		int fileNum = m_timer[i].nowTime;
		UpdateSpriteInfo(
			&m_timer[i].spriteRender
			, nsUI::Timer::POS[i]
			, nsUI::Timer::SCALE
			, GetNumberFilePath(fileNum));
	}
}


void UI::InitializeScore() {
	m_nowScore = 0;
	for (int i = 0; i < enMaxScoreDigit; i++) {
		m_score[i].nowScore = 0;

		int fileNum = m_score[i].nowScore;

		UpdateSpriteInfo(
			&m_score[i].spriteRender
			, nsUI::Score::POS[i]
			, nsUI::Score::SCALE
			, GetNumberFilePath(fileNum)
		);
	}

}


void UI::InitializeLife() {
	for (int i = 0; i < nsUI::Life::MAX; i++) {
		m_life[i].isActive = true;

		UpdateSpriteInfo(
			&m_life[i].spriteRender
			, nsUI::Life::POS[i]
			, Vector3::One
			, GetLifeFilePath()
		);
	}
	UpdateLife();
}


bool UI::Start() {
	m_player = FindGO<Player>("player");

	InitializeTimer();
	InitializeScore();
	InitializeLife();

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
	//Œ»“_‚Å‚Ì•b”‚ğ•Û‘¶
	int oldSecond = m_timer[enTimer_OneSecond].nowTime;

	//ˆêƒtƒŒ[ƒ€‰ÁZ
	m_gameTimer += g_gameTime->GetFrameDeltaTime();
	//Œo‚Á‚½ƒtƒŒ[ƒ€•ª‚ÌŠÔ‚ğˆø‚­
	m_nowTime = UIInfo::Timer::TIME_LIMIT - m_gameTimer;
	//0•bˆÈ‰º‚É‚Í‚µ‚È‚¢
	m_nowTime = max(0.0f, m_nowTime);


	//100‚ÌˆÊ‚ÌŒvZ
	//Œ»İ‚Ìc‚èŠÔ‚ğ100‚ÅŠ„‚Á‚½’l‚ğŠi”[
	m_timer[enTimer_HanSecond].nowTime = m_nowTime / UIInfo::Timer::HAN_SECOND;
	
	//c‚è‰½100•b‚©Ši”[
	float hanSec = UIInfo::Timer::HAN_SECOND * m_timer[enTimer_HanSecond].nowTime;
	
	//Œ»İ‚Ìc‚èŠÔ‚©‚ç100‚ÌˆÊ‚ğˆø‚¢‚½’l‚ğ10‚ÅŠ„‚Á‚½’l‚ğŠi”[
	m_timer[enTimer_TenSecond].nowTime = (m_nowTime - hanSec) / UIInfo::Timer::TEN_SECOND;
	
	//c‚è‰½10•b‚©Ši”[
	float tenSec = UIInfo::Timer::TEN_SECOND * m_timer[enTimer_TenSecond].nowTime;
	
	//Œ»İ‚Ìc‚èŠÔ‚©‚ç100‚Æ10‚ÌˆÊ‚ğˆø‚¢‚½’l‚ğ1‚ÅŠ„‚Á‚½’l‚ğŠi”[
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