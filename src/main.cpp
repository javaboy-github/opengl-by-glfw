// 必要なものをインクルード
#include <iostream>
#include <GLFW/glfw3.h>

int main( void )
{
	// GLFWを初期化
	if( !glfwInit() )
	{
		fprintf( stderr, "GLFWの初期化に失敗しました\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);


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

	// 押されているEscキーをキャプチャできることを確認
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// 青黒い背景を設定
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	while(glfwWindowShouldClose(window) == GL_FALSE) {	
        // スクリーンをクリア。
		glClear( GL_COLOR_BUFFER_BIT );

		// 描画処理(今は特に何も描画しない)

		
		// バッファーをスワップ
		glfwSwapBuffers(window);
		glfwWaitEvents();
	} 
	// OpenGLウィンドウを閉じ、GLFWを終了
	glfwTerminate();

	return 0;
}

