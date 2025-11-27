#pragma once
#include "Transform.h"
#include "ActorStatus.h"

class Actor : public IGameObject {
protected:
	Transform m_transform;
	ModelRender m_modelRender;
	SpriteRender m_spriteRender;

	//ActorStatus* m_status = nullptr;
public:
	Actor();
	virtual ~Actor();


public:
	virtual bool Start()override = 0;
	virtual void Update()override = 0;
	virtual void Render(RenderContext& rc)override = 0;


public:
	inline Transform& GetTRSIns() { return m_transform; }

	inline ModelRender* GetModelRender() { return &m_modelRender; }

	inline SpriteRender* GetSpriteRender() { return &m_spriteRender; }
};