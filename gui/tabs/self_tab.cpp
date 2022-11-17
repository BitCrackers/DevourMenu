#include "pch-il2cpp.h"
#include "self_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace SelfTab {
	void Render() {
		if (not IsInGame())
			return;

		if (ImGui::BeginTabItem("Self")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("All Doors Unlocked", &State.doorsUnlocked);

			ImGui::EndTabItem();
		}
	}
}