#include <optional>

#include <imgui.h>
#include <imgui-SFML.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({1600, 800}), "Particle Simulator :: Rayhan - 5024241032");
	if (!ImGui::SFML::Init(window)) {
		exit(1);
	}
	
	sf::Clock deltaClock;
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			ImGui::SFML::ProcessEvent(window, *event);

			if (event->is<sf::Event::Closed>())
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Test Window");
        ImGui::Button("LOOK AT ME");
        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();

	}

	return 0;
}