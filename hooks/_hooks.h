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