#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include "json.hpp"

namespace KeyBinds {
    struct Config {
        uint8_t Toggle_Menu;
    };

    void WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
    const char* ToString(uint8_t key);
    std::vector<uint8_t> GetValidKeys();
    bool IsKeyDown(uint8_t key);
    bool IsKeyPressed(uint8_t key);
    bool IsKeyReleased(uint8_t key);

    void to_json(nlohmann::ordered_json& j, KeyBinds::Config value);
    void from_json(const nlohmann::ordered_json& j, KeyBinds::Config& value);
}