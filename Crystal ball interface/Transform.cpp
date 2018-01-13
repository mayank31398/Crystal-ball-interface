#include "Transform.h"
#include<iostream>

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
	float radians = glm::radians(degrees);
	float cosine = cos(radians);
	float sine = sin(radians);

	mat3 identity_matrix = mat3(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);

	mat3 axis_axisTranspose = mat3(
		axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
		axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
		axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);

	mat3 dual_matrix = mat3(
		0, -axis.z, axis.y,
		axis.z, 0, -axis.x,
		-axis.y, axis.x, 0);

	return identity_matrix * cosine + axis_axisTranspose * (1 - cosine) + dual_matrix * sine;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up)
{
	vec3 axis = up;
	mat3 R = rotate(-degrees, axis);
	eye = R * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up)
{
	vec3 axis = glm::normalize(glm::cross(eye, up));
	mat3 R = rotate(-degrees, axis);
	eye = R * eye;
	up = R * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up)
{
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	return glm::transpose(mat4(
		u.x, u.y, u.z, -u.x * eye.x - u.y * eye.y - u.z * eye.z,
		v.x, v.y, v.z, -v.x * eye.x - v.y * eye.y - v.z * eye.z,
		w.x, w.y, w.z, -w.x * eye.x - w.y * eye.y - w.z * eye.z,
		0, 0, 0, 1));
}

Transform::Transform()
{

}

Transform::~Transform()
{

}