#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "esp.hpp"

static int espTimer = 0, espTimerLimit = 1000;
void dNolanBehaviour_FixedUpdate(NolanBehaviour* __this, MethodInfo* method)
{
	// collect all the game data ingame we need for ESP
	if (IsInGame())
	{
		if (espTimer >= espTimerLimit)
		{
			drawing_t& instance = Esp::GetDrawing();
			synchronized(instance.m_DrawingMutex) {
				if (__this->fields._._._._._entity->fields._entity->fields.IsOwner)
					instance.LocalPosition = app::Transform_get_position(app::Component_get_transform((Component_1*)__this, NULL), NULL);

				il2cpp::List m_Players = (*Game::pInGameHelpers)->fields.m_Survival->fields.m_PlayerNolanBehaviours;
				int i = 0;
				for (auto player : m_Players)
				{
					instance.m_Players[i] = app::Transform_get_position(app::Component_get_transform((Component_1*)player, NULL), NULL);
					i++;
				}

			}
		} espTimer++;
	}

	app::NolanBehaviour_FixedUpdate(__this, method);
}