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
			// for each item

			// for each key

			// for each goat ?

			// etc
		} espTimer++;
	}

	app::NolanBehaviour_FixedUpdate(__this, method);
}