#pragma once

struct Color final
{
	float r, g, b, a;
};

enum ClearBits : uint32_t
{
	ColorBit = GL_COLOR_BUFFER_BIT,
	DepthBit = GL_DEPTH_BUFFER_BIT,
	All = ColorBit | DepthBit
};

struct Camera final
{
	Camera() {}
	~Camera() {}

	void SetPerspectiveProjection(float fov, float aspect, float zNear, float zFar);
	void LookAt(glm::vec3& eye, glm::vec3& center, glm::vec3& up);

	void SetClearMask(uint32_t mask) { _clearMask = mask; }
	const uint32_t GetClearMask() const { return _clearMask; }
	
	void SetClearColor(Color col) { _clearColor = col; }
	const Color GetClearColor() const { return _clearColor; }

	const glm::mat4& GetProjection() const { return _projection; }
	const glm::mat4& GetView() const { return _view; }

private:
	glm::mat4 _view;
	glm::mat4 _projection;

	uint32_t _clearMask;
	Color _clearColor;
};
using CameraPtr = std::shared_ptr<Camera>;

CameraPtr Perspective(float fov, float aspect, float zNear, float zFar);
CameraPtr Ortho();