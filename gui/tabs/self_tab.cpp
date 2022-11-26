#include "pch-il2cpp.h"
#include "self_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace SelfTab {
	std::vector<const char*> items = { "Hay", "Goat", "Rat", "FirstAid", "Battery", "Gasoline", "Fuse", "RottenFood", "Bleach" };
	static int selectedItem = 1;

	void Render() {
		if (not IsInGame())
			return;

		if (ImGui::BeginTabItem("Self")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("All Doors Unlocked", &State.doorsUnlocked);

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

			CustomListBoxInt("", &selectedItem, items, 75.f);
			ImGui::SameLine();
			if (ImGui::Button("Spawn") && IsInGame() && GetLocalPlayer())
			{
				app::NolanBehaviour_StartCarry(GetLocalPlayer(), convert_to_string("Survival" + std::string(+items[selectedItem])), NULL);
			}

			ImGui::EndTabItem();
		}
	}
}
