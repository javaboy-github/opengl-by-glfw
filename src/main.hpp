#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

GLuint createProgram(const char *vs);
GLboolean printShaderInfoLog(GLuint shader, const char *str);
int main();
GLboolean printProgramInfoLog(GLuint program);
