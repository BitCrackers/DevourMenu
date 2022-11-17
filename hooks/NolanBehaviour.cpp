#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "esp.hpp"
#include "game.h"

static int espTimerLimit = 500, espTimer = 0;
void dNolanBehaviour_FixedUpdate(NolanBehaviour* __this, MethodInfo* method)
{
	// collect all the game data ingame we need for ESP every 10 seconds since it's a resource heavy task
	if (IsInGame() && espTimer >= espTimerLimit)
	{
		drawing_t& instance = Esp::GetDrawing();
		synchronized(instance.m_DrawingMutex) {
			instance.m_data.clear();
		}

		if (State.ShowEspItems)
		{
			il2cpp::Array s_SurvivalInteractables = GetGameObjectsOfType("Assembly-CSharp", "SurvivalInteractable");
			for (auto* item : s_SurvivalInteractables)
			{
				EspData espData;
				espData.Type = EspType::ITEM;
				espData.Name = convert_from_string(((SurvivalInteractable*)item)->fields.prefabName).c_str();
				espData.Color = ImVec4(1.f, 1.f, 1.f, 1.f);
				espData.Position = app::Transform_get_position(app::Component_get_transform((Component_1*)item, NULL), NULL);

				synchronized(instance.m_DrawingMutex) {
					instance.m_data.push_back(espData);
				}
			}
		}
		
		if (State.ShowEspKeys)
		{
			il2cpp::Array s_KeyInteractables = GetGameObjectsOfType("Assembly-CSharp", "KeyInteractable");
			for (auto* key : s_KeyInteractables)
			{
				EspData keyData;
				keyData.Type = EspType::KEY;
				keyData.Name = convert_from_string(app::KeyBehaviour_GetKeyName(((KeyInteractable*)key)->fields.keyBehaviour, NULL)).c_str();
				keyData.Color = ImVec4(0.15f, 0.97f, 0.99f, 1.f);
				keyData.Position = app::Transform_get_position(app::Component_get_transform((Component_1*)key, NULL), NULL);

				synchronized(instance.m_DrawingMutex) {
					instance.m_data.push_back(keyData);
				}
			}
		}

		if (State.ShowEspGoats)
		{
			il2cpp::Array s_GoatInteractables = GetGameObjectsOfType("Assembly-CSharp", "GoatInteractable");
			for (auto* goat : s_GoatInteractables)
			{
				EspData goatData;
				goatData.Type = EspType::GOAT;
				goatData.Name = convert_from_string(((GoatInteractable*)goat)->fields.prefabName).c_str();
				goatData.Color = ImVec4(0.f, 1.f, 0.f, 1.f);
				goatData.Position = app::Transform_get_position(app::Component_get_transform((Component_1*)goat, NULL), NULL);

				synchronized(instance.m_DrawingMutex) {
					instance.m_data.push_back(goatData);
				}
			}
		}
	} espTimer++;

	app::NolanBehaviour_FixedUpdate(__this, method);
}