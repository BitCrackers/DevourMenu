#include "pch-il2cpp.h"
#include "state.hpp"
#include <iostream>
#include <fstream>
#include "main.h"
#include "utility.h"
#include "logger.h"

Settings State;

void Settings::Load() {
    auto path = getModulePath(hModule);
    auto settingsPath = path.parent_path() / "settings.json";

    if (!std::filesystem::exists(settingsPath))
        return;

    try {
        std::ifstream inSettings(settingsPath);
        nlohmann::ordered_json j = nlohmann::ordered_json::parse(inSettings, NULL, false);

#define JSON_TRYGET(key, value) \
        try { \
            j.at(key).get_to(value); \
        } catch (nlohmann::detail::out_of_range& e) { \
            DLog.Info(e.what()); \
        }

        JSON_TRYGET("ShowMenu", this->ShowMenu);
        JSON_TRYGET("KeyBinds", this->KeyBinds);
#ifdef _DEBUG
        JSON_TRYGET("ShowDebug", this->showDebugTab);
#endif
        JSON_TRYGET("AdjustByDPI", this->AdjustByDPI);
        JSON_TRYGET("ShowUnityLogs", this->ShowUnityLogs);
        JSON_TRYGET("ShowEsp", this->ShowEsp);
        JSON_TRYGET("ShowEspPlayers", this->ShowEspPlayers);
        JSON_TRYGET("ShowEspAzazel", this->ShowEspAzazel);
        JSON_TRYGET("ShowEspDemons", this->ShowEspDemons);
        JSON_TRYGET("ShowEspItems", this->ShowEspItems);
        JSON_TRYGET("ShowEspKeys", this->ShowEspKeys);
        JSON_TRYGET("ShowEspAnimals", this->ShowEspAnimals);
        JSON_TRYGET("doorsUnlocked", this->doorsUnlocked);
    } catch (...) {
        DLog.Info("Unable to load settings.json");
    }

    //Do not do any IL2CPP stuff here!  The constructors of most classes have not run yet!
}

void Settings::Save() {
    auto path = getModulePath(hModule);
    auto settingsPath = path.parent_path() / "settings.json";

    try {
        nlohmann::ordered_json j = nlohmann::ordered_json{
            {"ShowMenu", this->ShowMenu},
            {"KeyBinds", this->KeyBinds},
    #ifdef _DEBUG
            {"ShowDebug", this->showDebugTab},
    #endif
            {"AdjustByDPI", this->AdjustByDPI},
            {"ShowUnityLogs", this->ShowUnityLogs},
            {"ShowEsp", this->ShowEsp},
            {"ShowEspPlayers", this->ShowEspPlayers},
            {"ShowEspAzazel", this->ShowEspAzazel},
            {"ShowEspDemons", this->ShowEspDemons},
            {"ShowEspItems", this->ShowEspItems},
            {"ShowEspKeys", this->ShowEspKeys},
            {"ShowEspAnimals", this->ShowEspAnimals},
            {"doorsUnlocked", this->doorsUnlocked}
        };

        std::ofstream outSettings(settingsPath);
        outSettings << std::setw(4) << j << std::endl;
    } catch (...) {
        DLog.Info("Unable to save settings.json");
    }
}
