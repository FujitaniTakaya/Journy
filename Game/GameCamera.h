#pragma once
class Player;

class GameCamera : public IGameObject{
public:
	GameCamera();
	~GameCamera();
	void Update()override;
	
private:
	Player* m_player = nullptr;
	Vector3 m_toCameraPos = { Vector3::Zero };
};

