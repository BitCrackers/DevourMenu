#include "pch-il2cpp.h"
#include "self_tab.h"
#include "game.h"
#include "gui-helpers.hpp"
#include "imgui/imgui.h"
#include "state.hpp"
#include "utility.h"

namespace GameTab {
	void Render() {
		if (not IsInGame())
			return;

		if (ImGui::BeginTabItem("Game")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("Freeze Azazel", &State.FreezeAzazel);

			ImGui::EndTabItem();
		}
	}
}
