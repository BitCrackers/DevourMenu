#include "pch-il2cpp.h"
#include "esp_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"
#include "imgui/imgui.h"
#include "gui-helpers.hpp"

namespace EspTab {

	void Render() {
		if (not IsInGame())
			return;

		bool changed = false;
		if (ImGui::BeginTabItem("Esp")) {

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			changed |= ImGui::Checkbox("Enable ESP", &State.ShowEsp);

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			changed |= ImGui::Checkbox("Players##esp", &State.ShowEspPlayers);
			changed |= ImGui::Checkbox("Azazel##esp", &State.ShowEspAzazel);
			changed |= ImGui::Checkbox("Demons##esp", &State.ShowEspDemons);
			changed |= ImGui::Checkbox("Items##esp", &State.ShowEspItems);
			changed |= ImGui::Checkbox("Keys##esp", &State.ShowEspKeys);
			changed |= ImGui::Checkbox("Animals##esp", &State.ShowEspAnimals);

			ImGui::EndTabItem();
		}
		if (changed) {
			State.Save();
		}
	}
}