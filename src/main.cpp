
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int SCREEN_WIDTH = 3440;
const int SCREEN_HEIGHT = 1440;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos; \n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
    "}\0";
const char *altFragmentShaderSource = R"(
    #version 330 core

    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
    }
)";


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);           
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}
int main()
{    
    // -- WINDOW CREATION
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // --

    // -- SHADER CREATION & COMPILATION
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);            
        std::cout << "ERROR: SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER::FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;                        
    }

    unsigned int altFragmentShader;
    altFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(altFragmentShader, 1, &altFragmentShaderSource, NULL);
    glCompileShader(altFragmentShader);

    glGetShaderiv(altFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(altFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER::ALT_FRAGMENT:COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;                        
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    unsigned int altShaderProgram;
    altShaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glAttachShader(altShaderProgram, vertexShader);
    glAttachShader(altShaderProgram, altFragmentShader);
    glLinkProgram(altShaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER::PROGRAM:COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    glGetProgramiv(altShaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(altShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER::ALT_PROGRAM:COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    glDeleteShader(vertexShader);    
    glDeleteShader(fragmentShader);
    glDeleteShader(altFragmentShader);
    // --


    float firstTriangle[] = 
    {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f, 
        0.25f, 0.5f, 0.0f,

    };
    float secondTriangle[] = 
    {
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.0f, 0.0f,
        -0.25f, 0.5f, 0.0f
    };

    // -- VERTEX BUFFER OBJECT & VERTEX ARRAY OBJECT CREATION & CONFIGURATION
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);    
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    // -- 

    // -- RENDER LOOP
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);    

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(altShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();                
    }
    // -- 

    // -- CLEANUP
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);

    glDeleteProgram(shaderProgram);
    glDeleteProgram(altShaderProgram);

    glfwTerminate();
    // --
    
    return 0;    
}