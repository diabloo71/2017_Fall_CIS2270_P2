#pragma once
/**
*	Author: Ivonne Nelson
*	Email :	ssalinas6@cnm.edu
*   File  : Transform.h
*/
#include "MathFuncs.h"

class Transform
{
public:
	Transform(const vec3& pos = vec3(0.0f, 0.0f, 0.0f), const vec3& rotat = vec3(0.0f, 0.0f, 0.0f), const vec3& scales = vec3(1.0f, 1.0f, 1.0f))
	{
		positionIt = pos;
		rotateIt = rotat;
		scaleIt = scales;
	}

	mat4 GetModel()const
	{
		mat4 posMatrix = translate(identity_mat4(), positionIt);  // gives the vec3 position
		mat4 scaleMatrix = scale(identity_mat4(), scaleIt);       // scales the object

		mat4 rotXMatrix = rotate_x_deg(identity_mat4(), angleX);  // rotates the object around the X axis
		mat4 rotYMatrix = rotate_y_deg(identity_mat4(), angleY);  // rotates the object around the Y axis
		mat4 rotZMatrix = rotate_z_deg(identity_mat4(), angleZ);  // rotates the object around the Z axis
		mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;    // calculates the rotation in 3D

		return identity_mat4() * posMatrix * rotMatrix * scaleMatrix;  //complete calculation
	}
	// Accessors & Mutators
	void SetPositionIt(vec3 pos) {
		positionIt = pos;
	}
	vec3& GetPositionIt() {
		return positionIt;
	}
	void SetRotateIt(vec3 rotat) {
		rotateIt = rotat;
	}
	vec3& GetRotateIt() {
		return rotateIt;
	}
	void SetScaleIt(vec3 scales) {
		scaleIt = scales;
	}
	vec3& GetScaleIt() {
		return scaleIt;
	}
	void SetAngleX(float aX = 0.0f) {
		angleX = aX;
	}	
	void SetAngleY(float ay = 0.0f) {
		angleY = ay;
	}
	void SetAngleZ(float aZ = 0.0f) {
		angleZ = aZ;
	}
private:
	vec3 positionIt;
	vec3 rotateIt;
	vec3 scaleIt;
	float angleX = 0.0f;
	float angleY = 0.0f;
	float angleZ = 0.0f;
};
