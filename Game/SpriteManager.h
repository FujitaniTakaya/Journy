#pragma once

struct SpriteSlot {
	SpriteRender spriteRender;
	bool isActive;
};


enum EnSpriteType {
	enSpriteType_Title,	
	enSpriteType_StageClear,
	enSpriteType_GameOver,
	enSpriteType_Pause,
	enSpriteType_StartButton,
	enSpriteType_HowToPlayButton,
	enSpriteType_ExitButton,
	enSpriteType_Num
};


class SpriteManager : public IGameObject{
private:
	std::vector<SpriteSlot> m_spritSlots;


public:
	void LoadSprites();
	void SetActive(EnSpriteType type, bool isActive);


public:
	SpriteManager();
	~SpriteManager()override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};

