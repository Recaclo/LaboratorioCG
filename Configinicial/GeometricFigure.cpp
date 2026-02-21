// Laura Reyes Carrillo
// Sol con triangulos: dodecagono (12 triángulos) + 12 rayos
// Practica 2 - Computacion Grafica

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

// Callback: GLFW llama cuando cambia el tamaño de la ventana
void resize(GLFWwindow* window, int width, int height);

// Tamaño inicial de la ventana
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
    GLFWwindow* window = glfwCreateWindow(
        WIDTH, HEIGHT,
        "Reyes Carrillo Laura - Sol (dodecagono + 12 rayos)",
        NULL, NULL
    );

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
    // 0 = centro
    // 1..12 = dodecagono (tus puntos)
    // 13..24 = anillo externo (bases de rayos)
    // 25..36 = puntas de los 12 rayos
    // Total = 37 vertices
    // =========================================================
    float vertices[] = {
        // centro
        0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 0.0f,   // 0

        // dodecagono (12 puntos) - TUS PUNTOS
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

        // =====================================================
        // BASES DE RAYOS (anillo externo) 13..24
        // =====================================================
        0.44f,  0.10f, 0.0f,  1.0f, 0.75f, 0.0f,  // 13
        0.44f, -0.10f, 0.0f,  1.0f, 0.75f, 0.0f,  // 14
        0.33f, -0.31f, 0.0f,  1.0f, 0.75f, 0.0f,  // 15
        0.12f, -0.43f, 0.0f,  1.0f, 0.75f, 0.0f,  // 16
       -0.12f, -0.43f, 0.0f,  1.0f, 0.75f, 0.0f,  // 17
       -0.33f, -0.31f, 0.0f,  1.0f, 0.75f, 0.0f,  // 18
       -0.44f, -0.10f, 0.0f,  1.0f, 0.75f, 0.0f,  // 19
       -0.44f,  0.10f, 0.0f,  1.0f, 0.75f, 0.0f,  // 20
       -0.33f,  0.31f, 0.0f,  1.0f, 0.75f, 0.0f,  // 21
       -0.12f,  0.43f, 0.0f,  1.0f, 0.75f, 0.0f,  // 22
        0.12f,  0.43f, 0.0f,  1.0f, 0.75f, 0.0f,  // 23
        0.33f,  0.31f, 0.0f,  1.0f, 0.75f, 0.0f,  // 24

        // =====================================================
        // PUNTAS DE RAYOS 25..36
        // =====================================================
        0.85f,  0.00f, 0.0f,  1.0f, 0.55f, 0.0f,  // 25 (rayo 1)
        0.75f, -0.42f, 0.0f,  1.0f, 0.55f, 0.0f,  // 26 (rayo 2)
        0.41f, -0.79f, 0.0f,  1.0f, 0.55f, 0.0f,  // 27 (rayo 3)
        0.00f, -0.85f, 0.0f,  1.0f, 0.55f, 0.0f,  // 28 (rayo 4)
       -0.41f, -0.79f, 0.0f,  1.0f, 0.55f, 0.0f,  // 29 (rayo 5)
       -0.75f, -0.42f, 0.0f,  1.0f, 0.55f, 0.0f,  // 30 (rayo 6)
       -0.85f,  0.00f, 0.0f,  1.0f, 0.55f, 0.0f,  // 31 (rayo 7)
       -0.75f,  0.42f, 0.0f,  1.0f, 0.55f, 0.0f,  // 32 (rayo 8)
       -0.41f,  0.79f, 0.0f,  1.0f, 0.55f, 0.0f,  // 33 (rayo 9)
        0.00f,  0.85f, 0.0f,  1.0f, 0.55f, 0.0f,  // 34 (rayo 10)
        0.41f,  0.79f, 0.0f,  1.0f, 0.55f, 0.0f,  // 35 (rayo 11)
        0.75f,  0.42f, 0.0f,  1.0f, 0.55f, 0.0f   // 36 (rayo 12)
    };

    // =========================================================
    // INDICES:
    // - 12 triángulos del centro
    // - 12 triángulos de rayos
    // Total = 24 triangulos = 72 indices
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

        // Rayos (12 triángulos)
        13, 14, 25,  // rayo 1
        14, 15, 26,  // rayo 2
        15, 16, 27,  // rayo 3
        16, 17, 28,  // rayo 4
        17, 18, 29,  // rayo 5
        18, 19, 30,  // rayo 6
        19, 20, 31,  // rayo 7
        20, 21, 32,  // rayo 8
        21, 22, 33,  // rayo 9
        22, 23, 34,  // rayo 10
        23, 24, 35,  // rayo 11
        24, 13, 36   // rayo 12 (cierra)
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

        // Dibuja puntos para verificar (opcional)
        // glPointSize(6.0f);
        glDrawArrays(GL_POINTS, 0, 37);

        // Dibuja todos los triángulos: 72 indices
        glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

// Callback resize
void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}