#include "pch-il2cpp.h"
#include "game_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace GameTab {
	void Render() {
		if (ImGui::BeginTabItem("Game")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			ImGui::Checkbox("All Doors Unlocked", &State.doorsUnlocked);
			ImGui::EndTabItem();
		}
	}
}
