# このリポジトリについて
このリポジトリはJavaばっかりしてる作者が、C++の勉強かつ、OpenGLの勉強用のレポジトリです。

# 使用しているもの
- OpenGL
- cmake(ビルドツールとして)
- glm
- glfw
- conan

# 実行方法
1. このプロジェクトをclone。
2. パソコンにg++とcmake、conanをインストール。aptを使用している場合は`sudo apt install cmake g++ conan`
3. cloneしたレポジトリまでcd。
4. `mkdir build && cd build && conan install .. && cmake .. && make`を実行
