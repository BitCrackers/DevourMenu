#include "pch-il2cpp.h"
#include "self_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace SelfTab {
	std::vector<std::pair<const char*, const char*>> items
	{
		{"Hay", "SurvivalHay"},
		{"Goat", "SurvivalGoat"},
		{"Rat", "SurvivalRat"},
		{"FirstAid", "SurvivalFirstAid"},
		{"Battery", "SurvivalBattery"},
		{"Gasoline", "SurvivalGasoline"},
		{"MatchBox", "Matchbox-3"},
		{"Fuse", "SurvivalFuse"},
		{"RottenFood", "SurvivalRottenFood"},
		{"Bleach", "SurvivalBleach"},
	};
	static int selectedItem = 1;

	void Render() {
		if (not IsInGame())
			return;

		if (ImGui::BeginTabItem("Self")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("All Doors Unlocked", &State.DoorsUnlocked);

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			SteppedSliderFloat("Sprint Speed", &State.SprintSpeed, 2.f, 10.f, 0.5f, "%.2fx", 0);

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

			CustomListBoxPair("", &selectedItem, items, 75.f);
			ImGui::SameLine();
			if (ImGui::Button("Spawn") && IsInGame() && GetLocalPlayer())
			{
				app::NolanBehaviour_StartCarry(GetLocalPlayer(), convert_to_string(std::string(items.at(selectedItem).second)), NULL);
			}
			ImGui::EndTabItem();
		}
	}
}
