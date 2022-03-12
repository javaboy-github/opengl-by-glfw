#pragma once
#include "program.hpp"
#include <glm/detail/qualifier.hpp>
#include <glm/vec3.hpp>

namespace box {
	GLuint index[]{
    0, 1, 2, 0, 2, 3, // 左
    0, 3, 4, 0, 4, 5, // 裏
    0, 5, 6, 0, 6, 1, // 下
    7, 6, 5, 7, 5, 4, // 右
    7, 4, 3, 7, 3, 2, // 上
    7, 2, 1, 7, 1, 6  // 前
  };

	struct Vertex {
		GLfloat position[3];
		GLfloat normal[3];
	};

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
			const Vertex vertex[8];


		public:
			NormalBox(glm::vec3 pos, glm::vec3 boxSize, program::Program& program);
			~NormalBox();
			void draw() const override;
	};
}
