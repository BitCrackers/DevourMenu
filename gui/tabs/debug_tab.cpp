#include "pch-il2cpp.h"
#include "debug_tab.h"
#include "imgui/imgui.h"
#include "state.hpp"
#include "main.h"
#include "game.h"
#include "profiler.h"
#include "logger.h"
#include <iostream>
#include <sstream>
#include "gui-helpers.hpp"

namespace DebugTab {
	void Render() {
		if (ImGui::BeginTabItem("Debug")) {
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#ifndef _VERSION
			if (ImGui::Button("Unload DLL"))
			{
				SetEvent(hUnloadEvent);
			}
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
#endif

			if (ImGui::Button("Force Load Settings"))
			{
				State.Load();
			}
			if (ImGui::Button("Force Save Settings"))
			{
				State.Save();
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			ImGui::Checkbox("Log Unity Debug Messages", &State.ShowUnityLogs);

			ImGui::EndTabItem();
		}
	}
}