#pragma once
#include "lighting.h"
#include "manual_model.h"
#include "model.cpp"
#include "shader.cpp"
#include "camera.cpp"

#define NUM_TREES 100
#define NUM_ROCKS 50
#define NUM_RAINDROPS 500
#define root3 1.732051f
#define random(x) (rand()%x)

class imported_model
{
public:
    imported_model();
    ~imported_model();

    void draw(Shader modelShader, Camera camera, float currentFrame, bool daylight, bool flashlight, bool raining, glm::mat4 model, glm::mat4 view, glm::mat4 projection, manual_model manual_models, GLFWwindow* window);
    glm::mat4 get_eagleMatrix();
private:
    lighting lighting;

    Model maintempleModel;
    Model skyboxModel;
    Model torchModel;
    Model eagleModel;
    Model treeModel;
    Model rockModel;
    Model moonModel;
    Model raindropModel;

    glm::mat4 eagleMatrix;
};
