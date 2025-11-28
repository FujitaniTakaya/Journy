#pragma once
#include "Actor.h"

class Button : public Actor{
private:
	virtual void SetUpSprite()override;

public:
	Button();
	~Button() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};


class StartButton : public Button {
	private:
		virtual void SetUpSprite()override;
public:
	StartButton();
	~StartButton() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};


class HowToPlayButton : public Button {
	private:
		virtual void SetUpSprite()override;
public:
	HowToPlayButton();
	~HowToPlayButton() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};


class ExitButton : public Button {
	private:
		virtual void SetUpSprite()override;
public:
		
	ExitButton();
	~ExitButton() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};


class ToTitleButton : public Button {
	private:
		virtual void SetUpSprite()override;
public:
	ToTitleButton();
	~ToTitleButton() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};


class RetryButton : public Button {
	private:
		virtual void SetUpSprite()override;
public:
	RetryButton();
	~RetryButton() override;
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;
};
