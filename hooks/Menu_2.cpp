#include "pch-il2cpp.h"
#include "_hooks.h"

UIOutfitSelectionType* dMenu_2_SetupOutfit(MenuM_2* __this, CharacterOutfit* outfit, MethodInfo* method)
{
	outfit->fields.isHidden = false;
	outfit->fields.isOwned = true;
	outfit->fields.basePrice = 0;
	outfit->fields.currentPrice = 0;
	return Menu_2_SetupOutfit(__this, outfit, method);
}

UIPerkSelectionType* dMenu_2_SetupPerk(MenuM_2* __this, CharacterPerk* perk, MethodInfo* method)
{
	perk->fields.isHidden = false;
	perk->fields.isOwned = true;
	perk->fields.cost = 0;
	return Menu_2_SetupPerk(__this, perk, method);
}

UIFlashlightSelectionType* dMenu_2_SetupFlashlight(MenuM_2* __this, CharacterFlashlight* flashlight, MethodInfo* method)
{
	flashlight->fields.isHidden = false;
	flashlight->fields.isOwned = true;
	flashlight->fields.cost = 0;
	return Menu_2_SetupFlashlight(__this, flashlight, method);
}

UIPetSelectionType* dMenu_2_SetupPet(MenuM_2* __this, CharacterPet* pet, MethodInfo* method)
{
	pet->fields.isHidden = false;
	pet->fields.isOwned = true;
	return Menu_2_SetupPet(__this, pet, method);
}
