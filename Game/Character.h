#pragma once
#include <stdint.h>

enum EnCharacterType {
	enCharacterType_Player,
	enCharacterType_NormalEnemy,
	enCharacterType_GuimickEnemy,
	enCharacterType_BossEnemy,
	enCharacterType_Num
};



class Character : public IGameObject
{
protected:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rotation = Quaternion::Identity;
	CharacterController m_characterController;
	CollisionObject* m_characterCollision = nullptr;
	ModelRender m_modelRender;


public:
	Character();
	~Character();

	virtual bool Start()override { return true; }
	virtual void Update() override {}
	virtual void Render(RenderContext& rc) override {}


public:
	// 初期化


private:
	// このクラスでしか呼ばれないもの


	/** 位置情報などのゲッター・セッター系 */
public:
	inline const Vector3& GetPosition() const { return m_position; }
	inline void SetPosition(const Vector3& pos) { m_position = pos; }

	inline const Vector3& GetScale() const { return m_scale; }
	inline void SetScale(const Vector3& scale) { m_scale = scale; }

	inline const Quaternion& GetRotation() const { return m_rotation; }
	inline void SetRotation(const Quaternion& rot) { m_rotation = rot; }


	/** 当たり判定系 */
public:
	CharacterController* GetCharacterController() { return &m_characterController; }
	CollisionObject* GetCollisionObject() { return m_characterCollision; }
};