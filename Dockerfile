FROM ubuntu:latest
LABEL version="1.0"
LABEL description="openglの勉強用のこのリポジトリのビルド用Docker"
RUN apt-get update 
RUN apt-get install -y cmake g++ gcc make  libx11-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxrandr-dev libxext-dev libxcursor-dev libxinerama-dev libxi-dev
RUN mkdir ~/opengl-example/build -p
WORKDIR ~/opengl-example
COPY ./* ~/opengl-exampel
CMD ["cmake", ".."]
CMD ["cmake", "--build", "."]
