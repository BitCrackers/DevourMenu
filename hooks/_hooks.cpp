#include "pch-il2cpp.h"
#include "_hooks.h"
#include "detours/detours.h"
#include "DirectX.h"
#include <iostream>
#include "main.h"
#include "SignatureScan.hpp"
#include "game.h"

using namespace Game;

bool HookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourAttach(ppPointer, pDetour); error != NO_ERROR) {
		std::cout << "Failed to hook " << functionName << ", error " << error << std::endl;
		return false;
	}
	//std::cout << "Hooked " << functionName << std::endl;
	return true;
}

#define HOOKFUNC(n) if (!HookFunction(&(PVOID&)n, d ## n, #n)) return;

bool UnhookFunction(PVOID* ppPointer, PVOID pDetour, const char* functionName) {
	if (const auto error = DetourDetach(ppPointer, pDetour); error != NO_ERROR) {
		std::cout << "Failed to unhook " << functionName << ", error " << error << std::endl;
		return false;
	}
	//std::cout << "Unhooked " << functionName << std::endl;
	return true;
}

#define UNHOOKFUNC(n) if (!UnhookFunction(&(PVOID&)n, d ## n, #n)) return;

void DetourInitilization() {
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	directx11 d3d11 = directx11();
	if (!d3d11.presentFunction) {
		std::cout << "Unable to retrieve IDXGISwapChain::Present method" << std::endl;
		return;
	} else {
		// Attempting to hook the Steam overlay
		do {
			if (oPresent)
				break;
			HMODULE hModule = GetModuleHandleA("GameOverlayRenderer.dll");
			if (!hModule)
				break;
			oPresent = SignatureScan<D3D_PRESENT_FUNCTION>("55 8B EC 53 8B 5D ? F6 C3 01 74 ? 53 FF 75 ? FF 75 ? FF 15 ? ? ? ? 5B 5D C2", hModule);
			if (oPresent)
				break;
			if (MessageBox(NULL,
				L"Failed to hook the Steam overlay D3DPresent function.\nThis may cause the menu to be visible to streaming applications.  Do you wish to continue?",
				L"Error",
				MB_YESNO | MB_ICONWARNING) == IDNO)
			{
#ifndef _VERSION
				SetEvent(hUnloadEvent); //Might as well unload the DLL if we're not going to render anything
#endif
				return;
			}
			oPresent = d3d11.presentFunction;
		} while (0);
		if (!oPresent)
			oPresent = d3d11.presentFunction;
	}

	HOOKFUNC(Debug_Log);
	HOOKFUNC(Debug_LogError);
	HOOKFUNC(Debug_LogException);
	HOOKFUNC(Debug_LogWarning);
	HOOKFUNC(Menu_2_SetupOutfit);
	HOOKFUNC(Menu_2_SetupPerk);
	HOOKFUNC(Menu_2_SetupFlashlight);
	HOOKFUNC(Menu_2_SetupPet);
	HOOKFUNC(AchievementHelpers_ShowHardModeUnlocked);
	HOOKFUNC(AchievementHelpers_ShowHardRobeUnlocked);
	HOOKFUNC(AchievementHelpers_ShowNightmareModeUnlocked);
	HOOKFUNC(OptionsHelpers_IsCharacterUnlocked);
	HOOKFUNC(OptionsHelpers_IsRobeUnlocked);
	HOOKFUNC(SurvivalLobbyController_CanReady);
	HOOKFUNC(SurvivalLobbyController_PlayableCharacterSelected);
	HOOKFUNC(SurvivalLobbyController_UnlockedCharacterSelected);
	HOOKFUNC(LockedInteractable_CanInteract)

	if (!HookFunction(&(PVOID&)oPresent, dPresent, "D3D_PRESENT_FUNCTION")) return;

	DetourTransactionCommit();
}

void DetourUninitialization()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	UNHOOKFUNC(Debug_Log);
	UNHOOKFUNC(Debug_LogError);
	UNHOOKFUNC(Debug_LogException);
	UNHOOKFUNC(Debug_LogWarning);
	UNHOOKFUNC(Menu_2_SetupOutfit);
	UNHOOKFUNC(Menu_2_SetupPerk);
	UNHOOKFUNC(Menu_2_SetupFlashlight);
	UNHOOKFUNC(Menu_2_SetupPet);
	UNHOOKFUNC(AchievementHelpers_ShowHardModeUnlocked);
	UNHOOKFUNC(AchievementHelpers_ShowHardRobeUnlocked);
	UNHOOKFUNC(AchievementHelpers_ShowNightmareModeUnlocked);
	UNHOOKFUNC(OptionsHelpers_IsCharacterUnlocked);
	UNHOOKFUNC(OptionsHelpers_IsRobeUnlocked);
	UNHOOKFUNC(SurvivalLobbyController_CanReady);
	UNHOOKFUNC(SurvivalLobbyController_PlayableCharacterSelected);
	UNHOOKFUNC(SurvivalLobbyController_UnlockedCharacterSelected);
	UNHOOKFUNC(LockedInteractable_CanInteract)

	if (DetourDetach(&(PVOID&)oPresent, dPresent) != 0) return;

	DetourTransactionCommit();
	DirectX::Shutdown();
}