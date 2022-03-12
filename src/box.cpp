#include "box.hpp"
#include "program.hpp"
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>


namespace box {
	Box::Box(glm::vec3 pos, program::Program& program): pos(pos), program(program) {}

	NormalBox::NormalBox(glm::vec3 pos, glm::vec3 boxsize, program::Program& program): Box(pos, program), 
	vertex{
    Vertex{-boxsize.x/2 + pos.x, -boxsize.y/2 + pos.y, -boxsize.z/2 + pos.z, 0,    0,    0,  }, // 0
    Vertex{-boxsize.x/2 + pos.x, -boxsize.y/2 + pos.y,  boxsize.z/2 + pos.z, 0,    0,    0.8f}, // 1
    Vertex{-boxsize.x/2 + pos.x,  boxsize.y/2 + pos.y,  boxsize.z/2 + pos.z, 0,    0.8f, 0,  }, // 2
    Vertex{-boxsize.x/2 + pos.x,  boxsize.y/2 + pos.y, -boxsize.z/2 + pos.z, 0,    0.8f, 0.8f}, // 3
    Vertex{ boxsize.x/2 + pos.x,  boxsize.y/2 + pos.y, -boxsize.z/2 + pos.z, 0.8f, 0,    0,  }, // 4
    Vertex{ boxsize.x/2 + pos.x, -boxsize.y/2 + pos.y, -boxsize.z/2 + pos.z, 0.8f, 0,   0.8f,}, // 5
    Vertex{ boxsize.x/2 + pos.x, -boxsize.y/2 + pos.y,  boxsize.z/2 + pos.z, 0.8f, 0.8f, 0,  }, // 6
    Vertex{ boxsize.x/2 + pos.x,  boxsize.y/2 + pos.y,  boxsize.z/2 + pos.z, 0.8f, 0.8f, 0.8f}, // 7
	}{
		glGenBuffers(1, &(this->vbo));
		glBindVertexArray(this->vbo);

		glGenBuffers(1, &(this->vbo));
		glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertex), vertex, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<char *>(0) + sizeof this->vertex->position);
		glEnableVertexAttribArray(0);

		glGenBuffers(1, &(this->ibo));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	}

	void NormalBox::draw() const {
		this->program.use();
		glBindVertexArray(this->vao);
		glDrawElements(GL_TRIANGLES, sizeof(index), GL_UNSIGNED_INT, 0);
	}

	NormalBox::~NormalBox() {
		glDeleteVertexArrays(this->vao);
		glDeleteBuffers(1, this->vao);
		glDeleteBuffers(1, this->ibo);
	}
}