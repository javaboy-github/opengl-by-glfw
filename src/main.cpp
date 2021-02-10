// 必要なものをインクルード
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
using namespace glm;

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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

	do{
        // スクリーンをクリア。
		glClear( GL_COLOR_BUFFER_BIT );

		// 描画処理(今は特に何も描画しない)

		
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

