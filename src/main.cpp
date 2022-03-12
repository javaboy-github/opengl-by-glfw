#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "box.hpp"
#include "program.hpp"

class Window {
	private:
	GLFWwindow *const window;

	public:
	Window(int width, int height, std::string title)
		: window(glfwCreateWindow(width, height, title.c_str(), NULL, NULL)) {
			if (window == NULL) {
				std::cout << "Cannot create GLFW Window!";
				std::exit(1);
			}
			glfwMakeContextCurrent(window);
			glfwSwapInterval(1);
	}

	GLFWwindow* getWindow() const {return window;}
	void show() {glfwShowWindow(window);}
	void hide() {glfwHideWindow(window);}

	operator GLFWwindow*() const {return window;}
	
	~Window() {
		glfwDestroyWindow(window);
	}
};

int main() {
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
	program::Program program(R"(
#version 150 core

uniform mat4 modelview;
uniform mat4 projection;
uniform float t;
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
uniform float t;

void main() {
fragment = vertex_color;
}
)");
	box::NormalBox box(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), program);

	while (glfwWindowShouldClose(window) == GL_FALSE) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		box.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	glfwSetErrorCallback(NULL);
}
