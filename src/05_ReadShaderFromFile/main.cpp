#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define numVAOs 1
//VAO = Vertex Array Objects

GLuint renderingProgram; //GLuint è una shortcat per unsigned int
GLuint vao[numVAOs];

void printShaderLog(GLuint);
void printProgramLog(int);
bool checkOpenGLError();
string readShaderSource(const char *);

GLuint createShaderProgram() {
  GLint vertCompiled;
  GLint fragCompiled;
  GLint linked;

  string vertShaderStr = readShaderSource("vertShader.glsl");
  string fragShaderStr = readShaderSource("fragShader.glsl");

  const char *vertShaderScr = vertShaderStr.c_str();
  const char *fragShaderScr = fragShaderStr.c_str();

  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vShader, 1, &vertShaderScr, NULL);
  glShaderSource(fShader, 1, &fragShaderScr, NULL);

  glCompileShader(vShader);
  checkOpenGLError();
  glGetShaderiv(vShader, GL_COMPILE_STATUS, &vertCompiled);
  if (vertCompiled != true){
    cout << "Vertex compilation FAILED!" << endl;
    printShaderLog(vShader);
  }

  glCompileShader(fShader);
  checkOpenGLError();
  glGetShaderiv(fShader, GL_COMPILE_STATUS, &fragCompiled);
  if (fragCompiled != true){
    cout << "Fragment compilation FAILED!" << endl;
    printShaderLog(fShader);
  }

  GLuint vfProgram = glCreateProgram();

  glAttachShader(vfProgram, vShader);
  glAttachShader(vfProgram, fShader);

  glLinkProgram(vfProgram);
  checkOpenGLError();
  glGetProgramiv(vfProgram, GL_LINK_STATUS, &linked);
  if (linked != true){
    cout << "Linking FAILED!" << endl;
    printProgramLog(vfProgram);
  }

  return vfProgram;
}

void init (GLFWwindow* window){
  renderingProgram = createShaderProgram();
  glGenVertexArrays(numVAOs, vao);
  glBindVertexArray(vao[0]);
  glPointSize(30.0f); //Setta la grandezza di un Punto!
}

void display (GLFWwindow* window, double currentTime){
  glUseProgram(renderingProgram);
  glDrawArrays(GL_POINTS, 0, 1);
}

void printShaderLog(GLuint shader){
  int len = 0;
  int chWrittn = 0;
  char *log;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  if (len > 0){
    log = (char *)malloc(len);
    glGetShaderInfoLog(shader, len, &chWrittn, log);
    cout << "Shader Info Log:" << log << endl;
    free(log);
  }
}

void printProgramLog(int prog){
    int len = 0;
    int chWrittn = 0;
    char *log;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
    if (len > 0){
      log = (char *)malloc(len);
      glGetProgramInfoLog(prog, len, &chWrittn, log);
      cout << "Program Info Log:" << log << endl;
      free(log);
    }
}

bool checkOpenGLError(){
  bool foundError = false;
  int glErr = glGetError();
  while (glErr != GL_NO_ERROR){
    cout << "GL error:" << glErr << endl;
    foundError = true;
    glErr = glGetError();
  }
  return foundError;
}

string readShaderSource(const char *filePath){
    string content;
    ifstream fileStream(filePath, ios::in);
    string line = "";
    while (!fileStream.eof()){
      getline(fileStream, line);
      content.append(line + "\n");
    }
    fileStream.close();
    return content;
}

int main(void){
  if (!glfwInit()) {exit(EXIT_FAILURE);}
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  GLFWwindow* window = glfwCreateWindow(600, 600, "03_DisegnaUnPuntoColorato", NULL, NULL);
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
