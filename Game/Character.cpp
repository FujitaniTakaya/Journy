#include "stdafx.h"
#include "Character.h"


namespace {
	const std::string FILE_PATH = "Assets/";
	const std::string FILE_EXTENSION = ".tkm";

	struct CharacterInfo {
		std::string fileName;

		inline const std::string GetModelFullPath()const {
			return FILE_PATH + fileName + FILE_EXTENSION;
		}
	};

	const CharacterInfo CharacterModels[static_cast<int>(EnCharacterType::enCharacterType_Num)] = {
		{"modelData/unityChan"},
		{"enemy/normalEnemy/NormalEnemy"},
		{"enemy/gimmickEnemy/GimmickEnemy"},
		{"enemy/bossEnemy/BossEnemy"}
	};
}



void Character::InitModelRender(const EnCharacterType characterType) {
	const std::string modelPath = CharacterModels[static_cast<int>(characterType)].GetModelFullPath();
	
	if (characterType == EnCharacterType::enCharacterType_Player) {
		m_modelRender.Init(modelPath.c_str(), nullptr, 0, enModelUpAxisY);
		return;
	}
}