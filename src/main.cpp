
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Shader.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int SCREEN_WIDTH = 3440;
const int SCREEN_HEIGHT = 1440;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float vertices[] = {
    // positions          // normals           // texcoords

    // back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,

    // front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

    // left face
    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

    // right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

    // bottom face
    -0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f,

    // top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);           
}

float lastX, lastY;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera->ProcessMouseMovement(xoffset, yoffset, true);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    camera->ProcessMouseScroll(yoffset);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->ProcessKeyboard(FORWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);
}
glm::vec3 lightPos(1.2f, 1.0f, -2.0f);
int main()
{
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f),
                    glm::vec3(0.0f, 1.0f, 0.0f),
                    YAW, PITCH);
        

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT
        , "LearnOpenGL", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetWindowPos(window, 0, 0);        
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, &camera);                    

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glEnable(GL_DEPTH_TEST);

    unsigned int VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);    

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //glGenBuffers(1, &EBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position atrribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader lightingShader("shaders/shader.vs", "shaders/shader.fs");
    lightingShader.use();
    lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lightingShader.setVec3("lightPos", lightPos.x, lightPos.y, lightPos.z);

    Shader lightCubeShader("shaders/lightShader.vs", "shaders/lightShader.fs");
    
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
 /*
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);    

    int width, height, nrChannels;    
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data;

    data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD" << std::endl;        
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD" << std::endl;
    }
    stbi_image_free(data);
*/    

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-75.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view = glm::mat4(1.0f);
    view = camera.GetViewMatrix();

    float aspect = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), aspect , 0.1f, 100.0f);

    unsigned int modelLoc = glGetUniformLocation(lightingShader.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int viewLoc = glGetUniformLocation(lightingShader.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

    unsigned int projectionLoc = glGetUniformLocation(lightingShader.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));     
    
    while (!glfwWindowShouldClose(window))
    {        
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);             

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);            
        
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), aspect, 0.1f, 100.0f);

        lightingShader.use();
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f));

        lightCubeShader.use();

        glUniformMatrix4fv(
            glGetUniformLocation(lightCubeShader.ID, "model"),
            1, GL_FALSE, glm::value_ptr(model)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(lightCubeShader.ID, "view"),
            1, GL_FALSE, glm::value_ptr(view)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(lightCubeShader.ID, "projection"),
            1, GL_FALSE, glm::value_ptr(projection)
        );

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();           
    }

    glDeleteVertexArrays(1,  &VAO);
    glDeleteBuffers(1, &VBO);    
    glDeleteProgram(lightingShader.ID);

    glfwTerminate();
    
    return 0;    
}
