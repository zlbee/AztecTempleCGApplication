#pragma once

#include "shader.cpp"
#include "camera.cpp"

#define FIRE_COLOR glm::vec3(100.0f / 255.0f, 48.0 / 255.0f, 48.0 / 255.0f)
#define SPOTLIGHT_STRENGTH 1.0f

class lighting
{
public:
	lighting();
	void specify_directional_light(Shader shader, bool on_off);
	void specify_point_lights(Shader shader, float currentFrame, bool on_off);
	void specify_spotlight(Shader shader, Camera camera, bool on_off, bool flashlight);
private:
	glm::vec3 fire_color;
	GLfloat spotlight_color;

	void specify_point_light(Shader shader, int index, glm::vec3 position, glm::vec3 color);
	
};

