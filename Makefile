build:
	g++ -std=c++17 -DSFML_STATIC \
	main.cpp \
	src/environment.cpp src/body2d.cpp src/collisionbody2d.cpp src/kineticbody2d.cpp src/circle.cpp src/particle.cpp \
	ext/imgui-sfml/imgui-SFML.cpp \
	ext/imgui/imgui.cpp ext/imgui/imgui_widgets.cpp ext/imgui/imgui_draw.cpp ext/imgui/imgui_tables.cpp \
	-o ./particlesimulator \
	-Iext/imgui -Iext/imgui-sfml -Isrc \
	-Iext/SFML/include -Lext/SFML/build/lib \
	-lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lGL \
	-lX11 -lXrandr -ludev -lfreetype -lXi -lXcursor

deps:
	sudo apt install build-essential cmake ninja-build libx11-dev libxrandr-dev libgl1-mesa-dev libxi-dev libxcursor-dev

sfml:
	cd ext/SFML && mkdir -p build && cd build && cmake -G Ninja -DSFML_BUILD_EXAMPLES=OFF -DSFML_BUILD_TEST_SUITE=OFF -DSFML_USE_STATIC_STD_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release -DSFML_BUILD_AUDIO=OFF .. && ninja