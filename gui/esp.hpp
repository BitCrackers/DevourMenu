#pragma once

#include <vector>
#include <mutex>
#include "state.hpp"
#include "game.h"
#include "utility.h"
#include "DirectX.h"
#include <imgui/imgui.h>

static float GetScaleFromValue(float value)
{
	float scale = DirectX::GetWindowSize().y / 1080.0f;
	return (value * scale);
}

static bool IsWithinScreenBounds(Vector2& pos)
{
	return pos.x < (float)app::Screen_get_width(nullptr) && pos.y < (float)app::Screen_get_height(nullptr);
}

typedef struct Drawing
{
	std::mutex m_DrawingMutex;

	std::array<app::Vector3, Game::MAX_PLAYERS> m_Players;

	app::Vector3 LocalPosition{ 0.0f, 0.0f, 0.f };
} drawing_t;

class Esp
{
public:
	static void Render();

	static drawing_t& GetDrawing() { return *s_Instance; }
private:
	static drawing_t* s_Instance;
};