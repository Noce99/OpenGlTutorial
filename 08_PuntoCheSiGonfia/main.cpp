#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

#define numVAOs 1
//VAO = Vertex Array Objects

GLuint renderingProgram; //GLuint è una shortcat per unsigned int
GLuint vao[numVAOs];

float size = 1.0f;
float inc = -0.4f;

GLuint createShaderProgram() {
  const char *vshaderSource =
    "#version 430 \n"
    "void main(void) \n"
    "{gl_Position = vec4(0.0, 0.0, 0.0, 1.0);}";
  const char *fshaderSource =
    "#version 430 \n"
    "out vec4 color; \n"
    "void main(void) \n"
    "{color = vec4(0.0, 0.0, 1.0, 1.0);}";
  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vShader, 1, &vshaderSource, NULL);
  glShaderSource(fShader, 1, &fshaderSource, NULL);

  glCompileShader(vShader);
  glCompileShader(fShader);

  GLuint vfProgram = glCreateProgram();
  glAttachShader(vfProgram, vShader);
  glAttachShader(vfProgram, fShader);
  glLinkProgram(vfProgram);

  return vfProgram;
}

void init (GLFWwindow* window){
  renderingProgram = createShaderProgram();
  glGenVertexArrays(numVAOs, vao);
  glBindVertexArray(vao[0]);
}

void display (GLFWwindow* window, double currentTime){
  glClear(GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT); //Clear the background to black
  glUseProgram(renderingProgram);
  if (size >= 200.0f || size <= 1.0f){
    inc = -inc;
  }
  size += inc;
  glPointSize(size); //Setta la grandezza di un Punto!
  glDrawArrays(GL_POINTS, 0, 1);
}

int main(void){
  if (!glfwInit()) {exit(EXIT_FAILURE);}
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  GLFWwindow* window = glfwCreateWindow(600, 600, "02_DisegnoUnPunto", NULL, NULL);
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
