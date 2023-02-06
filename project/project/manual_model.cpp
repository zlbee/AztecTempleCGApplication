#pragma once

#include "manual_model.h"
#include "vertices_data.h"


#define root3 1.732051f

manual_model::manual_model()
{
    // load data
    load_vertex_datas();
    load_texture_datas();
}

void manual_model::draw(Shader lightShader, Camera camera, float currentFrame, bool daylight, bool flashlight, const glm::mat4 model, const glm::mat4 view, const glm::mat4 projection)
{
    lightShader.use();
    int step_num = STEP_NUM; // number of steps

    // uniform: light
    // view position
    lightShader.setVec3("viewPos", camera.Position);
    // directional light
    lighting.specify_directional_light(lightShader, daylight);
    // point lights
    lighting.specify_point_lights(lightShader, currentFrame, daylight);
    // spotLight
    lighting.specify_spotlight(lightShader, camera, daylight, flashlight);

    // uniform: model, view, projection
    lightShader.setMat4("projection", projection);
    lightShader.setMat4("view", view);
    lightShader.setMat4("model", model);

    // transform: first base
    glm::mat4 base1Model = glm::translate(model, glm::vec3(0.0f, root3, 0.0f));
    this->base1ModelMatrix = base1Model;
    lightShader.setMat4("model", base1Model);
    // bind textures   
    glActiveTexture(GL_TEXTURE15);
    glBindTexture(GL_TEXTURE_2D, base_texBuffer);
    glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 15);
    // draw the first base
    glBindVertexArray(base1_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // transform: second base
    glm::mat4 base2Model = glm::translate(base1Model, glm::vec3(0.0f, 2 * root3, 0.0f));
    this->base2ModelMatrix = base2Model;
    lightShader.setMat4("model", base2Model);
    glActiveTexture(GL_TEXTURE15);
    glBindTexture(GL_TEXTURE_2D, base_texBuffer);
    glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 15);
    // draw the second base
    glBindVertexArray(base2_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // transform: third base
    glm::mat4 base3Model = glm::translate(base2Model, glm::vec3(0.0f, 2 * root3, 0.0f));
    this->base3ModelMatrix = base3Model;
    lightShader.setMat4("model", base3Model);
    glActiveTexture(GL_TEXTURE15);
    glBindTexture(GL_TEXTURE_2D, base_texBuffer);
    glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 15);
    // draw the third base
    glBindVertexArray(base3_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    for (int i = 0; i < 4; i++)
    {
        glm::mat4 benchmark1 = glm::rotate(base1Model, glm::radians(i * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 benchmark2 = glm::rotate(base2Model, glm::radians(i * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 benchmark3 = glm::rotate(base3Model, glm::radians(i * 90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        // transform: first base steps
        glm::mat4 step1Model;
        step1Model = glm::translate(benchmark1, glm::vec3(0.0f, -root3, 18.0f));
        step1Model = glm::rotate(step1Model, glm::radians(120.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        step1Model = glm::translate(step1Model, glm::vec3(0.0f, 0.0f, -4.0f / step_num / 2));
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        for (int i = 1; i < step_num + 1; i++)
        {
            glm::mat4 step1Model_temp = step1Model;
            step1Model_temp = glm::translate(step1Model, glm::vec3(0.0f, 0.0f, 4.0f / step_num * i));
            step1Model_temp = glm::rotate(step1Model_temp, glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            step1Model_temp = glm::scale(step1Model_temp, glm::vec3(4.0f, 2 * root3 / step_num, 2.0f / step_num));
            lightShader.setMat4("model", step1Model_temp);
            // draw the first base step
            glBindVertexArray(cube_vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // transform: left enclosure for the first base
        glm::mat4 enclosure1Model;
        enclosure1Model = glm::translate(benchmark1, glm::vec3(2.0f, 0.0f, 17.0f));
        enclosure1Model = glm::rotate(enclosure1Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure1Model = glm::translate(enclosure1Model, glm::vec3(0.0f, -root3 / 2, 0.0f));
        enclosure1Model = glm::scale(enclosure1Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure1Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        // transform: left enclosure for the first base
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // transform: draw again
        enclosure1Model = glm::translate(benchmark1, glm::vec3(2.0f, root3 * 3 / 2, 14.0f));
        enclosure1Model = glm::rotate(enclosure1Model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure1Model = glm::scale(enclosure1Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure1Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: right enclosure for the first base
        glm::mat4 enclosure2Model;
        enclosure2Model = glm::translate(benchmark1, glm::vec3(-2.0f, 0.0f, 17.0f));
        enclosure2Model = glm::rotate(enclosure2Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure2Model = glm::translate(enclosure2Model, glm::vec3(0.0f, -root3 / 2, 0.0f));
        enclosure2Model = glm::scale(enclosure2Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure2Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // transform: draw again
        enclosure2Model = glm::translate(benchmark1, glm::vec3(-2.0f, root3 * 3 / 2, 14.0f));
        enclosure2Model = glm::rotate(enclosure2Model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure2Model = glm::scale(enclosure2Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure2Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: plane
        glm::mat4 planeModel;
        planeModel = glm::translate(benchmark1, glm::vec3(0.0f, root3, 14.0f));
        planeModel = glm::scale(planeModel, glm::vec3(4.0f, 0.05f, 4.0f));
        lightShader.setMat4("model", planeModel);
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the plane
        glBindVertexArray(cube_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: second base steps
        glm::mat4 step2Model;
        step2Model = glm::translate(benchmark2, glm::vec3(0.0f, -root3, 14.0f));
        step2Model = glm::rotate(step2Model, glm::radians(120.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        step2Model = glm::translate(step2Model, glm::vec3(0.0f, 0.0f, -4.0f / step_num / 2));
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        for (int i = 1; i < step_num + 1; i++)
        {
            glm::mat4 stepModel_temp = step1Model;
            stepModel_temp = glm::translate(step2Model, glm::vec3(0.0f, 0.0f, 4.0f / step_num * i));
            stepModel_temp = glm::rotate(stepModel_temp, glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            stepModel_temp = glm::scale(stepModel_temp, glm::vec3(4.0f, 2 * root3 / step_num, 2.0f / step_num));
            lightShader.setMat4("model", stepModel_temp);
            // draw the second base step
            glBindVertexArray(cube_vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // transform: left enclosure for the second base
        glm::mat4 enclosure3Model;
        enclosure3Model = glm::translate(benchmark2, glm::vec3(2.0f, 0.0f, 13.0f));
        enclosure3Model = glm::rotate(enclosure3Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure3Model = glm::translate(enclosure3Model, glm::vec3(0.0f, -root3 / 2, 0.0f));
        enclosure3Model = glm::scale(enclosure3Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure3Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // transform: draw again
        enclosure3Model = glm::translate(benchmark2, glm::vec3(2.0f, root3 * 3 / 2, 10.0f));
        enclosure3Model = glm::rotate(enclosure3Model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure3Model = glm::scale(enclosure3Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure3Model);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: right enclosure for the second base
        glm::mat4 enclosure4Model;
        enclosure4Model = glm::translate(benchmark2, glm::vec3(-2.0f, 0.0f, 13.0f));
        enclosure4Model = glm::rotate(enclosure4Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure4Model = glm::translate(enclosure4Model, glm::vec3(0.0f, -root3 / 2, 0.0f));
        enclosure4Model = glm::scale(enclosure4Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure4Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // transform: draw again
        enclosure4Model = glm::translate(benchmark2, glm::vec3(-2.0f, root3 * 3 / 2, 10.0f));
        enclosure4Model = glm::rotate(enclosure4Model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure4Model = glm::scale(enclosure4Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure4Model);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: plane
        glm::mat4 plane2Model;
        plane2Model = glm::translate(benchmark2, glm::vec3(0.0f, root3, 10.0f));
        plane2Model = glm::scale(plane2Model, glm::vec3(4.0f, 0.05f, 4.0f));
        lightShader.setMat4("model", plane2Model);
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the plane
        glBindVertexArray(cube_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: third base steps
        glm::mat4 step3Model;
        step3Model = glm::translate(benchmark3, glm::vec3(0.0f, -root3, 10.0f));
        step3Model = glm::rotate(step3Model, glm::radians(120.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        step3Model = glm::translate(step3Model, glm::vec3(0.0f, 0.0f, -4.0f / step_num / 2));
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        for (int i = 1; i < step_num + 1; i++)
        {
            glm::mat4 stepModel_temp = step3Model;
            stepModel_temp = glm::translate(step3Model, glm::vec3(0.0f, 0.0f, 4.0f / step_num * i));
            stepModel_temp = glm::rotate(stepModel_temp, glm::radians(120.0f), glm::vec3(1.0f, 0.0f, 0.0f));
            stepModel_temp = glm::scale(stepModel_temp, glm::vec3(4.0f, 2 * root3 / step_num, 2.0f / step_num));
            lightShader.setMat4("model", stepModel_temp);
            // draw the third base step
            glBindVertexArray(cube_vao);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // transform: left enclosure for the third base
        glm::mat4 enclosure5Model;
        enclosure5Model = glm::translate(benchmark3, glm::vec3(2.0f, 0.0f, 9.0f));
        enclosure5Model = glm::rotate(enclosure5Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure5Model = glm::translate(enclosure5Model, glm::vec3(0.0f, -root3 / 2, 0.0f));
        enclosure5Model = glm::scale(enclosure5Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure5Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // transform: right enclosure for the third base
        glm::mat4 enclosure6Model;
        enclosure6Model = glm::translate(benchmark3, glm::vec3(-2.0f, 0.0f, 9.0f));
        enclosure6Model = glm::rotate(enclosure6Model, glm::radians(240.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        enclosure6Model = glm::translate(enclosure6Model, glm::vec3(0.0f, -root3 / 2, 0.0f));
        enclosure6Model = glm::scale(enclosure6Model, glm::vec3(0.1f, 1.0f, 1.0f));
        lightShader.setMat4("model", enclosure6Model);
        // bind textures   
        glActiveTexture(GL_TEXTURE14);
        glBindTexture(GL_TEXTURE_2D, enclosure_texBuffer);
        glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 14);
        // draw the enclosure
        glBindVertexArray(enclosure_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // transform: ground
    glm::mat4 groundModel = model;
    lightShader.setMat4("model", groundModel);
    // bind textures
    glActiveTexture(GL_TEXTURE13);
    glBindTexture(GL_TEXTURE_2D, ground_texBuffer);
    glUniform1i(glGetUniformLocation(lightShader.ID, "theTexture"), 13);
    // draw the ground
    glBindVertexArray(ground_vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

unsigned int manual_model::load_vertex_data(float* vertices, int size_arr)
{
    // generate VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate VBO and assign data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * size_arr, vertices, GL_STATIC_DRAW);

    // coordinate
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture position
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return VAO;
}

unsigned int manual_model::load_vertex_data_wnormals(float* vertices, int size_arr)
{
    // generate VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate VBO and assign data
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * size_arr, vertices, GL_STATIC_DRAW);

    // coordinate
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture position
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    return VAO;
}

unsigned int manual_model::load_texture(const char* filename, GLint internalFormat, GLenum format, int textureSlot)
{
    // create and bind texture buffer
    unsigned int texBuffer;
    glGenTextures(1, &texBuffer);
    glActiveTexture(GL_TEXTURE0 + textureSlot);
    glBindTexture(GL_TEXTURE_2D, texBuffer);

    int width, height, nrChannel;
    // load image file
    unsigned char* data = stbi_load(filename, &width, &height, &nrChannel, 0);
    if (data)
    {
        // set texture attributes
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("load image failed.");
    }
    return texBuffer;
}

void manual_model::load_vertex_datas()
{
    // base1: load vertex data
    base1_vao = load_vertex_data_wnormals(base1_vertices_wnormals, sizeof(base1_vertices_wnormals));

    // base2: load vertex data
    base2_vao = load_vertex_data_wnormals(base2_vertices_wnormals, sizeof(base2_vertices_wnormals));

    // base3: load vertex data
    base3_vao = load_vertex_data_wnormals(base3_vertices_wnormals, sizeof(base3_vertices_wnormals));

    // enclosure: load vertex data
    enclosure_vao = load_vertex_data_wnormals(enclosure_vertices_wnormals, sizeof(enclosure_vertices_wnormals));

    //cube: load vertex data
    cube_vao = load_vertex_data_wnormals(cube_vertices_wnormals, sizeof(cube_vertices_wnormals));

    // ground: load vertex data
    ground_vao = load_vertex_data_wnormals(ground_vertices_wnormals, sizeof(ground_vertices_wnormals));
}

void manual_model::load_texture_datas()
{
    // load textures to the buffer
    base_texBuffer = load_texture("../resources/textures/stone_wall3.jpg", GL_RGB, GL_RGB, 15);
    enclosure_texBuffer = load_texture("../resources/textures/stone_wall1.jpg", GL_RGB, GL_RGB, 14);
    ground_texBuffer = load_texture("../resources/textures/grassland.jpg", GL_RGB, GL_RGB, 13);
}

glm::mat4 manual_model::get_base1ModelMatrix()
{
    return this->base1ModelMatrix;
}

glm::mat4 manual_model::get_base2ModelMatrix()
{
    return this->base2ModelMatrix;
}

glm::mat4 manual_model::get_base3ModelMatrix()
{
    return this->base3ModelMatrix;
}



