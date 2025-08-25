build:
	g++ -std=c++17 -DSFML_STATIC \
	main.cpp \
	-o ./particlesimulator \
	-ISFML-3.0.0/include -LSFML-3.0.0/lib \
	-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lGL \
	-lX11 -lXrandr -ludev -lfreetype -lXi -lXcursor

deps:
	sudo apt install build-essential libx11-dev libxrandr-dev libgl1-mesa-dev libxi-dev libxcursor-dev

download:
	wget https://www.sfml-dev.org/files/SFML-3.0.0-linux-gcc-64-bit.tar.gz
	tar xzf SFML-3.0.0-linux-gcc-64-bit.tar.gz