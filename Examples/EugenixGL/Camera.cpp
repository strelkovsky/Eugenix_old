#include "Includes.h"
#include "Camera.h"

void Camera::SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar)
{
	_projection = glm::perspective(fov, aspect, zNear, zFar);
}

void Camera::LookAt(glm::vec3& eye, glm::vec3& center, glm::vec3& up)
{
	_view = glm::lookAt(eye, center, up);
}

CameraPtr Perspective(float fov, float aspect, float zNear, float zFar)
{
	Camera cam;
	cam.SetPerspectiveProjection(fov, aspect, zNear, zFar);

	return std::make_shared<Camera>(cam);
}

CameraPtr Ortho()
{
	return std::make_shared<Camera>();
}