#include "box.hpp"
#include "program.hpp"
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>

namespace box {
	Box::Box(glm::vec3 pos, program::Program& program): pos(pos), program(program) {}

	NormalBox::NormalBox(glm::vec3 pos, glm::vec3 boxsize, program::Program& program): Box(pos, program){
		const auto s = glm::vec3(boxsize.x/2, boxsize.y/2, boxsize.z/2);
		GLfloat[] vertex = {
    -s.x + pos.x, -s.y + pos.y, -s.z + pos.z, 0,    0,    0,    // 0
    -s.x + pos.x, -s.y + pos.y,  s.z + pos.z, 0,    0,    0.8f, // 1
    -s.x + pos.x,  s.y + pos.y,  s.z + pos.z, 0,    0.8f, 0,    // 2
    -s.x + pos.x,  s.y + pos.y, -s.z + pos.z, 0,    0.8f, 0.8f, // 3
     s.x + pos.x,  s.y + pos.y, -s.z + pos.z, 0.8f, 0,    0,    // 4
     s.x + pos.x, -s.y + pos.y, -s.z + pos.z, 0.8f, 0,   0.8f,  // 5
     s.x + pos.x, -s.y + pos.y,  s.z + pos.z, 0.8f, 0.8f, 0,    // 6
     s.x + pos.x,  s.y + pos.y,  s.z + pos.z, 0.8f, 0.8f, 0.8f  // 7
		};
		glGenBuffers(1, &(this->vbo));
		glBindVertexArray(vbo);

		glGenBuffers(1, &(this->vbo));
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, false, 6*sizeof(float), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, false, 6*sizeof(float), 3*sizeof(float));
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &(this->ibo));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex)/sizeof(GLfloat), vertex, GL_STATIC_DRAW);
	}

	void NormalBox::draw() const {
		this->program.use();
		glBindVertexArray(this->vao);
		glDrawElements(GL_TRIANGLES, sizeof(vertex)/sizeof(GLfloat), GL_UNSIGNED_INT, 0);
	}

	NormalBox::~NormalBox() {
		glDeleteVertexArrays(this->vao);
		glDeleteBuffers(1, this->vao);
		glDeleteBuffers(1, ibo);
	}
}
