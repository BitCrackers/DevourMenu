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
	static const char* items[]{ "SurvivalHay", "SurvivalGoat", "SurvivalRat", "SurvivalFirstAid", "SurvivalBattery", "SurvivalGasoline", "SurvivalFuse", "SurvivalRottenFood", "SurvivalBleach", };
	static int selectedItem = 1;

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

			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);
			ImGui::Separator();
			ImGui::Dummy(ImVec2(7, 7) * State.dpiScale);

			ImGui::Combo("##SpawnItems", &selectedItem, items, IM_ARRAYSIZE(items));
			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);
			if (ImGui::Button("Spawn") && IsInGame() && GetLocalPlayer())
			{
				app::NolanBehaviour_StartCarry(GetLocalPlayer(), convert_to_string(std::string(items[selectedItem])), NULL);
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Button("Debug Interactables"))
			{
				il2cpp::Array goatArray = GetGameObjectsOfType("Assembly-CSharp", "GoatInteractable");
				il2cpp::Array keyArray = GetGameObjectsOfType("Assembly-CSharp", "KeyInteractable");
				il2cpp::Array survivalArray = GetGameObjectsOfType("Assembly-CSharp", "SurvivalInteractable");

				for (auto interactable : goatArray)
				{
					printf("Goat: %s\n", convert_from_string(((GoatInteractable*)interactable)->fields.prefabName).c_str());
				}

				for (auto interactable : keyArray)
				{
					printf("Key: %s\n", convert_from_string(app::KeyBehaviour_GetKeyName(((KeyInteractable*)interactable)->fields.keyBehaviour, NULL)).c_str());
				}

				for (auto interactable : survivalArray)
				{
					printf("Survival: %s\n", convert_from_string(((SurvivalInteractable*)interactable)->fields.prefabName).c_str());
				}


				printf("Active Scene: %s\n", GetActiveSceneName().c_str());
			}

			ImGui::Dummy(ImVec2(4, 4) * State.dpiScale);

			if (ImGui::Button("Debug GameObjects"))
			{
				auto gameObjects = GetGameObjectsInAllScenes();
				printf("%llu GameObjects found.\n", gameObjects.size());
			}

			ImGui::EndTabItem();
		}
	}
}