#pragma once
#include "program.hpp"
#include <glm/detail/qualifier.hpp>
#include <glm/vec3.hpp>

namespace box {
	class Box {
		public:
			const program::Program& program;
			glm::vec3 pos;
			virtual const void draw();

			Box(glm::vec3 pos, program::Program& program);
	};
	
	class NormalBox: Box {
		private:
			GLuint vao;
			GLuint vbo;

		public:
			NormalBox(glm::vec3 pos, glm::vec3 boxSize, program::Program program);
			~NormalBox();
	};
}
