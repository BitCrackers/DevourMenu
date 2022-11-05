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

    void Load();
    void Save();
};

extern Settings State;