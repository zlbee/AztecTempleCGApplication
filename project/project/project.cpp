// Zhangli Wang, 20028336
#pragma once

#include "manual_model.h"
#include "imported_model.h"
#include "lighting.h"

#include <iostream>

// settings
const unsigned int SCR_WIDTH = 1280;                                            // window width
const unsigned int SCR_HEIGHT = 800;                                            // window height
static bool daylight_on_off = true;                                             // set the initial directional light mode
static bool flashlight_on_off = true;                                           // set the intial flashlight mode
static bool raining_on_off = true;                                              // set the initial rianing mdoe
Camera camera(glm::vec3(0.0f, 15.0f, 40.0f));                                   // set the initial position of the camera

// camera initial parameters
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// model, view, projection matrixes
glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void processInput_Eagle(GLFWwindow* window, glm::mat4 eagleModelMatrix);

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Coursework3", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // shader for imported models
    Shader modelShader("./shaders/vertexShader.vert", "./shaders/fragShader.frag");
    // shader for manually drawn models
    Shader lightShader("./shaders/lightVertexShader.vert", "./shaders/lightFragShader.frag");

    // construct: lighting attributes
    lighting lighting;

    // construct: manually drawn models
    manual_model manual_models;

    // load external models
    imported_model imported_models;


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // presetting
        GLfloat daylight_strength = 1.0f;           // default: daylight
        GLfloat spotlight_strength = 0.0f;          // default: turn off spotlight
        float currentFrame = glfwGetTime();         // current frame
        deltaTime = currentFrame - lastFrame;       // delta frame
        lastFrame = currentFrame;                   // last frame

        // process input from keyboard/mouse
        processInput(window);

        // initialize model, view, projection matrixes
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
        view = camera.GetViewMatrix();
        model = glm::mat4(1.0f);

        // set scene attributes
        glClearColor(0.05f, 0.1f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // manually draw models
        manual_models.draw(lightShader, camera, currentFrame, daylight_on_off, flashlight_on_off, model, view, projection);

        // draw imported models
        imported_models.draw(modelShader, camera, currentFrame, daylight_on_off, flashlight_on_off, raining_on_off, model, view, projection, manual_models, window);

        // process input for the view point of the eagle
        processInput_Eagle(window, imported_models.get_eagleMatrix());

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}


#pragma region keyboard/mouse input
// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
    // close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // camera movements
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // set light mode
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
        daylight_on_off = false;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        daylight_on_off = true;

    // set view points
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        camera.SetViewPoint(glm::vec3(0.0f, 15.0f, 40.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        camera.SetViewPoint(glm::vec3(0.0f, 15.0f, -40.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 90.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        camera.SetViewPoint(glm::vec3(40.0f, 15.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        camera.SetViewPoint(glm::vec3(-40.0f, 15.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f);
    }

    // turn on/off flashlight
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        flashlight_on_off = true;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        flashlight_on_off = false;

    // turn on/off raining effect
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        raining_on_off = false;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        raining_on_off = true;
}

// set view point to the eagle
void processInput_Eagle(GLFWwindow* window, glm::mat4 eagleModelMatrix)
{
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        glm::vec3 new_position = glm::vec3(eagleModelMatrix[3][0], eagleModelMatrix[3][1] + 25.0f, eagleModelMatrix[3][2]);
        glm::vec3 new_front = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 new_up = glm::vec3(0.0f, 0.0f, -1.0f);
        float new_yaw = -90.0f;
        float new_pitch = -90.0f;
        camera.SetViewPoint(new_position, new_front, new_up, new_yaw, new_pitch);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
#pragma endregion
