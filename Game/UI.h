#pragma once

enum EnTimer {
	enTimer_OneSecond,
	enTimer_TenSecond,
	enTimer_HanSecond,
	enTimer_Num,
};


namespace UIInfo {
	namespace Life {
		constexpr int MAX_HP = 5;
	}


	namespace Timer {
		constexpr int ONE_SECOND = 1;			//1	 •b
		constexpr int TEN_SECOND = 10;			//10 •b
		constexpr int HAN_SECOND = 100;			//100•b

		constexpr float TIME_LIMIT = 300.0f;	//300•b
	}
	const Vector3 TIMER_POS[enTimer_Num] = {
			{  500.0f, 300.0f, 0.0f },	//1•b
			{  460.0f, 300.0f, 0.0f },	//10•b
			{  420.0f, 300.0f, 0.0f }	//100•b
	};
}


struct Life {
	SpriteRender lifeSpriteRender;
	bool isActive = true;
};

struct Timer {
	Timer() : 
		nowTime(0)
	{}

	int nowTime;
	SpriteRender timerSpriteRender;
};


class Player;

class UI : public IGameObject{
private:
	std::array<Life, UIInfo::Life::MAX_HP> m_life;
	std::array<Timer, enTimer_Num> m_timer;
	float m_gameTimer = 0.0f;
	float m_nowTime = 0.0f;
	float m_score = 0.0f;


private:
	Player* m_player = nullptr;


public:

	UI() : 
		m_gameTimer(0.0f)
		, m_nowTime(UIInfo::Timer::TIME_LIMIT)
		,m_score(0)
	{}

	~UI()noexcept {}


	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {
		for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
			if (m_life[i].isActive) m_life[i].lifeSpriteRender.Draw(rc);
		}
		for (int i = 0; i < enTimer_Num; i++) {
			m_timer[i].timerSpriteRender.Draw(rc);
		}
	}
	

	/** ‘Ì—Í‚Ìî•ñ‚ðXV‚·‚é */
	void UpdateLife();



private:
	/** Œ»Ý‚ÌŽžŠÔ‚ðŒv‘ª‚·‚é */
	void MeasureNowTime();

	/** ƒ^ƒCƒ}[‚ðXV‚·‚é */
	void UpdateTimer();
};

