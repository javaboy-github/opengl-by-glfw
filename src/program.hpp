#pragma once
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <string>

namespace program {
	class Program {
		public:
			const GLuint program;

			Program(std::string vertex, std::string fragment);

		private:
			bool isLinked;
		public:
			void link();
			void use() const;
		private:
			GLint getLoc(std::string name);
		public:
		void set(std::string name, bool value);
		void set(std::string name, int value);
		void set(std::string name, float value);
		void set(std::string name, glm::mat4 value);

		Program createFromSourcefile(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename);
	};
}
