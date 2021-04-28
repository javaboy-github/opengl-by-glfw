#pragma once
#include <memory>
#include "Object.h"

// 図形を表すクラス
class Shape {
private:
	// 図形データ
	std::shared_ptr<const Object> object;
protected:
	// 描画に使う頂点の数　
	const GLsizei vertexcount;
public:
	// Shapeオブジェクトを作成する
	// @param vertexcount 頂点の数
	// @param vertex 頂点属性を格納した配列
	Shape(GLint size, GLsizei vertexcount, const Object::Vertex *vertex) : object(new Object(size, vertexcount, vertex)), vertexcount(vertexcount){}

	// 描画
	void draw() const {
		// 頂点配列オブジェクトを結合する
		object->bind();
		// 描画を実行
		execute();
	}	

	// 描画の実行
	virtual void execute() const {
		// 折れ線で描画する
		glDrawArrays(GL_LINE_LOOP, -0, vertexcount);
	}
};
