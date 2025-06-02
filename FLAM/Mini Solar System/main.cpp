#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string loadShader(const char* path);
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;
bool firstMouse = true;
float fov = 45.0f;
glm::vec3 cameraPos(0.0f, 0.0f, 10.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Mini Solar System", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    GLuint basicShader = createShaderProgram("shader.vert", "shader.frag");
    GLuint sunShader = createShaderProgram("shader.vert", "sun_shader.frag");

    float vertices[] = {      
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float time = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        time += 0.01f;
        glfwPollEvents();
        glClearColor(0.01f, 0.01f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f/600.0f, 0.1f, 100.0f);

        glUseProgram(sunShader);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.5f));
        glUniformMatrix4fv(glGetUniformLocation(sunShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(sunShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(sunShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1f(glGetUniformLocation(sunShader, "time"), time);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(basicShader);
        model = glm::mat4(1.0f);
        model = glm::rotate(model, time, glm::vec3(0, 1, 0));
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        glUniformMatrix4fv(glGetUniformLocation(basicShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(basicShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(basicShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        model = glm::rotate(model, time * 2.0f, glm::vec3(0, 1, 0));
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(basicShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        model = glm::mat4(1.0f);
        model = glm::rotate(model, time * 0.5f, glm::vec3(0, 1, 0));
        model = glm::translate(model, glm::vec3(-5.0f, 0.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.6f));
        glUniformMatrix4fv(glGetUniformLocation(basicShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
