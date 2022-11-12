#include "pch-il2cpp.h"
#include "game_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace GameTab {

	static const char* items[]{ "SurvivalHay", "SurvivalGoat", "SurvivalRat", "SurvivalFirstAid", "SurvivalBattery", "SurvivalGasoline", "SurvivalFuse", "SurvivalRottenFood", "SurvivalBleach", };
	static int selectedItem = 1;

	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("All Doors Unlocked", &State.doorsUnlocked);

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

			ImGui::Combo("##SpawnItems", &selectedItem, items, IM_ARRAYSIZE(items));
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (ImGui::Button("Spawn") && IsInGame() && GetLocalPlayer())
			{
				NolanBehaviour_StartCarry(GetLocalPlayer(), convert_to_string(std::string(items[selectedItem])), NULL);
			}

			/*ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Button("Debug Entities")) {
				il2cpp::Array entities = (*Game::pSceneObjects)->fields.entries;
				for (auto entity : entities) {
					printf("PrefabId: %s\n", GetPrefabName(entity.value->fields._prefabId).c_str());
				}
			}*/

			ImGui::EndTabItem();
		}
	}
}
