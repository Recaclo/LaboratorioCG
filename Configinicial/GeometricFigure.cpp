// Laura Reyes Carrillo
// Sol con triangulos: dodecagono (12 triángulos) + 1 rayo
// Practica 2 - Computacion Grafica

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
    // 1) Inicializamos GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to init GLFW\n";
        return EXIT_FAILURE;
    }

    // 2) Creamos la ventana
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
        "Reyes Carrillo Laura - Sol (dodecagono + 1 rayo)",
        NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // 3) Callback resize
    glfwSetFramebufferSizeCallback(window, resize);

    // 4) Contexto actual
    glfwMakeContextCurrent(window);

    // 5) Inicializamos GLEW
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialise GLEW\n";
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Info
    std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // 6) Shaders desde archivos
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // =========================================================
    // VERTICES (x,y,z,r,g,b)
    // NOTA: aqui estás usando indices 0..15 (16 vertices)
    // 0 = centro
    // 1..12 = dodecagono
    // 13..15 = 1 rayo (base 13,14 y punta 15)
    // =========================================================
    float vertices[] = {
        // centro
        0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   // 0

        // dodecagono (12 puntos)
        0.4f,   0.1f, 0.0f,  1.0f, 1.0f, 0.0f,   // 1
        0.4f,  -0.1f, 0.0f,  1.0f, 1.0f, 0.0f,   // 2
        0.29f, -0.29f,0.0f,  1.0f, 1.0f, 0.0f,   // 3
        0.1f,  -0.4f, 0.0f,  1.0f, 1.0f, 0.0f,   // 4
       -0.1f,  -0.4f, 0.0f,  1.0f, 1.0f, 0.0f,   // 5
       -0.29f, -0.29f,0.0f,  1.0f, 1.0f, 0.0f,   // 6
       -0.4f,  -0.1f, 0.0f,  1.0f, 1.0f, 0.0f,   // 7
       -0.4f,   0.1f, 0.0f,  1.0f, 1.0f, 0.0f,   // 8
       -0.29f,  0.29f,0.0f,  1.0f, 1.0f, 0.0f,   // 9
       -0.1f,   0.4f, 0.0f,  1.0f, 1.0f, 0.0f,   // 10
        0.1f,   0.4f, 0.0f,  1.0f, 1.0f, 0.0f,   // 11
        0.29f,  0.29f,0.0f,  1.0f, 1.0f, 0.0f,   // 12

        // rayo (primer rayo a la derecha)
        0.44f,  0.1f, 0.0f,  1.0f, 0.6f, 0.0f,   // 13 base arriba
        0.44f, -0.1f, 0.0f,  1.0f, 0.6f, 0.0f,   // 14 base abajo
        0.85f,  0.0f, 0.0f,  1.0f, 0.6f, 0.0f    // 15 punta
    };

    // =========================================================
    // INDICES: 12 triángulos del centro + 1 triángulo del rayo
    // Cada 3 índices = 1 triángulo
    // =========================================================
    unsigned int indices[] = {
        // Centro (12 triángulos)
        0,  1,  2,
        0,  2,  3,
        0,  3,  4,
        0,  4,  5,
        0,  5,  6,
        0,  6,  7,
        0,  7,  8,
        0,  8,  9,
        0,  9, 10,
        0, 10, 11,
        0, 11, 12,
        0, 12,  1,

        // 1 rayo (triángulo): base (13,14) + punta (15)
        13, 14, 15
    };

    // =========================================================
    // VAO/VBO/EBO
    // =========================================================
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // VBO: vertices
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO: indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Atributo 0: posición
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Atributo 1: color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // =========================================================
    // LOOP
    // =========================================================
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.Use();
        glBindVertexArray(VAO);

        // (Opcional) dibujar puntos para verificar
        //glPointSize(6.0f);
        glDrawArrays(GL_POINTS, 0, 16);

        // Dibuja todos los triángulos definidos en indices[]
        // total indices = (12*3) + 3 = 39
        glDrawElements(GL_TRIANGLES, 39, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}