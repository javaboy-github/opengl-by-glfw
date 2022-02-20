#include <GLFW/glfw3.h>
#include <cstdlib>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>

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

	for (long i=0L;i<10000000000L;i++){}

	glfwTerminate();
	glfwSetErrorCallback(NULL);
}
