#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stack>
#include "../Utils.h"

using namespace std;

#define numVAOs 1
#define numVBOs 2
//VAO = Vertex Array Objects
//VBO = Vertex Buffer Objects

float cameraX , cameraY, cameraZ;
float cubeLocX, cubeLocY, cubeLocZ;
float pyrLocX, pyrLocY, pyrLocZ;
GLuint renderingProgram; //GLuint è una shortcat per unsigned int
GLuint vao[numVAOs];
GLuint vbo[numVBOs];

//Variabili allocate in init così non devono essere allocate durante il rendering
GLuint mvLoc, projLoc;
int width, height;
float aspect;
glm::mat4 pMat, vMat, mMat, mvMat;
stack<glm::mat4> mvStack;
/*
 * pMat : Perspective matrix
 * vMat : View matrix
 * mMat : Model matrix
 * mvMat : vMat*mMat
*/

void setupVertices(){
    float cubePositions[108] = {  -1.0f, 1.0f, -1.0f,     -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f,
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
    float pyramidPositions[54] = {  -1.0f, -1.0f, 1.0f,     1.0f, -1.0f, 1.0f,      0.0f, 1.0f, 0.0f,
                                    1.0f, -1.0f, 1.0f,      1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 0.0f,
                                    1.0f, -1.0f, -1.0f,     -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f,
                                    -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
                                    -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, 1.0f,      -1.0f, -1.0f, 1.0f, 
                                    1.0f, -1.0f, 1.0f,      -1.0f, -1.0f, -1.0f,    1.0f, -1.0f, -1.0f  };
            
    glGenVertexArrays(numVAOs, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(numVBOs, vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubePositions), cubePositions, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidPositions), pyramidPositions, GL_STATIC_DRAW);
}

void init (GLFWwindow* window){
    renderingProgram = createShaderProgram((char *)"vertShader.glsl",(char *) "fragShader.glsl");
    cameraX = 0.0f; cameraY = 0.0f; cameraZ = 10.0f;
    cubeLocX = 0.0f; cubeLocY = -2.0f; cubeLocZ = 0.0f;
    pyrLocX = 3.0f; pyrLocY = 4.0f; pyrLocZ = -1.0f;
    setupVertices();
}

void display (GLFWwindow* window, double currentTime){
    glClear(GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT); //Clear the background to black
    glUseProgram(renderingProgram);
    
    //Getto le uniform
    mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
    projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
    
    //Costruisco la pMat
    glfwGetFramebufferSize(window, &width, &height);
    aspect = (float)width / (float)height;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees
    
    //Aggiungo allo stack la vMat
    vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
    mvStack.push(vMat);
    
    //SUN_PYRAMID
    //Aggiungo allo stack la posizione del Sole e la sua rotazione su se stesso
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)); //Positioning the Sun in the Origin
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
    
    //Spedisco matrici allo shader
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    
    //Associazione VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    mvStack.pop(); //Tolgo la rotazione del sole su se stesso!
    
    //PLANET_CUBE
    //Aggiungo allo stack la rotazione del pianeta attorno al sole e la sua rotazione su se stesso
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(sin((float)currentTime)*4.0f, 0.0f, cos((float)currentTime)*4.0));
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime*4.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    
    //Spedisco matrici allo shader
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    
    //Associazione VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    mvStack.pop(); //Tolgo la rotazione del pianeta su se stesso!
    
    //MOON_CUBE
    //Aggiungo allo stack la rotazione del pianeta attorno al sole e la sua rotazione su se stesso
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, sin((float)currentTime*2.0f)*2.0f, cos((float)currentTime*2.0f)*2.0));
    mvStack.top() *= glm::rotate(glm::mat4(1.0f), (float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
    mvStack.top() *= glm::scale(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.25f));
    
    //Spedisco matrici allo shader
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvStack.top()));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));
    
    //Associazione VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    mvStack.pop(); //Tolgo la rotazione della luna su se stessa, rotazione luna attorno al pianeta e scale della luna!
    mvStack.pop(); //Tolgo la rotazione del pianeta attorno al sole!
    mvStack.pop(); //Tolgo il posizionamento del sole nell'origine!
    mvStack.pop(); //Tolgo la vMat!
}

int main(void){
    if (!glfwInit()) {exit(EXIT_FAILURE);}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    GLFWwindow* window = glfwCreateWindow(600, 600, "15_Cube And Pyramid", NULL, NULL);
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
