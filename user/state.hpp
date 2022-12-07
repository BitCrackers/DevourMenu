#pragma once
#include <bitset>
#include <queue>
#include "keybinds.h"
#include "game.h"

class Settings {
public:

    KeyBinds::Config KeyBinds = {
        VK_DELETE // toggle menu
    };

    bool ImGuiInitialized = false;
    bool ShowMenu = false;

#ifdef _DEBUG
    bool showDebugTab = false;
#endif

    bool AdjustByDPI = true;
    float dpiScale = 1.f;
    bool dpiChanged = false;

    bool ShowUnityLogs = true;

    bool DoorsUnlocked = false;
    float SprintSpeed = 2.f;

    bool ShowEsp = false;
    bool ShowEspPlayers = false;
    bool ShowEspAzazel = false;
    bool ShowEspDemons = false;
    bool ShowEspItems = false;
    bool ShowEspKeys = false;
    bool ShowEspAnimals = false;

    bool FreezeAzazel = false;

    void Load();
    void Save();
};

extern Settings State;