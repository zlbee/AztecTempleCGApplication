#include "lighting.h"

#define root3 1.732051f

lighting::lighting() : fire_color(FIRE_COLOR), spotlight_color(SPOTLIGHT_STRENGTH)
{
}

// specify attributes of the directional light
void lighting::specify_directional_light(Shader shader, bool on_off)
{
    GLfloat daylight_strength;
    if (on_off)
        daylight_strength = 1.0f;
    else
        daylight_strength = 0.2f;
    shader.setVec3("dirLight.direction", -0.0f, -1.0f, -0.0f);
    shader.setVec3("dirLight.ambient", daylight_strength, daylight_strength, daylight_strength);
    shader.setVec3("dirLight.diffuse", 0.0f, 0.0f, 0.0f);
    shader.setVec3("dirLight.specular", 0.0f, 0.0f, 0.0f);
}

// specify attributes of point lights
void lighting::specify_point_lights(Shader shader, float currentFrame, bool on_off)
{
    // mutative brightness of point light 1-8
    srand((unsigned) time(0));
    GLfloat rand_offset = rand() / GLfloat(RAND_MAX) * 3.1415926f;
    GLfloat brightness_torchlight = sin((currentFrame + rand_offset) * 50) * 0.05f + 1.0f;

    // dynamic position of point light 9
    glm::mat4 moonModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
    moonModelMatrix = glm::rotate(moonModelMatrix, glm::radians(-currentFrame * 36), glm::vec3(0.0f, 0.0f, 1.0f));
    moonModelMatrix = glm::translate(moonModelMatrix, glm::vec3(0.0f, 50.0f, 0.0f));

    // turn on point lights
    if (!on_off)
    {
        // point light 1
        specify_point_light(shader, 0, glm::vec3(-2.0f, 6 * root3 + 2.0f, 5.0f), fire_color * brightness_torchlight);
        // point light 2
        specify_point_light(shader, 1, glm::vec3(2.0f, 6 * root3 + 2.0f, 5.0f), fire_color * brightness_torchlight);
        // point light 3             
        specify_point_light(shader, 2, glm::vec3(-4.0f, 4 * root3 + 2.0f, 11.0f), fire_color * brightness_torchlight);
        // point light 4             
        specify_point_light(shader, 3, glm::vec3(4.0f, 4 * root3 + 2.0f, 11.0f), fire_color * brightness_torchlight);
        // point light 5             
        specify_point_light(shader, 4, glm::vec3(-4.0f, 2 * root3 + 2.0f, 15.0f), fire_color * brightness_torchlight);
        // point light 6             
        specify_point_light(shader, 5, glm::vec3(4.0f, 2 * root3 + 2.0f, 15.0f), fire_color * brightness_torchlight);
        // point light 7
        specify_point_light(shader, 6, glm::vec3(moonModelMatrix[3][0], moonModelMatrix[3][1], moonModelMatrix[3][2] + 10.0f), glm::vec3(0.8f, 0.8f, 0.8f));
        shader.setFloat("pointLights[6].constant", 1.0f);
        shader.setFloat("pointLights[6].linear", 0.014f);
        shader.setFloat("pointLights[6].quadratic", 0.0007f);
    }
    // turn off point lights
    else
    {
        for (int i = 0; i < 9; i++)
            specify_point_light(shader, i, glm::vec3(0.0f), glm::vec3(0.0f));
    }
}

// specify attributes of a point light
void lighting::specify_point_light(Shader shader, int index, glm::vec3 position, glm::vec3 color)
{
    std::string pl_index = "pointLights[" + std::to_string(index) + "]";
    shader.setVec3(pl_index + ".position", position);
    shader.setVec3(pl_index + ".ambient", color);
    shader.setVec3(pl_index + ".diffuse", color);
    shader.setVec3(pl_index + ".specular", color);
    shader.setFloat(pl_index + ".constant", 1.0f);
    shader.setFloat(pl_index + ".linear", 0.35f);
    shader.setFloat(pl_index + ".quadratic", 0.44f);
}

// specify attributes of the spotlight
void lighting::specify_spotlight(Shader shader, Camera camera, bool on_off, bool flashlight)
{
    GLfloat spotlight_strength = 0.0f;
    if (on_off)
        spotlight_strength = 0.0f;
    else
        if (flashlight)
            spotlight_strength = SPOTLIGHT_STRENGTH;
        
    shader.setVec3("spotLight.position", camera.Position);
    shader.setVec3("spotLight.direction", camera.Front);
    shader.setVec3("spotLight.ambient", spotlight_strength, spotlight_strength, spotlight_strength);
    shader.setVec3("spotLight.diffuse", spotlight_strength, spotlight_strength, spotlight_strength);
    shader.setVec3("spotLight.specular", spotlight_strength, spotlight_strength, spotlight_strength);
    shader.setFloat("spotLight.constant", 1.0f);
    shader.setFloat("spotLight.linear", 0.09);
    shader.setFloat("spotLight.quadratic", 0.032);
    shader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
}
