#pragma once
#include "program.hpp"
#include <glm/detail/qualifier.hpp>
#include <glm/vec3.hpp>

namespace box {
	extern const GLuint index[36];

	struct Vertex {
		GLfloat position[3];
		GLfloat normal[3];
	};

	class Box {
		public:
			const program::Program& program;
			glm::vec3 pos;
			virtual void draw() const = 0;

			Box(glm::vec3 pos, program::Program& program);
	};
	
	class NormalBox: public Box {
		private:
			unsigned int vao;
			unsigned int vbo;
			unsigned int ibo;
			const Vertex vertex[8];


		public:
			NormalBox(glm::vec3 pos, glm::vec3 boxSize, program::Program& program);
			~NormalBox();
			void draw() const override;
	};
}
