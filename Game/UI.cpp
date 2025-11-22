#include "stdafx.h"
#include "UI.h"
#include "Player.h"

#include <algorithm>


namespace {
	inline std::string GetNumberFilePath(int number)
	{
		return "Assets/UI/number/dds/" + std::to_string(number) + ".DDS";
	}

	inline std::string GetLifeFilePath()
	{
		return "Assets/UI/life/life.dds";
	}



	void UpdateSpriteInfo(SpriteRender* spriteRender, const Vector3& pos, const Vector3& scl, std::string filePath) {
		spriteRender->Init(filePath.c_str(), 30.0f, 50.0f);
		spriteRender->SetPosition(pos);
		spriteRender->SetScale(scl);
		spriteRender->Update();
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
	for (int i = 0; i < nsUI::Life::MAX; i++) {
		if (i < hp) continue;
		m_life[i].isActive = false;
	}
}


void UI::MeasureNowTime() {
	//一フレーム加算
	m_gameTimer += g_gameTime->GetFrameDeltaTime();
	//経ったフレーム分の時間を引く
	m_nowTime = nsUI::Timer::LIMIT - m_gameTimer;
	//0秒以下にはしない
	m_nowTime = max(0.0f, m_nowTime);

	int harderDigitTimeCalc = 0;

	for (int i = enTimer_Num - 1; i >= 0; i--) {
		int oldTime = m_timer[i].nowTime;
		m_timer[i].nowTime = (m_nowTime - harderDigitTimeCalc) / nsUI::Timer::DIGIT[i];
		harderDigitTimeCalc += m_timer[i].nowTime * nsUI::Timer::DIGIT[i];

		if (oldTime == m_timer[i].nowTime) continue;

		//時間が変化していたらスプライトを更新
		int fileNum = m_timer[i].nowTime;

		UpdateSpriteInfo(
			&m_timer[i].spriteRender
			, nsUI::Timer::POS[i]
			, nsUI::Timer::SCALE
			, GetNumberFilePath(fileNum)
		);
	}
}


void UI::AddScore(float score) {
	//スコアを加算
	m_nowScore += score;
	
	//桁ごとのスコアを計算
	int harderDigitScoreCalc = 0;

	for (int i = enMaxScoreDigit - 1; i > 0; i--) {
		//現在のスコアを保存
		int oldScore = m_score[i].nowScore;
				
		//桁ごとのスコアを計算
		//現在のスコアから、より大きい桁のスコアを引く
		//桁の値で割る
		m_score[i].nowScore = (m_nowScore - harderDigitScoreCalc) / nsUI::Score::DIGIT[i];
		
		//現在計算中桁のスコアを加算
		harderDigitScoreCalc += m_score[i].nowScore * nsUI::Score::DIGIT[i];
		
		//スコアが変化していなかったら次の桁へ
		if (oldScore == m_score[i].nowScore) continue;
			
		//スコアが変化していたらスプライトを更新
		int fileNum = m_score[i].nowScore;
		
		UpdateSpriteInfo(
			&m_score[i].spriteRender
			, nsUI::Score::POS[i]
			, nsUI::Score::SCALE
			, GetNumberFilePath(fileNum)
		);
	}
}


