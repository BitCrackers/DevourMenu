#include "pch-il2cpp.h"
#include "menu.hpp"
#include "imgui/imgui.h"
#include "tabs/self_tab.h"
#include "tabs/esp_tab.h"
#include "tabs/settings_tab.h"
#include "tabs/debug_tab.h"
#include "state.hpp"
#include "gui-helpers.hpp"

namespace Menu {
	void Init() {
		ImGui::SetNextWindowSize(ImVec2(520, 330 ) * State.dpiScale, ImGuiCond_None);
		ImGui::SetNextWindowBgAlpha(1.F);
	}

	bool init = false;
	bool firstRender = true;
	void Render() {
		if (!init)
			Menu::Init();

		ImGui::Begin("DevourMenu", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("AmongUs#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		if(!firstRender)
			SettingsTab::Render();
		SelfTab::Render();
		EspTab::Render();
#ifdef _DEBUG
		if (State.showDebugTab)
			DebugTab::Render();
#endif

		if(firstRender)
			firstRender = false;

		ImGui::EndTabBar();
		ImGui::End();
	}
}