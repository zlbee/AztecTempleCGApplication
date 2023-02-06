#pragma once
#include "imported_model.h"

#define NUM_TREES 100
#define NUM_ROCKS 50
#define root3 1.732051f
#define random(x) (rand()%x)

imported_model::imported_model()
{
    // load models
    maintempleModel = Model("../resources/objects/aztec/main temple/main_temple_fixed.obj");
    skyboxModel= Model("../resources/objects/aztec/skybox/skybox1.obj");
    torchModel= Model("../resources/objects/aztec/torch/firetorch.obj");
    eagleModel= Model("../resources/objects/aztec/eagle/eagle.obj");
    treeModel= Model("../resources/objects/aztec/tree/tree.obj");
    rockModel= Model("../resources/objects/aztec/rock/rock.obj");
    moonModel= Model("../resources/objects/aztec/moon2k/moon2k.obj");
    raindropModel = Model("../resources/objects/aztec/raindrop/raindrop.obj");
}

imported_model::~imported_model()
{
}

// draw imported models
void imported_model::draw(Shader modelShader, Camera camera, float currentFrame, bool daylight, bool flashlight, bool raining, glm::mat4 model, glm::mat4 view, glm::mat4 projection, manual_model manual_models, GLFWwindow* window)
{
    // draw the imported model
    modelShader.use();

    // uniform: material
    modelShader.setFloat("material.shininess", 32.0f);

    // uniform: light
    // view position
    modelShader.setVec3("viewPos", camera.Position);
    // directional light
    lighting.specify_directional_light(modelShader, daylight);
    // point lights
    lighting.specify_point_lights(modelShader, currentFrame, daylight);
    // spotlight
    lighting.specify_spotlight(modelShader, camera, daylight, flashlight);


    // uniform: model, view, projection
    modelShader.setMat4("projection", projection);
    modelShader.setMat4("view", view);
    modelShader.setMat4("model", model);

    // transform: skybox
    glm::mat4 skyboxModelMatrix = model;
    skyboxModelMatrix = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    skyboxModelMatrix = glm::translate(skyboxModelMatrix, glm::vec3(0.0f, -40.0f, 0.0f));
    modelShader.setMat4("model", skyboxModelMatrix);
    // draw the skybox
    skyboxModel.Draw(modelShader);

    // transform: main temple
    glm::mat4 maintempleModelMatrix = glm::translate(manual_models.get_base3ModelMatrix(), glm::vec3(0.0f, root3, 0.0f));
    modelShader.setMat4("model", maintempleModelMatrix);
    // draw the main temple
    maintempleModel.Draw(modelShader);

    // model: torches
    // transform: torches
    for (int i = -1; i <= 1; i += 2)
    {
        glm::mat4 torchModelMatrix = glm::translate(maintempleModelMatrix, glm::vec3(2.0f * i, 0.0f, 5.0f));
        modelShader.setMat4("model", torchModelMatrix);
        // draw the torch
        torchModel.Draw(modelShader);
    }
    for (int i = -1; i <= 1; i += 2)
    {
        glm::mat4 torchModelMatrix = glm::translate(manual_models.get_base2ModelMatrix(), glm::vec3(4.0f * i, root3, 11.0f));
        modelShader.setMat4("model", torchModelMatrix);
        // draw the torch
        torchModel.Draw(modelShader);
    }
    for (int i = -1; i <= 1; i += 2)
    {
        glm::mat4 torchModelMatrix = glm::translate(manual_models.get_base1ModelMatrix(), glm::vec3(4.0f * i, root3, 15.0f));
        modelShader.setMat4("model", torchModelMatrix);
        // draw the torch
        torchModel.Draw(modelShader);
    }

    // model: eagles
    // define rotation parameters
    GLfloat rotationRate = currentFrame * 36;
    glm::mat4 eagleModelMatrix;
    // transform: eagle
    for (int i = 0; i < 3; i++)
    {
        eagleModelMatrix = glm::translate(model, glm::vec3(0.0f, 20.0f, 0.0f));
        eagleModelMatrix = glm::rotate(eagleModelMatrix, glm::radians(-rotationRate + i * 36.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        eagleModelMatrix = glm::translate(eagleModelMatrix, glm::vec3(0.0f, 0.0f + i * 2.0f, 10.0f + i * 5.0f));
        modelShader.setMat4("model", eagleModelMatrix);
        // draw the eagle
        eagleModel.Draw(modelShader);
    }
    this->eagleMatrix = eagleModelMatrix;

    // model: trees
    srand(1);
    for (int i = 0; i < NUM_TREES; i++)
    {
        GLfloat rand_tree_pos = rand() / GLfloat(RAND_MAX);
        GLfloat rand_tree_size = 1.0f - rand() / GLfloat(RAND_MAX) / 2;
        // transform: tree
        glm::mat4 treeModelMatrix = glm::rotate(model, glm::radians(360.0f * rand_tree_pos), glm::vec3(0.0f, 1.0f, 0.0f));
        treeModelMatrix = glm::translate(treeModelMatrix, glm::vec3(0.0f, 0.0f, 30.0f + 1.0f * random(10)));
        treeModelMatrix = glm::scale(treeModelMatrix, glm::vec3(1.0f * rand_tree_size, 1.0f * rand_tree_size, 1.0f * rand_tree_size));
        modelShader.setMat4("model", treeModelMatrix);
        // draw the tree
        treeModel.Draw(modelShader);
    }

    // model: rocks
    for (int i = 0; i < NUM_ROCKS; i++)
    {
        GLfloat rand_rock_pos = rand() / GLfloat(RAND_MAX);
        GLfloat rand_rock_size = 1.0f - rand() / GLfloat(RAND_MAX) / 2;
        GLfloat rand_rock_posture = rand() / GLfloat(RAND_MAX);
        // transform: rocks
        glm::mat4 rockModelMatrix = glm::rotate(model, glm::radians(360.0f * rand_rock_pos), glm::vec3(0.0f, 1.0f, 0.0f));
        rockModelMatrix = glm::translate(rockModelMatrix, glm::vec3(0.0f, 0.0f, 30.0f + 1.0f * random(10)));
        rockModelMatrix = glm::scale(rockModelMatrix, glm::vec3(1.0f * rand_rock_size, 1.0f * rand_rock_size, 1.0f * rand_rock_size));
        rockModelMatrix = glm::rotate(rockModelMatrix, glm::radians(360.0f * rand_rock_posture), glm::vec3(0.0f, 1.0f, 0.0f));
        modelShader.setMat4("model", rockModelMatrix);
        // draw the rock
        rockModel.Draw(modelShader);
    }

    // model: moon
    // draw in the night mode
    if (!daylight)
    {
        // transform: moon
        glm::mat4 moonModelMatrix = glm::translate(model, glm::vec3(0.0f, 0.0f, -45.0f));
        moonModelMatrix = glm::rotate(moonModelMatrix, glm::radians(-rotationRate), glm::vec3(0.0f, 0.0f, 1.0f));
        moonModelMatrix = glm::translate(moonModelMatrix, glm::vec3(0.0f, 50.0f, 0.0f));
        modelShader.setMat4("model", moonModelMatrix);
        // draw the moon
        moonModel.Draw(modelShader);
    }

    // model: raindrops
    if (raining)
    {
        srand(1);
        glm::mat4 raindropModelMatrix = glm::translate(model, glm::vec3(-50.0f, 80.0f, -50.0f)); // specify initial position
        float drop_distance = currentFrame * 50; // specify speed
        for (int i = 0; i < NUM_RAINDROPS; i++)
        {
            GLfloat rand_pos_x = rand() / GLfloat(RAND_MAX) * 100.0f; // specify random position in x
            GLfloat rand_pos_y = rand() / GLfloat(RAND_MAX) * 80.0f;  // specify random position in y
            GLfloat rand_pos_z = rand() / GLfloat(RAND_MAX) * 100.0f; // specify random position in z
            glm::mat4 raindropModelMatrix_temp = glm::translate(raindropModelMatrix,
                glm::vec3(rand_pos_x,
                    rand_pos_y - ((int)drop_distance % (80 + (int)rand_pos_y)),
                    rand_pos_z));
            modelShader.setMat4("model", raindropModelMatrix_temp);
            // draw the raindrop
            raindropModel.Draw(modelShader);
        }
    }

}

glm::mat4 imported_model::get_eagleMatrix()
{
    return this->eagleMatrix;
}
