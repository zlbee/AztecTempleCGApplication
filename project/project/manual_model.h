#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include "lighting.h"
#include "shader.cpp"
#include "camera.cpp"

#define STEP_NUM 4

class manual_model
{
public:
	manual_model();
	void draw(Shader lightShader, Camera camera, float currentFrame, bool daylight, bool flashlight, const glm::mat4 model, const glm::mat4 view, const glm::mat4 projection);

	glm::mat4 get_base1ModelMatrix();
	glm::mat4 get_base2ModelMatrix();
	glm::mat4 get_base3ModelMatrix();

private:
	lighting lighting;

	unsigned int base1_vao;
	unsigned int base2_vao;
	unsigned int base3_vao;
	unsigned int enclosure_vao;
	unsigned int cube_vao;
	unsigned int ground_vao;

	unsigned int base_texBuffer;
	unsigned int enclosure_texBuffer;
	unsigned int ground_texBuffer;

	glm::mat4 base1ModelMatrix;
	glm::mat4 base2ModelMatrix;
	glm::mat4 base3ModelMatrix;

	unsigned int load_vertex_data(float* vertices, int size_arr);
	unsigned int load_vertex_data_wnormals(float* vertices, int size_arr);
	unsigned int load_texture(const char* filename, GLint internalFormat, GLenum format, int textureSlot);
	void load_vertex_datas();
	void load_texture_datas();


};

