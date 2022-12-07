#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "esp.hpp"
#include "game.h"

static int espTimerLimit = 25, espTimer = 0;
void dNolanBehaviour_FixedUpdate(NolanBehaviour* __this, MethodInfo* method)
{

	// only execute this ingame for local player
	if (IsInGame() && IsLocalPlayer(__this))
	{
		// Apply Sprint Speed
		if (__this->fields.speedChangeAbility)
		{
			__this->fields.speedChangeAbility->fields.m_SpeedChangeMultiplier = State.SprintSpeed;
			__this->fields.speedChangeAbility->fields.m_MaxSpeedChangeValue = State.SprintSpeed;
		}
	}

	// collect all the game data ingame
	if (IsInGame()
		&& not IsSequencePlaying()
		&& State.ShowEsp
		&& espTimer >= espTimerLimit)
	{
		drawing_t& instance = Esp::GetDrawing();
		synchronized(instance.m_DrawingMutex) {
			instance.m_data.clear();
		}

		auto scene_boxed = (Scene__Boxed*)il2cpp_value_box((Il2CppClass*)app::Scene__TypeInfo, &(Game::DontSaveOnLoadScene));
		il2cpp::Array gameObjects = app::Scene_GetRootGameObjects(scene_boxed, NULL);

		for (auto& object : gameObjects)
		{
			if (State.ShowEspPlayers && IsOnline())
			{
				auto component = (DissonancePlayerTracking*)app::GameObject_GetComponentByName(object, convert_to_string(std::string("DissonancePlayerTracking")), NULL);
				if (component && not IsLocalPlayer(component))
				{
					EspData playerData;
					playerData.Type = EspType::PLAYER;
					playerData.Name = convert_from_string(Object_1_get_name((Object_1*)object, NULL));
					playerData.Color = ImVec4(1.f, 1.f, 1.f, 1.f);
					playerData.Position = app::Transform_get_position(app::GameObject_get_transform(object, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(playerData);
					}
				}
			}

			if (State.ShowEspAzazel)
			{
				auto component = (SurvivalAzazelBehaviour*)app::GameObject_GetComponentByName(object, convert_to_string(std::string("SurvivalAzazelBehaviour")), NULL);
				if (component)
				{
					EspData azazelData;
					azazelData.Type = EspType::AZAZEL;
					azazelData.Name = std::string("Azazel");
					azazelData.Color = ImVec4(1.f, 0.f, 0.f, 1.f);
					azazelData.Position = app::Transform_get_position(app::GameObject_get_transform(object, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(azazelData);
					}
				}
			}

			if (State.ShowEspDemons)
			{
				auto component = (SurvivalDemonBehaviour*)app::GameObject_GetComponentByName(object, convert_to_string(std::string("SurvivalDemonBehaviour")), NULL);
				if (component)
				{
					EspData demonData;
					demonData.Type = EspType::DEMON;
					demonData.Name = std::string("Demon");
					demonData.Color = ImVec4(1.f, 0.65f, 0.f, 1.f);
					demonData.Position = app::Transform_get_position(app::GameObject_get_transform(object, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(demonData);
					}
				}
			}

			if (State.ShowEspItems)
			{
				auto component = app::GameObject_GetComponentByName(object, convert_to_string(std::string("SurvivalInteractable")), NULL);
				if (component)
				{
					EspData itemData;
					itemData.Type = EspType::ITEM;
					itemData.Name = convert_from_string(((SurvivalInteractable*)component)->fields.prefabName);
					itemData.Color = ImVec4(1.f, 1.f, 1.f, 1.f);
					itemData.Position = app::Transform_get_position(app::Component_get_transform(component, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(itemData);
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
					keyData.Name = convert_from_string(app::KeyBehaviour_GetKeyName(((KeyInteractable*)component)->fields.keyBehaviour, NULL));
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
					EspData animalData;
					animalData.Type = EspType::ANIMAL;
					animalData.Name = convert_from_string(((GoatInteractable*)component)->fields.prefabName);
					animalData.Color = ImVec4(0.f, 1.f, 0.f, 1.f);
					animalData.Position = app::Transform_get_position(app::Component_get_transform(component, NULL), NULL);

					synchronized(instance.m_DrawingMutex) {
						instance.m_data.push_back(animalData);
					}
				}
			}
		}
		espTimer = 0;
	} espTimer++;

	app::NolanBehaviour_FixedUpdate(__this, method);
}