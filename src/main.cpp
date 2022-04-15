#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstdlib>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "box.hpp"
#include "program.hpp"
using namespace glm;

class Window {
	private:
	GLFWwindow *const window;

	public:
	int width, height;

	Window(int width, int height, std::string title)
		: window(glfwCreateWindow(width, height, title.c_str(), NULL, NULL)), width(width), height(height) {
			if (window == NULL) {
				std::cout << "Cannot create GLFW Window!";
				std::exit(1);
			}
			
			glfwMakeContextCurrent(window);
			glfwSwapInterval(1);
    glfwSetWindowUserPointer(window, this);
	}

	GLFWwindow* getWindow() const {return window;}
	void show() {glfwShowWindow(window);}
	void hide() {glfwHideWindow(window);}

	operator GLFWwindow*() const {return window;}
	
	~Window() {
		glfwDestroyWindow(window);
	}

	void setViewportAutomatic() {
		int width, height;

		glfwSetWindowSizeCallback(this->window, resize);
		resize(window, 0, 0);
	}

  void static resize(GLFWwindow* arg1, int arg2, int arg3) {
		int width  = 0;
		int height = 0;
		glfwGetFramebufferSize(arg1, &width, &height);
		std::cout << width << " " << height << std::endl;
		glViewport(0, 0, width, height);

		
    Window *const
      instance(static_cast<Window *>(glfwGetWindowUserPointer(arg1)));

    if (instance != NULL) {
      // 開いたウィンドウのサイズを保存する
      instance->width  = static_cast<GLfloat>(width);
      instance->height = static_cast<GLfloat>(height);
    }
	};

};

int main() {
	try {
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Cannot initialize GLFW" << std::endl;
	}
	
	glfwDefaultWindowHints();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	Window window(1260, 960, "opengl-by-glfw");
	window.show();
	window.setViewportAutomatic();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Cannot initialize GLEW" << std::endl;
	}

	glfwSwapInterval(1);

	

	program::Program program(R"(
#version 150 core

uniform mat4 modelview;
uniform mat4 projection;
in vec4 position;
in vec4 color;
out vec4 vertex_color;
void main()
{
  vertex_color = color;
  gl_Position = projection * modelview * position;
}
				)", R"(
#version 150 core

in vec4 vertex_color;
out vec4 fragment;

void main() {
 fragment = vertex_color;
}
)");
	glBindAttribLocation(program.program, 0, "position");
	glBindAttribLocation(program.program, 1, "color");
	glBindFragDataLocation(program.program, 0, "fragment");
	program.link();
	box::NormalBox box(vec3(0, 0, 0), vec3(1, 1, 1), program);

	vec3 pos(0, 0, -3);

	glClearColor(1, 1, 1, 0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);


	while (glfwWindowShouldClose(window) == GL_FALSE) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vec3 pointOfView(0, 0, 1);
		mat4 model(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
		mat4 view = glm::lookAt(pos, pointOfView + pos, vec3(0, 1, 0));
		mat4 modelview = view * model;
		mat4 projection(glm::frustum(0.0, window.width + 0.0, window.height + 0.0, 0.0, 0.1, 1000.0));

		program.set("modelview", modelview);
		program.set("projection", projection);
		box.draw();

		if (glfwGetKey(window, GLFW_KEY_W) != GLFW_RELEASE) pos = pos + vec3(0, 0, 1);
		if (glfwGetKey(window, GLFW_KEY_S) != GLFW_RELEASE) pos = pos + vec3(0, 0, -1);
		if (glfwGetKey(window, GLFW_KEY_A) != GLFW_RELEASE) pos = pos + vec3(1, 0, 0);
		if (glfwGetKey(window, GLFW_KEY_D) != GLFW_RELEASE) pos = pos + vec3(-1, 0, 0);

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwSetErrorCallback(NULL);
	
	}catch(std::string s ) {
		std::cout << s << std::endl;
	}catch(char* s ) {
		std::cout << s << std::endl;
	}
	
}
