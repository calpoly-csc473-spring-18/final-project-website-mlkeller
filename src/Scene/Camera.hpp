
// Copyright (C) 2018 Ian Dunn
// For conditions of distribution and use, see the LICENSE file


#pragma once

#include <glm/glm.hpp>

#include <RayTracer/Ray.hpp>


class Camera
{

public:

	const glm::vec3 & GetPosition() const;
	const glm::vec3 & GetViewVector() const;
	const glm::vec3 & GetUpVector() const;
	const glm::vec3 & GetRightVector() const;
	const glm::vec3 & GetLookAt() const;

	void SetPosition(const glm::vec3 & position);
	void SetLookAt(const glm::vec3 & LookAt);
	void SetUpVector(const glm::vec3 & upVector);
	void SetRightVector(const glm::vec3 & rightVector);

	static glm::vec2 PixelToView(const glm::ivec2 & Pixel, const glm::ivec2 & imageSize);
	Ray GetPixelRay(const glm::ivec2 & pixel, const glm::ivec2 & imageSize,
		const glm::ivec2 & sample = glm::ivec2(0), const int sampleCount = 1) const;

protected:

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 view = glm::vec3(0, 0, 1);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 right = glm::vec3(1, 0, 0);
	glm::vec3 lookAt = glm::vec3(0, 0, 1);

};
