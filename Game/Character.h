#pragma once
#include <stdint.h>
#include "Status.h"
#include "memory.h"


class Character : public IGameObject
{
private:
	std::unique_ptr<GameStatus> m_status = nullptr;

protected:
	Vector3 m_firstPos = Vector3::Zero;
	Vector3 m_position = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Vector2 m_charConScl = Vector2::Zero;
	Quaternion m_rotation = Quaternion::Identity;
	CharacterController m_characterController;
	CollisionObject* m_characterCollision = nullptr;
	Vector3 m_charCollisionPos = Vector3::Zero;
	ModelRender m_modelRender;
	//std::vector<AnimationClip> m_animationClips;

	

public:
	Character() : m_status(std::make_unique<GameStatus>()) {}
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
	inline const Vector3& GetFirstPosition() const { return m_firstPos; }
	inline void SetFirstPosition(const Vector3& pos) { m_position = m_firstPos = pos; }

	inline const Vector3& GetPosition() const { return m_position; }
	inline void SetPosition(const Vector3& pos) { m_position = pos; }

	inline const Vector3& GetScale() const { return m_scale; }
	inline void SetScale(const Vector3& scale) { m_scale = scale; }

	inline const Quaternion& GetRotation() const { return m_rotation; }
	inline void SetRotation(const Quaternion& rot) { m_rotation = rot; }

	inline void SetTRS(const Vector3& pos = Vector3::Zero, const Quaternion& rot = Quaternion::Identity, const Vector3& scale = Vector3::One) {
		SetPosition(pos);
		SetRotation(rot);
		SetScale(scale);
	}

	inline const Vector3& GetMoveSpeed() const { return m_moveSpeed; }
	inline void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

	/** 当たり判定系 */
public:
	inline CharacterController* GetCharacterController() { return &m_characterController; }	

	inline void InitCollisionObject() { m_characterCollision = new CollisionObject; }
	inline CollisionObject* GetCollisionObject() { return m_characterCollision; }
	inline void DeleteCollision() {
		if (m_characterCollision) {
			delete m_characterCollision;
			m_characterCollision = nullptr;
		}
	}

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
		if (m_moveSpeed.x != 0.0f || m_moveSpeed.y != 0.0f || m_moveSpeed.z != 0.0f) {
			return true;
		}
		return false;
	}

	inline bool IsJump() {
		if (!m_characterController.IsOnGround()) {
			return true;
		}
		return false;
	}

	/**	キャラクター更新処理 */
protected:
	inline void UpdateTRSInfo() {
		//キャラコンに速度を加算して位置を更新
		m_position = m_characterController.Execute(m_moveSpeed, GameStatus::AddOneFrame());
		
		//モデルの位置、回転、スケールを更新
		m_modelRender.SetTRS(m_position, m_rotation, m_scale);
		m_modelRender.Update();
	}


	inline void UpdateCollisionInfo() {
		if (!m_characterCollision) {
			return;
		}
		m_characterCollision->SetIsEnable(true);
		m_charCollisionPos = m_position;
		m_charCollisionPos.y += m_charConScl.y * 3/4;
		m_characterCollision->SetPosition(m_charCollisionPos);
		m_characterCollision->SetRotation(m_rotation);
		m_characterCollision->Update();
	}


	/**	ステータス取得*/
private:
	inline GameStatus& GetGameStatus() {return *m_status;}

	/**	重力処理	*/
protected:
	inline void AddGravity() {
		//重力加算
		m_moveSpeed.y += m_status->GetGravity();
	}


	/**	移動方向に回転	*/
protected:
	inline void RotateToMoveDirection() {
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	}
};