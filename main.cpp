#include <optional>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include "environment.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode({1600, 800}), "Particle Simulator :: Rayhan - 5024241032");
	if (!ImGui::SFML::Init(window)) {
		exit(1);
	}

	Environment env;
	
	sf::Clock deltaClock;
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
		}

		sf::Time sfDelta = deltaClock.restart();
		std::int32_t delta = sfDelta.asMilliseconds();
		ImGui::SFML::Update(window, sfDelta);

        ImGui::Begin("Test Window");
        ImGui::Button("LOOK AT ME");
        ImGui::End();

        window.clear();
		env.render(&window, delta);

        ImGui::SFML::Render(window);
        window.display();

	}

	return 0;
}