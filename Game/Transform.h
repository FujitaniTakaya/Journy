#pragma once
class Transform
{
public:
	/** À•W */
	Vector3 position = Vector3::Zero;
	/** ‰ñ“] */
	Quaternion rotation = Quaternion::Identity;
	/** Šgk */
	Vector3 scale = Vector3::One;

	/** ‰Šú‰»—p’è” */
	static const Transform Initialize;


public:
	Transform();
	~Transform();


public:
	/**	À•W‚ğ“ü—Í */
	inline void SetPosition(const Vector3& pos)
	{
		position = pos;
	}

	/** À•W‚ğæ“¾ */
	inline const Vector3& GetPosition()const
	{
		return position;
	}


public:
	/** ‰ñ“]‚ğ“ü—Í */
	inline void SetRotation(const Quaternion& rot)
	{
		rotation = rot;
	}

	/** ‰ñ“]‚ğæ“¾ */
	inline const Quaternion& GetRotation()const
	{
		return rotation;
	}


public:
	/** Šgk‚ğ“ü—Í */
	inline void SetScale(const Vector3& scl)
	{
		scale = scl;
	}

	/** Šgk‚ğæ“¾ */
	inline const Vector3& GetScale()const
	{
		return scale;
	}


public:
	/**	À•WA‰ñ“]AŠgk‚ğ‚Ü‚Æ‚ß‚Ä“ü—Í */
	inline void SetTransform(const Vector3 pos, const Quaternion rot, const Vector3 scl)
	{
		position = pos;
		rotation = rot;
		scale = scl;
	}
};