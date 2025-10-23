#pragma once
#include <coroutine>
#include <optional>


class Enemy : public IGameObject{
protected:
	void Update()override;
	void UpdateEnemyPos();

	void Render(RenderContext& rc)override;

	void SetEnemyModel(const int enemyNum);
	bool IsModel(const ModelRender* model);


	//�G�l�~�[�������_���ɓ�����
	void RandomWalk();
	void RandomWait(std::atomic<bool>& waitFlag);

	//�ړI�n�̕����������Ă��邩�ǂ���
	bool IsRotateMovePos();
	//�ړI�n�ɂ��邩�ǂ���
	bool IsBeingMovePos()const;
	//���̖ړI�n�����߂�
	void DecideToMovePos();


private:
/// <summary>
/// /�Q�b�^�[
/// </summary>
	bool IsWait()const;

private:
	//�ҋ@���Ԃ̃^�C�}�[���X�^�[�g����
	void StartWaitTime(std::atomic<bool>& waitFlag);

public:
	enum EnEnemy {
		enEnemy_Normal,
		enEnemy_Gimmick,
		enEnemy_Boss,
		enEnemy_Num
	};

private:
	std::atomic<bool> m_isWait = true;

protected:
	ModelRender* m_enemyModelRender = nullptr;

	Vector3 m_enemyPos = Vector3::Zero;
	Vector3 m_moveSpeed =  Vector3::Zero;
	Vector3 m_firstEnemyPos = Vector3::Zero;
	Vector3 m_toMovePos = Vector3::Zero;
	Quaternion m_enemyRotate = Quaternion::Identity;
	CharacterController m_enemyCharaCon;
};

class Normal : public Enemy {
public:
	bool Start()override;
};

class Gimmick : public Enemy {
public:
	bool Start()override;
};

class Boss : public Enemy {
public:
	bool Start()override;
};