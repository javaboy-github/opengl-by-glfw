#include <fstream>
#include <ios>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>
#include "program.hpp"
#include <glm/mat4x4.hpp>

namespace program {
	Program::Program(std::string vertex, std::string fragment): program(glCreateProgram()), isLinked(false) {
			const char *vertexChar = vertex.c_str();
			GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vobj, 1, &vertexChar, NULL);
			glCompileShader(vobj);
			GLint vobjCompileStatus;
			glGetShaderiv(vobj, GL_COMPILE_STATUS, &vobjCompileStatus);
			if (vobjCompileStatus == GL_FALSE) {
				GLsizei bufsize;
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
			glShaderSource(fobj, 1, &fragmentChar, NULL);
			glCompileShader(fobj);
			GLint fobjCompileStatus;
			glGetShaderiv(fobj, GL_COMPILE_STATUS, &fobjCompileStatus);
			if (fobjCompileStatus == GL_FALSE) {
				GLsizei bufsize;
				glGetShaderiv(fobj, GL_INFO_LOG_LENGTH, &bufsize);
				if (bufsize > 1) {
					std::vector<GLchar> infoLog = std::vector<GLchar>(bufsize);
					GLsizei length;
					glGetShaderInfoLog(fobj, bufsize, &length, &infoLog[0]);
					throw std::string("Failed to compile fragment shader. Error Message: ") + &infoLog[0];
				}else throw "Failed to compile fragment shader and could not get error message"; 
			}
			glAttachShader(program, fobj);
			glDeleteShader(fobj);

		};

		void Program::link() {
			if (isLinked) throw "This program is alredy linked;";
			glLinkProgram(program);
			isLinked = true;
		}
		void Program::use() const {
			if (!isLinked) throw "You need to call Program::link() to call Program::use()";
			glUseProgram(this->program);
		}

		GLint Program::getLoc(std::string name) {
			GLint location = glGetUniformLocation(program, name.c_str());
			if (location == -1) throw "This uniform not found: " + name;
			return location;
		}

		void Program::set(std::string name, bool value) {glUniform1i(getLoc(name), value);}
		void Program::set(std::string name, int value) {glUniform1i(getLoc(name), value);}
		void Program::set(std::string name, float value) {glUniform1f(getLoc(name), value);}
		void Program::set(std::string name, glm::mat4 value) {glUniformMatrix4fv(getLoc(name), 1, GL_FALSE, &value[0][0]);}
	
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
