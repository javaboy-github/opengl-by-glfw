#pragma once
#include "program.hpp"
#include <glm/detail/qualifier.hpp>
#include <glm/vec3.hpp>

namespace box {
	class Box {
		public:
			const program::Program& program;
			glm::vec3 pos;
			virtual void draw() const;

			Box(glm::vec3 pos, program::Program& program);
	};
	
	class NormalBox: Box {
		private:
			GLuint vao;
			GLuint vbo;
			GLuint ibo;
			const GLfloat vertex[48];


		public:
			NormalBox(glm::vec3 pos, glm::vec3 boxSize, program::Program& program);
			~NormalBox();
			void draw() const override;
	};
}
