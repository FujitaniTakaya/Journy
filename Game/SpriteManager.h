#pragma once
#include "Actor.h"

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


class SpriteManager : public Actor{
private:
	bool m_isActive;

public:
	virtual void SetUpSprite()override;

public:
	SpriteManager();
	virtual ~SpriteManager()override;
	virtual bool Start()override;
	virtual void Update()override;
	virtual void Render(RenderContext& rc)override;
};



class Title : public Actor {
private:
	virtual void SetUpSprite()override;


public:
	Title();
	~Title() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};