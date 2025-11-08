#pragma once
#include <stdint.h>
#include "Text.h"


namespace Gravity {
	constexpr float MAX_FLYING_TIME = 0.5f;						//重力加速の最大フレーム数
	constexpr float GRAVITY = -49.0f;							//重力加速度
}


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
	//std::vector<AnimationClip> m_animationClips;

	float m_flyingTime = 0.0f;


public:
	Character(){}
	~Character(){}

	virtual bool Start()override { return true; }
	virtual void Update() override {}
	virtual void Render(RenderContext& rc) override {}


public:
	// 初期化
	virtual void InitializeCharacter(){}

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

	inline void SetTRS(const Vector3& pos = Vector3::Zero, const Quaternion& rot = Quaternion::Identity, const Vector3& scale = Vector3::Zero) {
		SetPosition(pos);
		SetRotation(rot);
		SetScale(scale);
	}

	inline const Vector3& GetMoveSpeed() const { return m_moveSpeed; }
	inline void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }
	inline void SetMoveSpeed(const float& x, const float& y, const float& z) { SetMoveSpeed({ x, y, z }); }



	inline void Add(const Vector3& add, Vector3& m_moveSpeed) { m_moveSpeed += add; }
	inline void Add(const float add, float& m_moveSpeed) { m_moveSpeed += add; }
	

	/** 当たり判定系 */
public:
	inline CharacterController* GetCharacterController() { return &m_characterController; }	

	inline void InitCollisionObject() { m_characterCollision = new CollisionObject; }
	inline CollisionObject* GetCollisionObject() { return m_characterCollision; }


	/** モデルレンダー系 */
public:
	inline ModelRender* GetModelRender() { return &m_modelRender; }
	//今回はアニメーションは基底クラスで管理しない
	//AnimationClip* GetAnimationClip() { return m_animationClips.data(); }


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

	/**	キャラクター更新処理 */
protected:
	inline void UpdateTRSInfo() {
		//キャラコンに速度を加算して位置を更新
		Vector3 pos = GetCharacterController()->Execute(m_moveSpeed, GameInfo::ONE_FRAME);
		SetPosition(pos);
		//モデルの位置、回転、スケールを更新
		GetModelRender()->SetTRS(GetPosition(), GetRotation(), GetScale());
		GetModelRender()->Update();
	}


	inline void UpdateCollisionInfo() {
		if (!GetCollisionObject()) {
			return;
		}
		GetCollisionObject()->SetIsEnable(true);
		GetCollisionObject()->SetPosition(GetPosition());
		GetCollisionObject()->SetRotation(GetRotation());
	}


	/**	重力処理	*/
protected:
	inline void AddGravity() {
		//滞空時間を加算
		GameInfo::AddOneFrame(m_flyingTime);
		m_flyingTime = min(m_flyingTime, Gravity::MAX_FLYING_TIME);
		const float gravity = Gravity::GRAVITY * m_flyingTime;
		//重力加算
		Add(gravity, m_moveSpeed.y);
	}


	/**	移動方向に回転	*/
protected:
	inline void RotateToMoveDirection() {
		m_rotation.SetRotationYFromDirectionXZ(GetMoveSpeed());
	}
};