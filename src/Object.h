#pragma once
#include <GL/glew.h>

// 図形データ
class Object {
private:
	// 頂点配列オブジェクト名
	GLuint vao;
	// 頂点バッファオブジェクト名
	GLuint vbo;

	// 複製禁止
	Object(const Object &o);
	Object &operator=(const Object &o);

public:
	// 頂点属性
	struct Vertex {
		GLfloat position[2];
	};

	// コンストラクタ
	// @param size 現在の位置の次元
	// @param vertexcount 頂点の数
	Object(GLint size, GLsizei vertexcount, const Vertex *vertex) {
		// 頂点配列オブジェクト
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// 頂点バッファオブジェクト
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexcount * sizeof (Vertex), vertex, GL_STATIC_DRAW);

		// 融合されている頂点バッファオブジェクトを in 変数から参照できるようにする
		glVertexAttribPointer(0, size,GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}

	virtual ~Object() {
		// 頂点配列オブジェクトを削除
		glDeleteVertexArrays(1, &vao);

		// 頂点バッファオブジェクトを削除する
		glDeleteBuffers(1, &vao);
	}
	// 頂点配列オブジェクトのバインド
	void bind() const {
		glBindVertexArray(vao);
	}
};
