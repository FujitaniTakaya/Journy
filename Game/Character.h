#pragma once
#include <stdint.h>
#include "Text.h"


class Character : public IGameObject
{
protected:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rotation = Quaternion::Identity;
	Vector3 m_moveSpeed = Vector3::Zero;
	CharacterController m_characterController;
	CollisionObject* m_characterCollision = nullptr;
	ModelRender m_modelRender;


public:
	Character(){}
	~Character(){}

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
	inline void SetPosition(const float& x, const float& y, const float& z) { SetPosition({ x, y, z }); }

	inline const Vector3& GetScale() const { return m_scale; }
	inline void SetScale(const Vector3& scale) { m_scale = scale; }

	inline const Quaternion& GetRotation() const { return m_rotation; }
	inline void SetRotation(const Quaternion& rot) { m_rotation = rot; }

	inline void SetTRS(const Vector3& pos = {0.0f, 0.0f, 0.0f}, const Quaternion& rot = Quaternion::Identity, const Vector3& scale = {0.0f, 0.0f, 0.0f}) {
		SetPosition(pos);
		SetRotation(rot);
		SetScale(scale);
	}

	inline const Vector3& GetMoveSpeed() const { return m_moveSpeed; }
	inline void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }
	inline void SetMoveSpeed(const float& x, const float& y, const float& z) { SetMoveSpeed({ x, y, z }); }
	inline void SetMoveSpeedX(const float& x) { m_moveSpeed.x = x; }
	inline void SetMoveSpeedY(const float& y) { m_moveSpeed.y = y; }
	inline void SetMoveSpeedZ(const float& z) { m_moveSpeed.z = z; }
	inline void SetMoveSpeedXZ(const float& x, const float& z) { m_moveSpeed.x = x, m_moveSpeed.z = z; }
	inline void AddMoveSpeed(const Vector3& speed) { m_moveSpeed += speed; }
	inline void AddMoveSpeed(const float& x, const float& y, const float& z) { AddMoveSpeed({ x, y, z }); }
	inline void AddMoveSpeedX(const float& x) { m_moveSpeed.x += x; }
	inline void AddMoveSpeedY(const float& y) { m_moveSpeed.y += y; }
	inline void AddMoveSpeedZ(const float& z) { m_moveSpeed.z += z; }


	/** 当たり判定系 */
public:
	CharacterController* GetCharacterController() { return &m_characterController; }
	CollisionObject* GetCollisionObject() { return m_characterCollision; }


	/** モデルレンダー系 */
public:
	ModelRender* GetModelRender() { return &m_modelRender; }


	/** 移動フラグ系 */
public:
	inline bool IsStick(Vector2& stick) {
		if (stick.x != 0.0f || stick.y != 0.0f) {
			return true;
		}
		return false;
	}

	inline bool IsMove() {
		if (GetMoveSpeed().x != 0.0f || GetMoveSpeed().y != 0.0f || GetMoveSpeed().z != 0.0f) {
			return true;
		}
		return false;
	}

	inline bool IsJump() {
		if (!GetCharacterController()->IsOnGround()) {
			return true;
		}
		return false;
	}


};