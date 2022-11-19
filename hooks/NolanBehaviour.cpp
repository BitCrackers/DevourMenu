#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "esp.hpp"
#include "game.h"

static int espTimerLimit = 25, espTimer = 0;
void dNolanBehaviour_FixedUpdate(NolanBehaviour* __this, MethodInfo* method)
{
	// collect all the game data ingame we need for ESP every 10 seconds since it's a resource heavy task
	if (IsInGame() && espTimer >= espTimerLimit)
	{
		drawing_t& instance = Esp::GetDrawing();
		synchronized(instance.m_DrawingMutex) {
			instance.m_data.clear();
		}

		auto scene_boxed = (Scene__Boxed*)il2cpp_value_box((Il2CppClass*)app::Scene__TypeInfo, &(Game::DontSaveOnLoadScene));
		il2cpp::Array gameObjects = app::Scene_GetRootGameObjects(scene_boxed, NULL);

		for (auto& object : gameObjects)
		{
			if (State.ShowEspItems)
			{
				auto component = app::GameObject_GetComponentByName(object, convert_to_string(std::string("SurvivalInteractable")), NULL);
				if (component)
				{
					EspData espData;
					espData.Type = EspType::ITEM;
					espData.Name = convert_from_string(((SurvivalInteractable*)component)->fields.prefabName).c_str();
					espData.Color = ImVec4(1.f, 1.f, 1.f, 1.f);
					espData.Position = app::Transform_get_position(app::Component_get_transform(component, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(espData);
					}
				}
			}

			if (State.ShowEspKeys)
			{
				auto component = app::GameObject_GetComponentByName(object, convert_to_string(std::string("KeyInteractable")), NULL);
				if (component)
				{
					EspData keyData;
					keyData.Type = EspType::KEY;
					keyData.Name = convert_from_string(app::KeyBehaviour_GetKeyName(((KeyInteractable*)component)->fields.keyBehaviour, NULL)).c_str();
					keyData.Color = ImVec4(0.15f, 0.97f, 0.99f, 1.f);
					keyData.Position = app::Transform_get_position(app::Component_get_transform(component, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(keyData);
					}
				}
			}

			if (State.ShowEspAnimals)
			{
				auto component = app::GameObject_GetComponentByName(object, convert_to_string(std::string("GoatInteractable")), NULL);
				if (component)
				{
					EspData goatData;
					goatData.Type = EspType::ANIMAL;
					goatData.Name = convert_from_string(((GoatInteractable*)component)->fields.prefabName).c_str();
					goatData.Color = ImVec4(0.f, 1.f, 0.f, 1.f);
					goatData.Position = app::Transform_get_position(app::Component_get_transform(component, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(goatData);
					}
				}
			}
		}
		espTimer = 0;
	} espTimer++;

	app::NolanBehaviour_FixedUpdate(__this, method);
}