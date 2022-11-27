#include "pch-il2cpp.h"
#include "_hooks.h"
#include "state.hpp"

bool dLockedInteractable_CanInteract(LockedInteractable* __this, GameObject* character, MethodInfo* method)
{
	if (State.DoorsUnlocked) {
		__this->fields.isLocked = false;
		return true;
	}

	return LockedInteractable_CanInteract(__this, character, method);
}
