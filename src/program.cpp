#include <fstream>
#include <ios>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>

namespace program {
	class Program {
		public:
		const GLuint program;

		Program(std::string vertex, std::string fragment): program(glCreateProgram()) {
			const char *vertexCChar = vertex.c_str();
			GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vobj, 1, &vertexCChar, NULL);
			glCompileShader(vobj);
			GLint vobjCompileStatus;
			glGetShaderiv(vobj, GL_COMPILE_STATUS, &vobjCompileStatus);
			if (vobjCompileStatus == GL_FALSE) {
				GLint bufsize;
				glGetShaderiv(vobj, GL_INFO_LOG_LENGTH, &bufsize);
				if (bufsize > 1) {
					std::vector<GLchar> infoLog = std::vector<GLchar>(bufsize);
					GLsizei length;
					glGetShaderInfoLog(vobj, bufsize, &length, &infoLog[0]);
					throw std::string("Failed to compile vertex shader. Error Message: ") + &infoLog[0];
				}else throw "Failed to compile vertex shader and could not get error message"; 
			}
			glAttachShader(program, vobj);
			glDeleteShader(vobj);

			const char *fragmentChar = fragment.c_str();
			GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fobj, 1, &vertexCChar, NULL);
			glCompileShader(fobj);
			GLint fobjCompileStatus;
			glGetShaderiv(fobj, GL_COMPILE_STATUS, &fobjCompileStatus);
			if (fobjCompileStatus == GL_FALSE) {
				GLint bufsize;
				glGetShaderiv(fobj, GL_INFO_LOG_LENGTH, &bufsize);
				if (bufsize > 1) {
					std::vector<GLchar> infoLog = std::vector<GLchar>(bufsize);
					GLsizei length;
					glGetShaderInfoLog(vobj, bufsize, &length, &infoLog[0]);
					throw std::string("Failed to compile fragment shader. Error Message: ") + &infoLog[0];
				}else throw "Failed to compile fragment shader and could not get error message"; 
			}
			glAttachShader(program, fobj);
			glDeleteShader(fobj);

			glLinkProgram(program);
		};

		void use() {
			glUseProgram(this->program);
		}

		private:
		GLint getLoc(std::string name) {
			GLint location = glGetUniformLocation(program, name.c_str());
			if (location == -1) throw "This uniform not found" + name;
			return location;
		}

		public:
		void set(std::string name, bool value) {glUniform1i(getLoc(name), value);}
		void set(std::string name, int value) {glUniform1i(getLoc(name), value);}
		void set(std::string name, float value) {glUniform1f(getLoc(name), value);}
	};
	
	Program createFromSourcefile(std::string vertexShaderSourceFilename, std::string fragmentShaderSourceFilename) {
		std::ifstream vifs(vertexShaderSourceFilename, std::ios::in);
		std::string lineBuffer;
		std::string vertexShaderSource;
		while(std::getline(vifs, lineBuffer)) {
			vertexShaderSource.append(lineBuffer);
		}
		vifs.close();

		std::ifstream fifs(fragmentShaderSourceFilename, std::ios::in);
		std::string fragmentShaderSource;
		while(std::getline(fifs, lineBuffer)) {
			fragmentShaderSource.append(lineBuffer);
		}
		fifs.close();

		return Program(vertexShaderSource, fragmentShaderSource);
	}
}
