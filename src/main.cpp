// 必要なものをインクルード
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

// プログラムオブジェクトを作成します
// @param vsrc バーテックスシェーダのソースプログラムの文字列
// @param fsrc フラグメントシェーダのソースプログラムの文字列
// @return 作成されたプログラム
GLuint createProgram(const char *vsrc, const char *fsrc) {
	// プログラムを作成する
	const GLuint program(glCreateProgram());
	
	if (vsrc != NULL ){
		// バーテックスシェーダのシェーダオブジェクトを作成シェーダのシェーダオブジェクトを作成するシェーダオブジェクトを作成する
		const GLuint vobj(glCreateShader(GL_VERTEX_SHADER));
		glShaderSource(vobj, 1, &vsrc, NULL);
		glCompileShader(vobj);
	
		// バーテックスシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		glAttachShader(program, vobj);
		glDeleteShader(vobj);
	} 
	if (fsrc != NULL) {
		// フラグメントシェーダのシェーダオブジェクトを作成する
		const GLuint fobj(glCreateShader(GL_FRAGMENT_SHADER));
		glShaderSource(fobj, 1, &fsrc, NULL);
		glCompileShader(fobj);

		// フラグメントシェーダのシェーダオブジェクトをプログラムオブジェクトに組み込む
		glAttachShader(program, fobj);
		glDeleteShader(fobj);
	}

	// プログラムオブジェクトをリンクする
	glBindAttribLocation(program, 0, "position");
	glBindFragDataLocation(program, 0, "fragment");
	glLinkProgram(program);

	// 作成したプログラムオブジェクトを返す
	return program;
}

int main( void )
{
	// GLFWを初期化
	if( !glfwInit() )
	{
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

	static const GLchar vsrc[] =
		"#version 150 core\n"
		"in vec4 position;"
		"void main()"
		"{"
		"  gl_Position = position;"
		"}";
	static const GLchar fsrc[] =
		"#version 150 core\n"
		"out vec4 fragment;"
		"void main()"
		"{"
		"  fragment = vec4(1.0, 0.0, 0.0, 1.0);"
		"}";
	const GLuint program(createProgram(vsrc, fsrc));


	
	do{
        // スクリーンをクリア。
		glClear( GL_COLOR_BUFFER_BIT );

		// シェーダプログラムの使用開始
		glUseProgram(program);
		
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

