#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include "UI.h"

namespace {
	int HEAL_AMOUNT = 1;

	const std::string FILE_PATH = "Assets/item/";
	const std::string FILE_EXT = ".tkm";

	struct ItemInfo {
		std::string fileName;

		const std::string GetItemFullPath()const {
			return FILE_PATH + fileName + FILE_EXT;
		}
	};


	const ItemInfo ITEM_INFO[enItemType_Num] = {
		{ "purpCrystal/purpCrystal" },
	};
}



Item::Item() {
}


Item::~Item() {
}


bool Item::Start() {
	return true;
}


void Item::Update(){}


void Item::Render(RenderContext& rc) {}


void Item::InitializeItem(EnItemType itemType) {
	//入力されたものが範囲外なら抜ける
	if (itemType >= enItemType_Num || itemType < enItemType_None) return;

	//モデルの初期化
	m_modelRender.Init(ITEM_INFO[itemType].GetItemFullPath().c_str());
	m_modelRender.SetTRS(m_transform.position, m_transform.rotation, m_transform.scale);
	m_modelRender.Update();
}


void Item::GetOtherClassInfo() {
	m_player = FindGO<Player>("player");
	m_ui = FindGO<UI>("ui");
}


//---------------------------------------------------------
//-- PurpleCrystal クラス
//---------------------------------------------------------


PurpleCrystal::PurpleCrystal() {
}

PurpleCrystal::~PurpleCrystal() {
	if (m_collision) {
		delete m_collision;
		m_collision = nullptr;
	}
}


bool PurpleCrystal::Start() {
	InitializeItem(enItemType_PurpleCrystal);

	m_collision = new CollisionObject;
	m_collision->CreateSphere(
		m_transform.position,
		m_transform.rotation,
		5.0f
	);
	return true;
}


void PurpleCrystal::Update() {
	if (m_collision->IsHit(m_player->GetCharacterController())) {
		Effect();
		DeleteGO(this);
	}
}


void PurpleCrystal::Render(RenderContext& rc) {
	m_modelRender.Draw(rc);
}


void PurpleCrystal::Effect() {
	m_player->GetStatus()->HealLife(HEAL_AMOUNT);
}