#include "pch-il2cpp.h"
#include "esp_tab.h"
#include "game.h"
#include "state.hpp"
#include "utility.h"

namespace EspTab {

	void Render() {
		if (not IsInGame())
			return;

		bool changed = false;
		if (ImGui::BeginTabItem("Esp")) {

			changed |= ImGui::Checkbox("Enable", &State.ShowEsp);

			ImGui::EndTabItem();
		}
		if (changed) {
			State.Save();
		}
	}
}