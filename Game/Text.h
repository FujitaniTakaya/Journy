#pragma once


enum EnMoveState {
	enMoveState_Walk,
	enMoveState_Run,
	enMoveState_Num
};


enum EnJumpPower {
	enJumpPower_First,
	enJumpPower_Second,
	enJumpPower_Third,
	enJumpPower_Num
};


namespace nsAnim {
	const std::string ANIM_FILE_PATH = "Assets/animData/";
	const std::string ANIM_FILE_EXTENTION = ".tka";

	static inline std::string GetFullPath(const std::string charType, const std::string& fileName) {
		return ANIM_FILE_PATH + charType + fileName + ANIM_FILE_EXTENTION;
	}
}


namespace nsModel {
	const std::string FILE_PATH = "Assets/modelData/";
	const std::string FILE_EXTENTION = ".tkm";

	static inline std::string GetFullPath(const std::string charType, const std::string& fileName) {
		return FILE_PATH + charType + fileName + FILE_EXTENTION;
	}
}