//22 / Febrero / 2026
//Reyes Carrillo Laura
//320015764
//Practica 3: Proyecciones, transformaciones y Shaders
// Hacer la misma cantidad de cubos que la cantidad de letras en mi nombre
//Previo 3 Proyecciones, transformaciones y Shaders

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    //Verificaci�n de compatibilidad
    // Set all the required options for GLFW
    /*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Reyes Carrillo Laura Proyecciones y transformaciones basicas", nullptr, nullptr);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    //Verificaci�n de errores de creacion  ventana
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;

    //Verificaci�n de errores de inicializaci�n de glew
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define las dimensiones del viewport
    glViewport(0, 0, screenWidth, screenHeight);

    // Setup OpenGL options
    glEnable(GL_DEPTH_TEST);

    // enable alpha support
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Build and compile our shader program
    Shader ourShader("Shader/core.vs", "Shader/core.frag");

    // use with Perspective Projection
    float vertices[] = {
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
         0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
         0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
        -0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

        -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
         0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
         0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
         0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
        -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
        -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f,1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f,1.0f,
         0.5f,  0.5f, -0.5f, 0.0f, 0.0f,1.0f,
         0.5f,  0.5f,  0.5f, 0.0f, 0.0f,1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 0.0f,1.0f,

        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,0.0f,
        -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,0.0f,
        -0.5f, -0.5f, -0.5f, 1.0f, 1.0f,0.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
         0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
        -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,

        -0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
         0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
        -0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
        -0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Enlazar  Vertex Array Object
    glBindVertexArray(VAO);

    //2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 4. Despues colocamos las caracteristicas de los vertices

    //Posicion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    //Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0); // Unbind VAO

    glm::mat4 projection = glm::mat4(1.0f);
    //definimos proyecciones
    // IMPORTANTE: glm::perspective usa radianes, por eso usamos glm::radians(45.0f)
    projection = glm::perspective(glm::radians(45.0f),
        (float)screenWidth / (float)screenHeight,
        0.1f, 100.0f);

    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        glClearColor(0.95f, 0.95f, 0.95f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // mandamos la inofrmacion a la parte del shader
        ourShader.Use();

        // Se crean matrices view (camara)
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(1.0f, -1.5f, -15.0f));

        // comunicacion por medio de las variables uniform
        GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
        GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
        GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

        // Enviamos projection y view UNA SOLA VEZ por frame
        glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // --------- Transformaciones por cubo (cada uno diferente) ---------
        // Base de escalera: cada cubo se desplaza para "pegar" el siguiente (efecto visual)
        glm::vec3 basePos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 step = glm::vec3(-0.55f, 1.05f, -0.55f); // ajuste visual

        // Escalas (todos diferentes, el ultimo es el mas grande)
        float scales[5] = { 0.55f, 0.75f, 0.95f, 1.20f, 2.0f };

        // Rotaciones distintas (grados) para cada cubo
        float rotY[5] = { 15.0f, 25.0f, 30.0f, 35.0f, 35.0f };
        float rotX[5] = { 8.0f, 10.0f, 12.0f, 14.0f, 14.0f };
        float rotZ[5] = { 0.0f,  0.0f,  0.0f,  0.0f, 45.0f }; // el ultimo en rombo

        for (int i = 0; i < 5; i++)
        {
            // ======= CUBOS PEQUEÑOS (0..3) =======
            if (i < 4)
            {
                glm::vec3 pos = basePos + step * (float)i;

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, pos);

                model = glm::rotate(model, glm::radians(rotY[i]), glm::vec3(0.0f, 1.0f, 0.0f));
                model = glm::rotate(model, glm::radians(rotX[i]), glm::vec3(1.0f, 0.0f, 0.0f));
                model = glm::rotate(model, glm::radians(rotZ[i]), glm::vec3(0.0f, 0.0f, 1.0f));

                float s = scales[i];
                model = glm::scale(model, glm::vec3(s, s, s));

                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            // ======= CUBO GRANDE (i==4) CON CONTACTO EXACTO =======
            else
            {
                int prev = 3;

                // --- 1) MODEL del cubo anterior (i=3) ---
                glm::vec3 posPrev = basePos + step * (float)prev;

                glm::mat4 prevModel = glm::mat4(1.0f);
                prevModel = glm::translate(prevModel, posPrev);
                prevModel = glm::rotate(prevModel, glm::radians(rotY[prev]), glm::vec3(0.0f, 1.0f, 0.0f));
                prevModel = glm::rotate(prevModel, glm::radians(rotX[prev]), glm::vec3(1.0f, 0.0f, 0.0f));
                prevModel = glm::rotate(prevModel, glm::radians(rotZ[prev]), glm::vec3(0.0f, 0.0f, 1.0f));
                prevModel = glm::scale(prevModel, glm::vec3(scales[prev], scales[prev], scales[prev]));

                // Punto objetivo: centro de la cara superior del cubo anterior (local: 0, +0.5, 0)
                glm::vec3 targetPoint = glm::vec3(prevModel * glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));

                // --- 2) Rotación y escala del cubo grande ---
                float s = scales[4];

                glm::mat4 R = glm::mat4(1.0f);
                R = glm::rotate(R, glm::radians(rotY[4]), glm::vec3(0.0f, 1.0f, 0.0f));
                R = glm::rotate(R, glm::radians(rotX[4]), glm::vec3(1.0f, 0.0f, 0.0f));
                R = glm::rotate(R, glm::radians(rotZ[4]), glm::vec3(0.0f, 0.0f, 1.0f)); // rombo (45°)

                glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(s, s, s));

                // --- 3) Esquina inferior del cubo grande (local) ---
                // Puedes cambiar esta esquina si quieres que apoye hacia otro lado:
                // (-0.5, -0.5, 0.5) o (0.5, -0.5, -0.5) o (-0.5, -0.5, -0.5)
                glm::vec3 cornerLocal = glm::vec3(0.5f, -0.5f, 0.5f);

                // Offset de esa esquina en mundo (sin traslación), después de R y S
                glm::vec3 cornerWorldOffset = glm::vec3((R * S) * glm::vec4(cornerLocal, 1.0f));

                // --- 4) Traslación EXACTA para que la esquina caiga en el centro de la cara superior del cubo anterior ---
                glm::vec3 T = targetPoint - cornerWorldOffset;

                // --- 5) Model final del cubo grande ---
                glm::mat4 bigModel = glm::mat4(1.0f);
                bigModel = glm::translate(bigModel, T);
                bigModel = bigModel * R;
                bigModel = bigModel * S;

                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(bigModel));
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        glBindVertexArray(0);

        // Swap the screen buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return EXIT_SUCCESS;
}