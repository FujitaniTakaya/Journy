#pragma once
#include <stdint.h>
#include "Actor.h"
#include "Status.h"
#include "memory.h"


class Character : public Actor
{
private:
	std::unique_ptr<GameStatus> m_status = nullptr;


protected:
	Vector3 m_firstPos = Vector3::Zero;
	Vector3 m_moveSpeed = Vector3::Zero;	
	Vector2 m_charConScl = Vector2::Zero;
	//Transform m_transform = Transform::Initialize;
	CharacterController m_characterController;
	//std::vector<AnimationClip> m_animationClips;

	

public:
	Character() : m_status(std::make_unique<GameStatus>()) {}
	virtual ~Character(){}

	virtual bool Start() override;
	virtual void Update()override;
	virtual void Render(RenderContext& rc)override;
	



public:
	// 初期化
	virtual void InitializeCharacter()= 0;


	inline const Vector3& GetMoveSpeed() const { return m_moveSpeed; }
	inline void SetMoveSpeed(const Vector3& speed) { m_moveSpeed = speed; }

	/** 当たり判定系 */
public:
	inline CharacterController& GetCharacterController() { return m_characterController; }	



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
		m_transform.position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);
		
		//モデルの位置、回転、スケールを更新
		m_modelRender.SetTRS(m_transform.position, m_transform.rotation, m_transform.scale);
		m_modelRender.Update();
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
		m_transform.rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
	}
};