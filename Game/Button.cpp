#include "stdafx.h"
#include "Button.h"


Button::Button(){
}
Button::~Button() {
}
void Button::SetUpSprite() {
}
bool Button::Start() {
	return true;
}
void Button::Update() {
}
void Button::Render(RenderContext& rc) {
}



StartButton::StartButton() {
}
StartButton::~StartButton() {
}
void StartButton::SetUpSprite() {
	//スプライトの設定
	m_spriteRender.Init("Assets/outGame/title/start_button.dds", 400.0f, 100.0f);
}
bool StartButton::Start() {
	SetUpSprite();
	return true;
}
void StartButton::Update() {
}
void StartButton::Render(RenderContext& rc) {
}



HowToPlayButton::HowToPlayButton() {
}
HowToPlayButton::~HowToPlayButton() {
}
void HowToPlayButton::SetUpSprite() {
	//スプライトの設定
	m_spriteRender.Init("Assets/outGame/title/howtoplay_button.dds", 400.0f, 100.0f);
}
bool HowToPlayButton::Start() {
	SetUpSprite();
	return true;
}
void HowToPlayButton::Update() {
}
void HowToPlayButton::Render(RenderContext& rc) {
}



ExitButton::ExitButton() {
}
ExitButton::~ExitButton() {
}
void ExitButton::SetUpSprite() {
	//スプライトの設定
	m_spriteRender.Init("Assets/outGame/title/exit_button.dds", 400.0f, 100.0f);
}
bool ExitButton::Start() {
	SetUpSprite();
	return true;
}
void ExitButton::Update() {
}
void ExitButton::Render(RenderContext& rc) {
}




ToTitleButton::ToTitleButton() {
}
ToTitleButton::~ToTitleButton() {
}
void ToTitleButton::SetUpSprite() {
	//スプライトの設定
	m_spriteRender.Init("Assets/outGame/pause/to_title_button.dds", 400.0f, 100.0f);
}
bool ToTitleButton::Start() {
	SetUpSprite();
	return true;
}
void ToTitleButton::Update() {
}
void ToTitleButton::Render(RenderContext& rc) {
}
