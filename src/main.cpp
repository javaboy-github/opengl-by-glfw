// 必要なものをインクルード
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include "Shape.h"

#include "main.hpp"

constexpr Object::Vertex rectangleVertex[] = {
	{-0.5f, -0.5f},
	{ 0.5f, -0.5f},
	{-0.5f,  0.5f},
	{ 0.5f,  0.5f},
};

// プログラムオブジェクトを作成します
// @param vsrc バーテックスシェーダのソースプログラムの文字列
// @param fsrc フラグメントシェーダのソースプログラムの文字列
// @return 作成されたプログラム
GLuint createProgram(const char *vsrc, const char *fsrc) {
	// プログラムを作成する
	const GLuint program(glCreateProgram());

	if (vsrc != NULL ){
		// バーテックスシェーダのシェーダオブジェクトを作成する
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);

		// バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		if (printShaderInfoLog(vobj, "vertex shader"))
			glAttachShader(program, vobj);
		glDeleteShader(vobj);
	} 
	if (fsrc != NULL) {
		// フラグメントシェーダのシェーダオブジェクトを作成する
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		// フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		if (printShaderInfoLog(fobj, "fragment shader"))
			glAttachShader(program, fobj);
		glDeleteShader(fobj);
	}

	// プログラムオブジェクトをリンクする
	glBindAttribLocation(program, 0, "position");
	glBindFragDataLocation(program, 0, "fragment");
	glLinkProgram(program);

	// 作成したプログラムオブジェクトを返す
	if (printProgramInfoLog(program))
		return program;

	// プログラムオブジェクトが作成できなければ 0 を返す
	glDeleteShader(program);
	return 0;
}

// シェーダのソースファイルを読み込んでプログラムオブジェクトを作成する
// @param vert バーティクスシェーダのソースファイル名
// @param frag フラグメントシェーダのソースファイル名
// @return プログラムオブジェクト
GLuint loadProgram(const char *vert, const char *frag) {
	// シェーダのソースファイルを読み込む
	std::vector<GLchar> vsrc;
	const bool vstat(readShaderSource(vert, vsrc));
	std::vector<GLchar> fsrc;
	const bool fstat(readShaderSource(frag, fsrc));

	// プログラムオブジェクトを作成する
	return vstat && fstat ? createProgram(vsrc.data(), fsrc.data()) : 0;
}

// シェーダオブジェクトのコンパイル結果を表示する
// @param shader シェーダオブジェクト名
// @param str コンパイルエラーが発生した場所を示す文字列
GLboolean printShaderInfoLog(GLuint shader, const char *str) {
	// コンパイル結果を表示する
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status ==  GL_FALSE) std::cerr << "Compile Error in " << str <<   std::endl;
	// シェーダのコンパイル時のログの長さを取得する
	GLsizei bufSize;	
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &bufSize);
	if (bufSize > 1) {
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);
		std::cerr <<   &infoLog[0] <<   std::endl;
	}
	return static_cast<GLboolean>(status);
}

// プログラムオブジェクトのリンク結果を表示する
// @param program プログラムオブジェクトの名前
GLboolean printProgramInfoLog(GLuint program) {
	// リンク結果を取得する
	GLint status;
	glGetShaderiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
		std::cerr << "Link error." << std::endl;

	// シェーダのリンク時のログの長さを取得する
	GLsizei bufSize;
	glGetShaderiv(program, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1) {
		// シェーダのリンク時のログの内容を取得する
		std::vector<GLchar> infoLog(bufSize);
		GLsizei length;
		glGetProgramInfoLog(program, bufSize, &length, &infoLog[0]);
		std::cerr << &infoLog[0] << std::endl;
	}

	return static_cast<GLboolean>(status);
}

// シェーダのソースファイルを読み込んだメモリを返す
// @param name シェーダのソースファイル名
// @param buffer 読み込んだソースファイルのテキスト
// @return 読み込めたらtrue
bool readShaderSource(const char *name, std::vector<GLchar> &buffer) {
	// ファイル名がnullの場合
	if (name == NULL)
		return false;

	// ソースファイルを開く
	std::ifstream file(name, std::ios::binary);
	if (file.fail()) {
		// 開けなかった場合
		std::cerr << "Error: Can't open source file: " << name << std::endl;
		return false;
	}

}

int main( void ) {
	// GLFWを初期化
	if( !glfwInit() ) {
		fprintf( stderr, "GLFWの初期化に失敗しました\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);


	// ウィンドウを開いて、OpenGLコンテキストを作成
	GLFWwindow* window;
	window = glfwCreateWindow( 1024, 768, "opengl-example", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "GLFWウィンドウを開くことに失敗しました。 もし、あなたがIntelGPUを使っているなら、それらはOpenGL 3.3と互換性がありません。バージョン2.1を試して下さい。\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// GLEWを初期化
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "GLEWの初期化に失敗しました\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// 押されているEscキーをキャプチャできることを確認
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// 青黒い背景を設定
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	const GLuint program(loadProgram("point.vert", "point.frag"));



	// 図形データの作成
	std::unique_ptr<const Shape> shape(new Shape(2, 4, rectangleVertex));
	do{
		// スクリーンをクリア。
		glClear( GL_COLOR_BUFFER_BIT );

		// シェーダプログラムの使用開始
		glUseProgram(program);

		// 図形の描画
		shape->draw();

		// バッファーをスワップ
		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	// ESCキーが押されたか、ウィンドウが閉じたかを確認
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0 );

	// OpenGLウィンドウを閉じ、GLFWを終了
	glfwTerminate();

	return 0;
}

