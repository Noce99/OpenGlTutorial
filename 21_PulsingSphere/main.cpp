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
float cubeLocX, cubeLocY, cubeLocZ;
GLuint renderingProgram; //GLuint è una shortcat per unsigned int
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

//Variabili allocate in init così non devono essere allocate durante il rendering
GLuint mvLoc, projLoc, timeLoc;
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
    float vertexPositions[654] = {  -0.5f, 0.5f, 0.5f, -0.333333f, 0.5f, 0.5f, -0.166667f, 0.5f, 0.5f, -5.55112e-17f, 0.5f, 0.5f, 0.166667f, 0.5f, 0.5f, 0.333333f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 
-0.5f, 0.333333f, 0.5f, -0.333333f, 0.333333f, 0.5f, -0.166667f, 0.333333f, 0.5f, -5.55112e-17f, 0.333333f, 0.5f, 0.166667f, 0.333333f, 0.5f, 0.333333f, 0.333333f, 0.5f, 0.5f, 0.333333f, 0.5f, 
-0.5f, 0.166667f, 0.5f, -0.333333f, 0.166667f, 0.5f, -0.166667f, 0.166667f, 0.5f, -5.55112e-17f, 0.166667f, 0.5f, 0.166667f, 0.166667f, 0.5f, 0.333333f, 0.166667f, 0.5f, 0.5f, 0.166667f, 0.5f, 
-0.5f, 5.55112e-17f, 0.5f, -0.333333f, 5.55112e-17f, 0.5f, -0.166667f, 5.55112e-17f, 0.5f, -5.55112e-17f, 5.55112e-17f, 0.5f, 0.166667f, 5.55112e-17f, 0.5f, 0.333333f, 5.55112e-17f, 0.5f, 0.5f, 5.55112e-17f, 0.5f, 
-0.5f, -0.166667f, 0.5f, -0.333333f, -0.166667f, 0.5f, -0.166667f, -0.166667f, 0.5f, -5.55112e-17f, -0.166667f, 0.5f, 0.166667f, -0.166667f, 0.5f, 0.333333f, -0.166667f, 0.5f, 0.5f, -0.166667f, 0.5f, 
-0.5f, -0.333333f, 0.5f, -0.333333f, -0.333333f, 0.5f, -0.166667f, -0.333333f, 0.5f, -5.55112e-17f, -0.333333f, 0.5f, 0.166667f, -0.333333f, 0.5f, 0.333333f, -0.333333f, 0.5f, 0.5f, -0.333333f, 0.5f, 
-0.5f, -0.5f, 0.5f, -0.333333f, -0.5f, 0.5f, -0.166667f, -0.5f, 0.5f, -5.55112e-17f, -0.5f, 0.5f, 0.166667f, -0.5f, 0.5f, 0.333333f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 
-0.5f, 0.5f, 0.333333f, -0.333333f, 0.5f, 0.333333f, -0.166667f, 0.5f, 0.333333f, -5.55112e-17f, 0.5f, 0.333333f, 0.166667f, 0.5f, 0.333333f, 0.333333f, 0.5f, 0.333333f, 0.5f, 0.5f, 0.333333f, 
0.5f, 0.333333f, 0.333333f, 0.5f, 0.166667f, 0.333333f, 0.5f, 5.55112e-17f, 0.333333f, 0.5f, -0.166667f, 0.333333f, 0.5f, -0.333333f, 0.333333f, 0.5f, -0.5f, 0.333333f, 0.333333f, -0.5f, 0.333333f, 
0.166667f, -0.5f, 0.333333f, 5.55112e-17f, -0.5f, 0.333333f, -0.166667f, -0.5f, 0.333333f, -0.333333f, -0.5f, 0.333333f, -0.5f, -0.5f, 0.333333f, -0.5f, -0.333333f, 0.333333f, -0.5f, -0.166667f, 0.333333f, 
-0.5f, -5.55112e-17f, 0.333333f, -0.5f, 0.166667f, 0.333333f, -0.5f, 0.333333f, 0.333333f, -0.5f, 0.5f, 0.166667f, -0.333333f, 0.5f, 0.166667f, -0.166667f, 0.5f, 0.166667f, -5.55112e-17f, 0.5f, 0.166667f, 
0.166667f, 0.5f, 0.166667f, 0.333333f, 0.5f, 0.166667f, 0.5f, 0.5f, 0.166667f, 0.5f, 0.333333f, 0.166667f, 0.5f, 0.166667f, 0.166667f, 0.5f, 5.55112e-17f, 0.166667f, 0.5f, -0.166667f, 0.166667f, 
0.5f, -0.333333f, 0.166667f, 0.5f, -0.5f, 0.166667f, 0.333333f, -0.5f, 0.166667f, 0.166667f, -0.5f, 0.166667f, 5.55112e-17f, -0.5f, 0.166667f, -0.166667f, -0.5f, 0.166667f, -0.333333f, -0.5f, 0.166667f, 
-0.5f, -0.5f, 0.166667f, -0.5f, -0.333333f, 0.166667f, -0.5f, -0.166667f, 0.166667f, -0.5f, -5.55112e-17f, 0.166667f, -0.5f, 0.166667f, 0.166667f, -0.5f, 0.333333f, 0.166667f, -0.5f, 0.5f, 5.55112e-17f, 
-0.333333f, 0.5f, 5.55112e-17f, -0.166667f, 0.5f, 5.55112e-17f, -5.55112e-17f, 0.5f, 5.55112e-17f, 0.166667f, 0.5f, 5.55112e-17f, 0.333333f, 0.5f, 5.55112e-17f, 0.5f, 0.5f, 5.55112e-17f, 0.5f, 0.333333f, 5.55112e-17f, 
0.5f, 0.166667f, 5.55112e-17f, 0.5f, 5.55112e-17f, 5.55112e-17f, 0.5f, -0.166667f, 5.55112e-17f, 0.5f, -0.333333f, 5.55112e-17f, 0.5f, -0.5f, 5.55112e-17f, 0.333333f, -0.5f, 5.55112e-17f, 0.166667f, -0.5f, 5.55112e-17f, 
5.55112e-17f, -0.5f, 5.55112e-17f, -0.166667f, -0.5f, 5.55112e-17f, -0.333333f, -0.5f, 5.55112e-17f, -0.5f, -0.5f, 5.55112e-17f, -0.5f, -0.333333f, 5.55112e-17f, -0.5f, -0.166667f, 5.55112e-17f, -0.5f, -5.55112e-17f, 5.55112e-17f, 
-0.5f, 0.166667f, 5.55112e-17f, -0.5f, 0.333333f, 5.55112e-17f, -0.5f, 0.5f, -0.166667f, -0.333333f, 0.5f, -0.166667f, -0.166667f, 0.5f, -0.166667f, -5.55112e-17f, 0.5f, -0.166667f, 0.166667f, 0.5f, -0.166667f, 
0.333333f, 0.5f, -0.166667f, 0.5f, 0.5f, -0.166667f, 0.5f, 0.333333f, -0.166667f, 0.5f, 0.166667f, -0.166667f, 0.5f, 5.55112e-17f, -0.166667f, 0.5f, -0.166667f, -0.166667f, 0.5f, -0.333333f, -0.166667f, 
0.5f, -0.5f, -0.166667f, 0.333333f, -0.5f, -0.166667f, 0.166667f, -0.5f, -0.166667f, 5.55112e-17f, -0.5f, -0.166667f, -0.166667f, -0.5f, -0.166667f, -0.333333f, -0.5f, -0.166667f, -0.5f, -0.5f, -0.166667f, 
-0.5f, -0.333333f, -0.166667f, -0.5f, -0.166667f, -0.166667f, -0.5f, -5.55112e-17f, -0.166667f, -0.5f, 0.166667f, -0.166667f, -0.5f, 0.333333f, -0.166667f, -0.5f, 0.5f, -0.333333f, -0.333333f, 0.5f, -0.333333f, 
-0.166667f, 0.5f, -0.333333f, -5.55112e-17f, 0.5f, -0.333333f, 0.166667f, 0.5f, -0.333333f, 0.333333f, 0.5f, -0.333333f, 0.5f, 0.5f, -0.333333f, 0.5f, 0.333333f, -0.333333f, 0.5f, 0.166667f, -0.333333f, 
0.5f, 5.55112e-17f, -0.333333f, 0.5f, -0.166667f, -0.333333f, 0.5f, -0.333333f, -0.333333f, 0.5f, -0.5f, -0.333333f, 0.333333f, -0.5f, -0.333333f, 0.166667f, -0.5f, -0.333333f, 5.55112e-17f, -0.5f, -0.333333f, 
-0.166667f, -0.5f, -0.333333f, -0.333333f, -0.5f, -0.333333f, -0.5f, -0.5f, -0.333333f, -0.5f, -0.333333f, -0.333333f, -0.5f, -0.166667f, -0.333333f, -0.5f, -5.55112e-17f, -0.333333f, -0.5f, 0.166667f, -0.333333f, 
-0.5f, 0.333333f, -0.333333f, -0.5f, 0.5f, -0.5f, -0.333333f, 0.5f, -0.5f, -0.166667f, 0.5f, -0.5f, -5.55112e-17f, 0.5f, -0.5f, 0.166667f, 0.5f, -0.5f, 0.333333f, 0.5f, -0.5f, 
0.5f, 0.5f, -0.5f, -0.5f, 0.333333f, -0.5f, -0.333333f, 0.333333f, -0.5f, -0.166667f, 0.333333f, -0.5f, -5.55112e-17f, 0.333333f, -0.5f, 0.166667f, 0.333333f, -0.5f, 0.333333f, 0.333333f, -0.5f, 
0.5f, 0.333333f, -0.5f, -0.5f, 0.166667f, -0.5f, -0.333333f, 0.166667f, -0.5f, -0.166667f, 0.166667f, -0.5f, -5.55112e-17f, 0.166667f, -0.5f, 0.166667f, 0.166667f, -0.5f, 0.333333f, 0.166667f, -0.5f, 
0.5f, 0.166667f, -0.5f, -0.5f, 5.55112e-17f, -0.5f, -0.333333f, 5.55112e-17f, -0.5f, -0.166667f, 5.55112e-17f, -0.5f, -5.55112e-17f, 5.55112e-17f, -0.5f, 0.166667f, 5.55112e-17f, -0.5f, 0.333333f, 5.55112e-17f, -0.5f, 
0.5f, 5.55112e-17f, -0.5f, -0.5f, -0.166667f, -0.5f, -0.333333f, -0.166667f, -0.5f, -0.166667f, -0.166667f, -0.5f, -5.55112e-17f, -0.166667f, -0.5f, 0.166667f, -0.166667f, -0.5f, 0.333333f, -0.166667f, -0.5f, 
0.5f, -0.166667f, -0.5f, -0.5f, -0.333333f, -0.5f, -0.333333f, -0.333333f, -0.5f, -0.166667f, -0.333333f, -0.5f, -5.55112e-17f, -0.333333f, -0.5f, 0.166667f, -0.333333f, -0.5f, 0.333333f, -0.333333f, -0.5f, 
0.5f, -0.333333f, -0.5f, -0.5f, -0.5f, -0.5f, -0.333333f, -0.5f, -0.5f, -0.166667f, -0.5f, -0.5f, -5.55112e-17f, -0.5f, -0.5f, 0.166667f, -0.5f, -0.5f, 0.333333f, -0.5f, -0.5f, 
0.5f, -0.5f, -0.5f  };
    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}

void init (GLFWwindow* window){
    renderingProgram = createShaderProgram((char *)"vertShader.glsl",(char *) "fragShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 8.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
    setupVertices();
    glPointSize(3.0f);
}

void display (GLFWwindow* window, double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); //Clear the background to black
    glUseProgram(renderingProgram);
    
    //Getto le uniform
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    timeLoc = glGetUniformLocation(renderingProgram, "time");
    
    //Costruisco la pMat
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees
    
    //Faccio Varie Traslazioni in cui uso il tempo
    tMat = glm::translate(glm::mat4(1.0f), glm::vec3(   sin(0.35f*currentTime)*2.0f,
                                                        cos(0.52f*currentTime)*2.0f,
                                                        sin(0.70f*currentTime)*2.0f  ));
    rMat = glm::rotate(glm::mat4(1.0f), 1.75f*(float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
    rMat = glm::rotate(rMat, 1.75f*(float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
    rMat = glm::rotate(rMat, 1.75f*(float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
    
    //Costruisco la mvMat
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mMat = tMat*rMat;//mMat = glm::translate(glm::mat4(1.0f), glm::vec3(0,0,1.0f));
    mvMat = vMat * mMat;
    
    //Spedisco matrici allo shader
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    
    //Mando il tempo per fare l'animazione
    glUniform1f(timeLoc, currentTime);
    
    //Associazione VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_POINTS, 0, 218);
}

int main(void){
    if (!glfwInit()) {exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "09_TriangoloRotante", NULL, NULL);
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
