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
            Log.Info(e.what()); \
        }

        JSON_TRYGET("ShowMenu", this->ShowMenu);
        JSON_TRYGET("KeyBinds", this->KeyBinds);
        JSON_TRYGET("AdjustByDPI", this->KeyBinds);
        JSON_TRYGET("ShowUnityLogs", this->ShowUnityLogs);
    } catch (...) {
        Log.Info("Unable to load settings.json");
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
            {"AdjustByDPI", this->AdjustByDPI},
            {"ShowUnityLogs", this->ShowUnityLogs}
        };

        std::ofstream outSettings(settingsPath);
        outSettings << std::setw(4) << j << std::endl;
    } catch (...) {
        Log.Info("Unable to save settings.json");
    }
}
