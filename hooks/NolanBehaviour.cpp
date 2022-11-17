#include "pch-il2cpp.h"
#include "_hooks.h"
#include "utility.h"
#include "esp.hpp"
#include "game.h"

static int espTimerLimit = 500, espTimer = 450;
void dNolanBehaviour_FixedUpdate(NolanBehaviour* __this, MethodInfo* method)
{
	// collect all the game data ingame we need for ESP every 10 seconds since it's a resource heavy task
	if (IsInGame() && espTimer >= espTimerLimit)
	{
		Game::s_SurvivalInteractables = GetGameObjectsOfType("Assembly-CSharp", "SurvivalInteractable");
		Game::s_KeyInteractables = GetGameObjectsOfType("Assembly-CSharp", "KeyInteractable");
		//Game::s_GoatInteractables = GetGameObjectsOfType("Assembly-CSharp", "GoatInteractable");
	} espTimer++;

	app::NolanBehaviour_FixedUpdate(__this, method);
}