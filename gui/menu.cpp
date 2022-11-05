#include "pch-il2cpp.h"
#include "menu.hpp"
#include "imgui/imgui.h"
#include "tabs/game_tab.h"
#include "tabs/settings_tab.h"
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
		GameTab::Render();

		if(firstRender)
			firstRender = false;

		ImGui::EndTabBar();
		ImGui::End();
	}
}