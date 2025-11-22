#include "stdafx.h"
#include "Transform.h"


Transform::Transform() {
	//position = Vector3::Zero;
	//rotation = Quaternion::Identity;
	//scale = Vector3::One;
}


Transform::~Transform() {
}


const Transform Transform::Initialize = Transform();