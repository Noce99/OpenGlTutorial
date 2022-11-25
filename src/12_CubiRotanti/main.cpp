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
GLuint mvLoc, projLoc;
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
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    
    //Costruisco la pMat
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees
    
    for (int i=0; i<24; i++){
        //Fattore che distingue un cubo dall'altro!
        double tf = currentTime + i*10;
        //Faccio Varie Traslazioni in cui uso il tempo
        tMat = glm::translate(glm::mat4(1.0f), glm::vec3(   sin(0.35f*tf)*6.0f,
                                                            cos(0.52f*tf)*6.0f,
                                                            sin(0.70f*tf)*6.0f  ));
        rMat = glm::rotate(glm::mat4(1.0f), 1.75f*(float)tf, glm::vec3(0.0f, 1.0f, 0.0f));
        rMat = glm::rotate(rMat, 1.75f*(float)tf, glm::vec3(1.0f, 0.0f, 0.0f));
        rMat = glm::rotate(rMat, 1.75f*(float)tf, glm::vec3(0.0f, 0.0f, 1.0f));
        
        //Costruisco la mvMat
        vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
        mMat = tMat*rMat;
        mvMat = vMat * mMat;
        
        //Spedisco matrici allo shader
        glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
        
        //Associazione VBO
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
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
