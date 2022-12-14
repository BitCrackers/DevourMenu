#include "pch-il2cpp.h"
#include "settings_tab.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "achievements.hpp"
#include "DirectX.h"
#include "imgui/imgui_impl_win32.h" // ImGui_ImplWin32_GetDpiScaleForHwnd
#include "theme.hpp" // ApplyTheme
#include "gui-helpers.hpp"

namespace SettingsTab {
	void Render() {
		if (ImGui::BeginTabItem("Settings")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			ImGui::Text("Show/Hide Menu Keybind:");
			ImGui::SameLine();
			if (HotKey(State.KeyBinds.Toggle_Menu)) {
				State.Save();
			}

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale); 
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			if (ImGui::Checkbox("Adjust by DPI", &State.AdjustByDPI)) {
				if (!State.AdjustByDPI) {
					State.dpiScale = 1.0f;
				}
				else {
					State.dpiScale = ImGui_ImplWin32_GetDpiScaleForHwnd(DirectX::window);
				}
				State.dpiChanged = true;
				State.Save();
			}
#ifdef _DEBUG
			static const std::vector<const char*> DPI_SCALING_LEVEL = { "100%", "125%", "150%", "175%", "200%", "225%", "250%", "275%", "300%" };
			ImGui::SameLine();
			int scaleIndex =(int(std::clamp(State.dpiScale, 1.0f, 3.0f) * 100.0f) - 100) / 25;
			if (CustomListBoxInt("Scaling Level", &scaleIndex, DPI_SCALING_LEVEL, 100 * State.dpiScale)) {
				State.dpiScale = (scaleIndex * 25 + 100) / 100.0f;
				State.dpiChanged = true;
			}
#endif
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

#ifdef _DEBUG
			if (ImGui::Checkbox("Show Debug Tab", &State.showDebugTab)) {
				State.Save();
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#endif

			if (ImGui::Button("Unlock All Steam Achievements")) {
				AchievementHelpers* ah = AchievementHelpers_get_singleton(NULL);
				for (const char* achievement : steamAchievements) {
					AchievementHelpers_Unlock(ah, convert_to_string(std::string(achievement)), false, NULL);
				}
			}

			ImGui::EndTabItem();
		}
	}
}