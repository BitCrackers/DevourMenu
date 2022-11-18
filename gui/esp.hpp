#pragma once

#include <vector>
#include <mutex>
#include "state.hpp"
#include "game.h"
#include "utility.h"
#include "DirectX.h"
#include <imgui/imgui.h>

enum EspType
{
	UNKNOWN = 0,
	PLAYER = 1,
	ITEM = 2,
	KEY = 3,
	ANIMAL = 4
};

struct EspData
{
	app::Vector3 Position = { 0.0f, 0.0f, 0.f };
	ImVec4 Color{ 0.0f, 0.0f, 0.0f, 0.0f };
	std::string Name = std::string();
	EspType Type = EspType::UNKNOWN;
};

static bool IsWithinScreenBounds(Vector2& pos)
{
	return pos.x < (float)app::Screen_get_width(nullptr) && pos.y < (float)app::Screen_get_height(nullptr);
}

static bool IsWithinScreenBounds(app::Vector3& pos)
{
	return pos.x < (float)app::Screen_get_width(nullptr) && pos.y < (float)app::Screen_get_height(nullptr) && pos.z > 0;
}

typedef struct Drawing
{
	std::mutex m_DrawingMutex;

	std::vector<EspData> m_data;

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