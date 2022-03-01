#pragma once
#include <GLFW/glfw3.h>
#include <string>

namespace program {
	class Program {
		public:
			const GLuint program;

			Program(std::string vertex, std::string fragment);

			void use();
		private:
			GLint getLoc(std::string name);
		public:
		void set(std::string name, bool value);
		void set(std::string name, int value);
		void set(std::string name, float value);

		Program createFromSourcefile(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename);
	};
}
