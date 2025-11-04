#include "stdafx.h"
#include "Item.h"

namespace {
	const std::string ITEM_FILE_PATH = "Assets/item/item.tkm";
}



Item::Item() {
	m_itemModelRender.Init(ITEM_FILE_PATH.c_str());
	m_itemModelRender.SetPosition(100.0f, 0.0f, 100.0f);
	m_itemModelRender.Update();
}


Item::~Item() {

}


void Item::Update() {
	m_itemRotate.AddRotationDegY(1.0f);
	m_itemModelRender.SetRotation(m_itemRotate);
	m_itemModelRender.Update();
}

void Item::Render(RenderContext& rc) {
	m_itemModelRender.Draw(rc);
}