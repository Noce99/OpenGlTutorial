#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 2
//VAO = Vertex Array Objects
//VBO = Vertex Buffer Objects

float cameraX , cameraY, cameraZ;
GLuint renderingProgram; //GLuint è una shortcat per unsigned int
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

//Variabili allocate in init così non devono essere allocate durante il rendering
GLuint vLoc, mLoc, projLoc, tfLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;
/*
 * pMat : Perspective matrix
 * vMat : View matrix
 * mMat : Model matrix
 * mvMat : vMat*mMat
*/

void setupVertices(){
    float vertexPositions[108] = {  -1.0f, 1.0f, -1.0f,     -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,
                                    1.0f, -1.0f, -1.0f,     1.0f, 1.0f, -1.0f,      -1.0f, 1.0f, -1.0f,
                                    1.0f, -1.0f, -1.0f,     1.0f, -1.0f, 1.0f,      1.0f, 1.0f, -1.0f,
                                    1.0f, -1.0f, 1.0f,      1.0f, 1.0f, 1.0f,       1.0f, 1.0f, -1.0f,
                                    1.0f, -1.0f, 1.0f,      -1.0f, -1.0f, 1.0f,     1.0f, 1.0f, 1.0f,
                                    -1.0f, -1.0f, 1.0f,     -1.0f, 1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
                                    -1.0f, -1.0f, 1.0f,     -1.0f, -1.0f, -1.0f,    -1.0f, 1.0f, 1.0f,
                                    -1.0f, -1.0f, -1.0f,    -1.0f, 1.0f, -1.0f,     -1.0f, 1.0f, 1.0f,
                                    -1.0f, -1.0f, 1.0f,     1.0f, -1.0f, 1.0f,      1.0f, -1.0f, -1.0f, 
                                    1.0f, -1.0f, -1.0f,     -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f, 1.0f,
                                    -1.0f, 1.0f, -1.0f,     1.0f, 1.0f, -1.0f,      1.0f, 1.0f, 1.0f,
                                    1.0f, 1.0f, 1.0f,       -1.0f, 1.0f, 1.0f,      -1.0f, 1.0f, -1.0f  };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void init (GLFWwindow* window){
    renderingProgram = createShaderProgram((char *)"vertShader.glsl",(char *) "fragShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 25.0f;
    setupVertices();
}

void display (GLFWwindow* window, double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); //Clear the background to black
    glUseProgram(renderingProgram);
    
    //Prendo gli id delle uniform
    mLoc = glGetUniformLocation(renderingProgram, "m_matrix");
    vLoc = glGetUniformLocation(renderingProgram, "v_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    tfLoc = glGetUniformLocation(renderingProgram, "tf");
    
    //Costruisco la pMat
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees
    
    //Fattore che distingue un cubo dall'altro!
    double tf = currentTime;
        
    //Costruisco la vMat
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    
    //Costruisco la mMat (matrice identità)
    mMat = glm::mat4(1.0f);
    
    //Spedisco matrici allo shader
    glUniform1f(tfLoc, (float)tf);
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(mMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(vMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
        
    //Associazione VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 24);
}

int main(void){
    if (!glfwInit()) {exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "12_CubiRotanti", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK){exit(EXIT_FAILURE);}
    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
