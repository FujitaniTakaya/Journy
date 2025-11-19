#pragma once


namespace UIInfo {
	namespace Life {
		constexpr int MAX_HP = 5;
	}

	namespace Timer {
	}
}


class Player;

class UI : public IGameObject{
private:
	std::array<Life, UIInfo::Life::MAX_HP> m_life;
	float m_gameTimer = 0.0f;
	float m_score = 0.0f;


private:
	Player* m_player = nullptr;


public:

		,m_score(0)
	{}

	~UI()noexcept {}


	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override {
		for (int i = 0; i < UIInfo::Life::MAX_HP; i++) {
		}
	}
	

	void UpdateLife();




};

