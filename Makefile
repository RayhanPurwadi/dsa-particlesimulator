build:
	g++ -std=c++17 -DSFML_STATIC -ISFML-3.0.0/include main.cpp -LSFML-3.0.0/lib -lX11 -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -o ./particlesimulator

deps:
	sudo apt install build-essential

download:
	wget https://www.sfml-dev.org/files/SFML-3.0.0-linux-gcc-64-bit.tar.gz
	tar xzf SFML-3.0.0-linux-gcc-64-bit.tar.gz