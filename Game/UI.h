#pragma once


namespace UIInfo {
	namespace Life {
		constexpr int MAX_HP = 5;
	}
	

	namespace Timer {
		constexpr int ONE_SECOND = 1;
		constexpr int ONE_MINUTE = 60;
	}
	
}


class Player;

class UI : public IGameObject{

private:
	struct Life {
		SpriteRender spriteRender;
		bool isActive = true;
	};
	std::array<Life, UIInfo::Life::MAX_HP> m_life;
	FontRender m_timerFontRender;
	FontRender m_scoreFontRender;

	float m_gameTimer = 0.0f;
	int m_second = 00;
	int m_minute = 00;
	std::array<wchar_t, FontRender::MAX_TEXT_SIZE> m_timerText;

	float m_score = 0.0f;
	std::array<wchar_t, FontRender::MAX_TEXT_SIZE> m_scoreText;


	std::thread m_timerThread;


private:
	Player* m_player = nullptr;


public:

	UI() : m_gameTimer(0.0f)
		,m_second(0)
		,m_minute(0)
		,m_score(0)
	{}

	~UI()noexcept {}


	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {
		m_timerFontRender.Draw(rc);
		m_scoreFontRender.Draw(rc);
		for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
			if (m_life[i].isActive) m_life[i].spriteRender.Draw(rc);
		}
	}
	

public:
	void UpdateLife();


private:
	inline void UpdateUI() {
		UpdateSecond();
		UpdateMinute();
		UpdateTimerText();
	}



	inline void UpdateSecond() {		
		if (m_gameTimer >= UIInfo::Timer::ONE_SECOND) {
			m_gameTimer = 0.0f;
			m_second++;
		}
	}

	inline void UpdateMinute() {
		if (m_second >= UIInfo::Timer::ONE_MINUTE) {
			m_second = 0;
			m_minute++;
		}
	}

	inline void UpdateTimerText() {
		swprintf_s(m_timerText.data(), m_timerText.size(), L"Time: %02d:%02d", m_minute, m_second);	
		m_timerFontRender.SetText(m_timerText.data());
	}
};

