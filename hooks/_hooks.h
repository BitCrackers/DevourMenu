#pragma once

void DetourInitilization();
void DetourUninitialization();

void dDebug_Log(Object* message, MethodInfo* method);
void dDebug_LogError(Object* message, MethodInfo* method);
void dDebug_LogException(Exception* exception, MethodInfo* method);
void dDebug_LogWarning(Object* message, MethodInfo* method);

UIOutfitSelectionType* dMenu_2_SetupOutfit(MenuM_2* __this, CharacterOutfit* outfit, MethodInfo* method);
UIPerkSelectionType* dMenu_2_SetupPerk(MenuM_2* __this, CharacterPerk* perk, MethodInfo* method);
UIFlashlightSelectionType* dMenu_2_SetupFlashlight(MenuM_2* __this, CharacterFlashlight* flashlight, MethodInfo* method);
UIPetSelectionType* dMenu_2_SetupPet(MenuM_2* __this, CharacterPet* pet, MethodInfo* method);

bool dAchievementHelpers_ShowHardModeUnlocked(AchievementHelpers* __this, MethodInfo* method);
bool dAchievementHelpers_ShowHardRobeUnlocked(AchievementHelpers* __this, MethodInfo* method);
bool dAchievementHelpers_ShowNightmareModeUnlocked(AchievementHelpers* __this, MethodInfo* method);

bool dOptionsHelpers_IsCharacterUnlocked(OptionsHelpers* __this, String* prefab, MethodInfo* method);
bool dOptionsHelpers_IsRobeUnlocked(OptionsHelpers* __this, String* robe, MethodInfo* method);

bool dSurvivalLobbyController_CanReady(SurvivalLobbyController* __this, MethodInfo* method);
bool dSurvivalLobbyController_PlayableCharacterSelected(SurvivalLobbyController* __this, MethodInfo* method);
bool dSurvivalLobbyController_UnlockedCharacterSelected(SurvivalLobbyController* __this, MethodInfo* method);

bool dLockedInteractable_CanInteract(LockedInteractable* __this, GameObject* character, MethodInfo* method);

void dNolanBehaviour_FixedUpdate(NolanBehaviour* __this, MethodInfo* method);

bool dCursor_get_visible(MethodInfo* method);
void dCursor_set_visible(bool value, MethodInfo* method);
CursorLockMode__Enum dCursor_get_lockState(MethodInfo* method);
void dCursor_set_lockState(CursorLockMode__Enum value, MethodInfo* method);

void dSurvivalAzazelBehaviour_Update(SurvivalAzazelBehaviour* __this, MethodInfo* method);
void dSurvivalAzazelBehaviour_OnKnockout(SurvivalAzazelBehaviour* __this, GameObject* ai, GameObject* player, MethodInfo* method);
