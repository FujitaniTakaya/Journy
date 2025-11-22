#pragma once
#include "Actor.h"


class Player;
class UI;


enum EnItemType {
	enItemType_PurpleCrystal = 0,
	enItemType_Num,
	enItemType_None = -1
};



class Item : public Actor{
protected:
	CollisionObject* m_collision = nullptr;
	bool m_isEffect = false;

protected:
	Player* m_player = nullptr;
	UI* m_ui = nullptr;


public:
	Item();
	virtual ~Item();
	virtual bool Start()override;
	virtual void Update()override;
	virtual void Render(RenderContext& rc)override;


protected:
	void InitializeItem(EnItemType itemType = enItemType_Num);
	virtual void Effect() = 0;
	

	void GetOtherClassInfo();
};


class PurpleCrystal : public Item {
public:
	PurpleCrystal();
	~PurpleCrystal();
	bool Start()override;
	void Update()override;
	void Render(RenderContext& rc)override;


private:
	void Effect()override;
};