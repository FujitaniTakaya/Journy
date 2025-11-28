#include "stdafx.h"
#include "SpriteManager.h"


SpriteManager::SpriteManager(){
}


SpriteManager::~SpriteManager() {
}


void SpriteManager::SetUpSprite() {
	//スプライトの設定
	m_spriteRender.Init("Assets/outGame/sprite_manager/sprite_manager.dds", 1920.0f, 1080.0f);
}


bool SpriteManager::Start() {
	return true;
}


void SpriteManager::Update() {
	//更新処理
}


void SpriteManager::Render(RenderContext& rc) {
	//描画処理
}



Title::Title() {
}


Title::~Title() {
}


void Title::SetUpSprite() {
	//スプライトの設定
	m_spriteRender.Init("Assets/outGame/title/title.dds", 1920.0f, 1080.0f);
}


bool Title::Start() {
	return true;
}


void Title::Update() {
}


void Title::Render(RenderContext& rc) {
}