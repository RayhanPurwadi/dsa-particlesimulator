#include <optional>

#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_internal.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

#include "environment.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode({1600, 800}), "Particle Simulator :: Rayhan - 5024241032");
	window.setFramerateLimit(90);
	if (!ImGui::SFML::Init(window)) {
		exit(1);
	}

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	Environment env;
	sf::Clock deltaClock;

	// show balls
	for (int i = 0; i < 30; i++) env.create_particle({50 + 30*i, 50}, {10, 10}, 0 + 10*i, {100, -1});

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

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags host_window_flags = 0;
        host_window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        host_window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        host_window_flags |= ImGuiWindowFlags_NoDocking;
        host_window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Host", nullptr, host_window_flags);
        ImGui::PopStyleVar(3);

        ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
		ImGui::PopStyleColor();

		static bool first_time = true;
        if (first_time) {
            first_time = false;

            ImGui::DockBuilderRemoveNode(dockspace_id); 
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
            ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

            ImGuiID right_id;
            ImGuiID main_id = dockspace_id;
            ImGui::DockBuilderSplitNode(main_id, ImGuiDir_Right, 0.3f, &right_id, &main_id);

            ImGui::DockBuilderDockWindow("Configuration", right_id);

            ImGui::DockBuilderFinish(dockspace_id);
        }

		ImVec2 arenaSize = ImGui::GetWindowSize();
        ImGui::End();

		ImGui::Begin("Configuration");
		ImVec2 windowSize = ImGui::GetWindowSize();

		ImGui::SetWindowFontScale(1.3f);
		ImGui::PushTextWrapPos(windowSize.x);

		ImGui::Text("(C) 2025 Rayhan D Purwadi");
		ImGui::Text("You can set numerous things in this configuration window");

		ImGui::Spacing();
		ImGui::SetWindowFontScale(2.0f);
		ImGui::Text("Spawner");

		ImGui::Spacing();
		ImGui::SetWindowFontScale(2.0f);
		ImGui::Text("Stats");

		ImGui::PopTextWrapPos();
		ImGui::SetWindowFontScale(1.0f); 
		ImGui::End();

		window.clear();

		env.arenaSize = arenaSize;
		env.render(&window, delta);
		ImGui::SFML::Render(window);
		
		window.display();
	}

	return 0;
}