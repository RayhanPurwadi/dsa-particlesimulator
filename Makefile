build:
	g++ -std=c++17 -DSFML_STATIC \
	main.cpp \
	src/body2d.cpp src/circle.cpp src/collisionbody2d.cpp src/environment.cpp src/kineticbody2d.cpp src/particle.cpp \
	ext/imgui-sfml/imgui-SFML.cpp \
	ext/imgui/imgui.cpp ext/imgui/imgui_widgets.cpp ext/imgui/imgui_draw.cpp ext/imgui/imgui_tables.cpp \
	-o ./particlesimulator \
	-Iext/imgui -Iext/imgui-sfml \
	-Iext/SFML-3.0.0/include -Lext/SFML-3.0.0/lib \
	-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lGL \
	-lX11 -lXrandr -ludev -lfreetype -lXi -lXcursor

deps:
	sudo apt install build-essential cmake ninja-build libx11-dev libxrandr-dev libgl1-mesa-dev libxi-dev libxcursor-dev

download:
	wget https://www.sfml-dev.org/files/SFML-3.0.0-linux-gcc-64-bit.tar.gz
	mv SFML-3.0.0-linux-gcc-64-bit.tar.gz ext/
	cd ext && tar xzf SFML-3.0.0-linux-gcc-64-bit.tar.gz
	rm SFML-3.0.0-linux-gcc-64-bit.tar.gz