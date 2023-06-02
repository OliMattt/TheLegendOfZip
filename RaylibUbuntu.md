# Instalação da Raylib no linux ubuntu e derivados: 

sudo apt update
sudo apt upgrade


sudo apt install build-essential git cmake libasound2-dev libpulse-dev libfreetype6-dev libglfw3-dev libglew-dev


git clone https://github.com/raysan5/raylib.git

cd raylib

mkdir build

cd build

cmake ..

make

sudo make install

## Compilar o código:

gcc -o main main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

## Executar:

./main
