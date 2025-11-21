#pragma once

enum EnTimer {
	enTimer_OneSecond,
	enTimer_TenSecond,
	enTimer_HunSecond,
	enTimer_Num,
};


enum EnScoreType {
	enScoreType_Coin = 0,
	enScoreType_Item,
	enScoreType_NormalEnemy,
	enScoreType_GimmickEnemy,
	enScoreType_BossEnemy,
	enScoreType_TimeBonus,
	enScoreType_Num
};


enum { enMaxScoreDigit = 6 };

namespace nsUI {
	namespace Life {
		constexpr int MAX = 5;

		const Vector3 POS[MAX] = {
			{ -700.0f, 400.0f, 0.0f},	//1
			{ -740.0f, 400.0f, 0.0f},	//2
			{ -780.0f, 400.0f, 0.0f},	//3
			{ -820.0f, 400.0f, 0.0f},	//4
			{ -860.0f, 400.0f, 0.0f}	//5
		};

	}


	namespace Timer {
		constexpr int ONE_SECOND = 1;			//1	 •b
		constexpr int TEN_SECOND = 10;			//10 •b
		constexpr int HUN_SECOND = 100;			//100•b

		constexpr float LIMIT = 300.0f;	//300•b

		const Vector3 POS[enTimer_Num] = {
			{  900.0f, 400.0f, 0.0f },	//1•b
			{  860.0f, 400.0f, 0.0f },	//10•b
			{  820.0f, 400.0f, 0.0f }	//100•b
		};


		const int DIGIT[enTimer_Num] = {
			ONE_SECOND,		//1•b
			TEN_SECOND,		//10•b
			HUN_SECOND		//100•b
		};


		const Vector3 SCALE = { 1.5f, 1.5f, 1.0f };
	}


	namespace Score {
		const Vector3 POS[enMaxScoreDigit] = {
			{  600.0f, 400.0f, 0.0f },	//1
			{  560.0f, 400.0f, 0.0f },	//10
			{  520.0f, 400.0f, 0.0f },	//100
			{  480.0f, 400.0f, 0.0f },	//1,000
			{  440.0f, 400.0f, 0.0f },	//10,000
			{  400.0f, 400.0f, 0.0f },	//10,0000
		};

		const int DIGIT[enMaxScoreDigit] = {
			1,		//1
			10,		//10
			100,	//100
			1000,	//1,000
			10000,	//10,000
			100000	//100,000
		};

		static const int MIN = 0;
		static const int MAX = 999999;

		const Vector3 SCALE = { 1.5f, 1.5f, 1.0f };

		const int TYPE[enScoreType_Num] = {
			10, //Coin
			50, //Item
			100,//NormalEnemy
			150,//GimmickEnemy
			500,//BossEnemy
			20  //TimeBonus
		};

		
	}
	
}


struct Life {
	Life() : 
		isActive(false)
	{}
	bool isActive;
	SpriteRender spriteRender;	
};

struct Timer {
	Timer() : 
		nowTime(0)
	{}
	int nowTime;
	SpriteRender spriteRender;
};


struct Score {
	Score() : 		
		nowScore(0)
	{}

	int nowScore;
	SpriteRender spriteRender;
};


class Player;

class UI : public IGameObject{
private:
	std::array<Life, nsUI::Life::MAX> m_life;
	std::array<Timer, enTimer_Num> m_timer;
	std::array<Score, enMaxScoreDigit> m_score;
	float m_gameTimer = 0.0f;
	float m_nowTime = 0.0f;
	int m_nowScore = 0.0f;


private:
	Player* m_player = nullptr;


public:

	UI() : 
		m_gameTimer(0.0f)
		, m_nowTime(nsUI::Timer::LIMIT)
		,m_nowScore(0)
	{}

	~UI()noexcept {}


	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {
		for (int i = 0; i < nsUI::Life::MAX; i++) {
			if (m_life[i].isActive) m_life[i].spriteRender.Draw(rc);
		}
		for (int i = 0; i < enTimer_Num; i++) {
			m_timer[i].spriteRender.Draw(rc);
		}
		for (int i = 0; i < 6; i++) {
			m_score[i].spriteRender.Draw(rc);
		}
	}
	

	/** ‘Ì—Í‚Ìî•ñ‚ðXV‚·‚é */
	void UpdateLife();


	void AddScore(float score);


private:
	/** ƒ^ƒCƒ}[‰Šú‰» */
	void InitializeTimer();

	/** ƒXƒRƒA‰Šú‰» */
	void InitializeScore();

	/** ƒ‰ƒCƒt‰Šú‰» */
	void InitializeLife();


private:
	/** Œ»Ý‚ÌŽžŠÔ‚ðŒv‘ª‚·‚é */
	void MeasureNowTime();
};

