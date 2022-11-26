#include "pch-il2cpp.h"
#include "esp.hpp"
#include "DirectX.h"
#include "utility.h"
#include "game.h"
#include "gui-helpers.hpp"

drawing_t* Esp::s_Instance = new drawing_t();
ImGuiWindow* CurrentWindow = nullptr;

static void RenderText(const char* text, const ImVec2& pos, const ImVec4& color, const bool outlined = true, const bool centered = true)
{
	if (!text) return;
	ImVec2 ImScreen = pos;
	if (centered)
	{
		auto size = ImGui::CalcTextSize(text);
		ImScreen.x -= size.x * 0.5f;
		ImScreen.y -= size.y;
	}

	if (outlined)
	{
		CurrentWindow->DrawList->AddText(nullptr, 0.f,
			ImScreen + 0.5f * State.dpiScale,
			ImGui::GetColorU32(IM_COL32_BLACK), text);
	}

	CurrentWindow->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text);
}

static void RenderLine(const ImVec2& start, const ImVec2& end, const ImVec4& color, bool shadow = false) noexcept
{
	if (shadow)
	{
		CurrentWindow->DrawList->AddLine(
			start + 0.5f * State.dpiScale,
			end + 0.5f * State.dpiScale,
			ImGui::GetColorU32(color) & IM_COL32_A_MASK, 1.0f * State.dpiScale);
	}

	CurrentWindow->DrawList->AddLine(start, end, ImGui::GetColorU32(color), 1.0f * State.dpiScale);
}

static void RenderBox(const ImVec2 top, const ImVec2 bottom, const float height, const float width, const ImVec4& color, const bool wantsShadow = true)
{
	const ImVec2 points[] = {
		bottom, { bottom.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) },
		{ bottom.x - 0.5f * State.dpiScale, bottom.y }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), bottom.y },

		{ top.x + 0.5f * State.dpiScale, bottom.y }, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), bottom.y },
		{ top.x, bottom.y }, { top.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) },

		{ bottom.x, top.y }, { bottom.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) },
		{ bottom.x - 0.5f * State.dpiScale, top.y }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), top.y },

		top, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), top.y },
		{ top.x, top.y + 0.5f * State.dpiScale }, { top.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) }
	};

	if (wantsShadow) {
		const ImVec4& shadowColor = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(color) & IM_COL32_A_MASK);
		for (size_t i = 0; i < std::size(points); i += 2) {
			RenderLine(points[i] + 0.5f * State.dpiScale, points[i + 1] + 0.5f * State.dpiScale, shadowColor, false);
		}
	}
	for (size_t i = 0; i < std::size(points); i += 2) {
		RenderLine(points[i], points[i + 1], color, false);
	}
}

static void DrawBox(float x, float y, float w, float h, ImVec4 color, float thickness)
{
	RenderLine(ImVec2(x, y), ImVec2(x + w, y), color, thickness);
	RenderLine(ImVec2(x, y), ImVec2(x, y + h), color, thickness);
	RenderLine(ImVec2(x + w, y), ImVec2(x + w, y + h), color, thickness);
	RenderLine(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thickness);
}

static void DrawEntity(EspData& data, const float footOffset, const float headOffset, const float nameOffset = -0.5f, const float widthOffset = 2.f)
{
	Vector3 footpos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), { data.Position.x, data.Position.y + footOffset, data.Position.z }, NULL);
	Vector3 headpos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), { data.Position.x, data.Position.y + headOffset, data.Position.z }, NULL);
	Vector3 namepos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), { data.Position.x, data.Position.y + nameOffset, data.Position.z }, NULL);

	if (footpos.z > 0.f)
	{
		float height = (headpos.y - footpos.y);
		float width = height / widthOffset;

		DrawBox(footpos.x - (width / 2), (float)app::Screen_get_height(NULL) - footpos.y - height, width, height, data.Color, 2.f);
		RenderText(data.Name.c_str(), ImVec2(namepos.x, (float)app::Screen_get_height(NULL) - namepos.y), data.Color);
	}
}

void Esp::Render()
{
	CurrentWindow = ImGui::GetCurrentWindow();

	drawing_t& instance = Esp::GetDrawing();

	// Lock our mutex when we render (this will unlock when it goes out of scope)
	synchronized(instance.m_DrawingMutex) {
		for (auto& it : instance.m_data)
		{
			app::Vector3 pos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), it.Position, NULL);

			if (not IsWithinScreenBounds(pos))
				continue;

			switch (it.Type)
			{
			case EspType::PLAYER:
				DrawEntity(it, -0.25f, 1.75f);
				break;

			case EspType::AZAZEL:
				DrawEntity(it, -0.25f, 2.f);
				break;

			case EspType::CRAWLER:
				DrawEntity(it, -0.25f, 1.5f);
				break;

			case EspType::ITEM:
			case EspType::ANIMAL:
				RenderText(it.Name.substr(8).c_str(), ImVec2(pos.x, (float)app::Screen_get_height(NULL) - pos.y), it.Color);
				break;

			case EspType::KEY:
				RenderText(it.Name.c_str(), ImVec2(pos.x, (float)app::Screen_get_height(NULL) - pos.y), it.Color);
				break;

			case EspType::UNKNOWN:
			default:
				break;
			}
		}
	}
}
