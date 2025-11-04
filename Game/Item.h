#pragma once
class Item : public IGameObject{
public:
	Item();
	~Item();
	void Update()override;
	void Render(RenderContext& rc)override;


private:
	ModelRender m_itemModelRender;
	Quaternion m_itemRotate = Quaternion::Identity;
};

