#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

void dSurvivalAzazelBehaviour_Update(SurvivalAzazelBehaviour* __this, MethodInfo* method)
{
	auto gObject = app::Component_get_gameObject((Component_1*)__this, NULL);

	if (not gObject) return app::SurvivalAzazelBehaviour_Update(__this, method);

	auto component = (UltimateCharacterLocomotion*)app::GameObject_GetComponentByName(gObject, convert_to_string(std::string("Opsive.UltimateCharacterController.Character.UltimateCharacterLocomotion")), NULL);

	if (not component) return app::SurvivalAzazelBehaviour_Update(__this, method);

	if (State.FreezeAzazel && app::UltimateCharacterLocomotion_get_TimeScale(component, NULL) != 0.f)
		app::UltimateCharacterLocomotion_set_TimeScale(component, 0.f, NULL);
	else if (not State.FreezeAzazel && app::UltimateCharacterLocomotion_get_TimeScale(component, NULL) == 0.f)
		app::UltimateCharacterLocomotion_set_TimeScale(component, 1.f, NULL);

	app::SurvivalAzazelBehaviour_Update(__this, method);
}

void dSurvivalAzazelBehaviour_OnKnockout(SurvivalAzazelBehaviour* __this, GameObject* ai, GameObject* player, MethodInfo* method)
{
	app::SurvivalAzazelBehaviour_OnKnockout(__this, ai, player, method);
}
