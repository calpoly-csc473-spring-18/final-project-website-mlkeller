
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#include "Camera.hpp"


const glm::vec3 & Camera::GetPosition() const
{
	return position;
}

const glm::vec3 & Camera::GetViewVector() const
{
	return view;
}

const glm::vec3 & Camera::GetUpVector() const
{
	return up;
}

const glm::vec3 & Camera::GetRightVector() const
{
	return right;
}

const glm::vec3 & Camera::GetLookAt() const
{
	return lookAt;
}

void Camera::SetPosition(const glm::vec3 & position)
{
	this->position = position;
}

//#define POVRAY_BASIS_VECTORS

void Camera::SetLookAt(const glm::vec3 & lookAt)
{
	this->lookAt = lookAt;

#ifdef POVRAY_BASIS_VECTORS
	float const FocalLength = 1.f;
	float const RightLength = glm::length(right);
	float const UpLength = glm::length(up);
	float const Handedness = glm::dot(glm::cross(up, view), right);

	view = glm::normalize(lookAt - position);

	right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), view));
	up = glm::normalize(glm::cross(view, right));

	view *= FocalLength;
	right *= RightLength;
	up *= UpLength;

	if (Handedness < 0.0)
	{
		right *= -1;
	}
#else
	view = glm::normalize(lookAt - position);
#endif
}

void Camera::SetUpVector(const glm::vec3 & upVector)
{
	up = upVector;
}

void Camera::SetRightVector(const glm::vec3 & rightVector)
{
	right = rightVector;
}

glm::vec2 Camera::PixelToView(const glm::ivec2 & pixel, const glm::ivec2 & imageSize)
{
	return (glm::vec2(pixel) + 0.5f) / glm::vec2(imageSize) - 0.5f;
}

Ray Camera::GetPixelRay(const glm::ivec2 & pixel, const glm::ivec2 & ScreenSize, const glm::ivec2 & sample, const int sampleCount) const
{
	Ray ray;

	glm::vec2 const viewSpace = PixelToView(pixel * sampleCount + sample, ScreenSize * sampleCount);

	ray.origin = position;
	ray.direction = glm::normalize(right * viewSpace.x + up * viewSpace.y + view);

	return ray;
}
