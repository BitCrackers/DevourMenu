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

void Esp::Render()
{
	CurrentWindow = ImGui::GetCurrentWindow();

	drawing_t& instance = Esp::GetDrawing();

	// Lock our mutex when we render (this will unlock when it goes out of scope)
	synchronized(instance.m_DrawingMutex) {

		// for each player
		il2cpp::List playerList = (*Game::pInGameHelpers)->fields.m_Survival->fields.m_PlayerNolanBehaviours;
		for (auto& player : playerList)
		{
			Vector3 playerPos = app::Transform_get_position(app::Component_get_transform((Component_1*)player, NULL), NULL);
			Vector3 playerFootPos; playerFootPos.x = playerPos.x; playerFootPos.z = playerPos.z; playerFootPos.y = playerPos.y - 0.25f;
			Vector3 playerHeadPos; playerHeadPos.x = playerPos.x; playerHeadPos.z = playerPos.z; playerHeadPos.y = playerPos.y + 1.75f;

			Vector3 w2s_footpos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), playerFootPos, NULL);
			Vector3 w2s_headpos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), playerHeadPos, NULL);

			if (w2s_footpos.z > 0.f)
			{
				float height = (w2s_headpos.y - w2s_footpos.y);
				float widthOffset = 2.f;
				float width = height / widthOffset;

				DrawBox(w2s_footpos.x - (width / 2), (float)app::Screen_get_height(NULL) - w2s_footpos.y - height, width, height, ImVec4(1.0f, 1.0f, 1.0f, 1.0f), 2.f);
			}
		}

		// for each item
		for (auto item : Game::s_SurvivalInteractables)
		{
			Vector3 itemPos = app::Transform_get_position(app::Component_get_transform((Component_1*)item, NULL), NULL);

			Vector3 w2sItemPos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), itemPos, NULL);

			if (w2sItemPos.z > 0.f)
				RenderText(convert_from_string(((SurvivalInteractable*)item)->fields.prefabName).c_str(), ImVec2(w2sItemPos.x, (float)app::Screen_get_height(NULL) - w2sItemPos.y), ImVec4(1.f, 1.f, 1.f, 1.f));
		}

		// for each key
		for (auto key : Game::s_KeyInteractables)
		{
			Vector3 keyPos = app::Transform_get_position(app::Component_get_transform((Component_1*)key, NULL), NULL);

			Vector3 w2sKeyPos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), keyPos, NULL);

			if (w2sKeyPos.z > 0.f)
				RenderText(convert_from_string(app::KeyBehaviour_GetKeyName(((KeyInteractable*)key)->fields.keyBehaviour, NULL)).c_str(), ImVec2(w2sKeyPos.x, (float)app::Screen_get_height(NULL) - w2sKeyPos.y), ImVec4(0.15f, 0.97f, 0.99f, 1.f));
		}

		// THIS CRASHES WHEN GOATS LEAVE CAGE
		// for each goat
		//for (auto goat : Game::s_GoatInteractables)
		//{
		//	Vector3 goatPos = app::Transform_get_position(app::Component_get_transform((Component_1*)goat, NULL), NULL);

		//	Vector3 w2sGoatPos = app::Camera_WorldToScreenPoint(app::Camera_get_main(NULL), goatPos, NULL);

		//	if (w2sGoatPos.z > 0.f)
		//		RenderText(convert_from_string(((GoatInteractable*)goat)->fields.prefabName).c_str(), ImVec2(w2sGoatPos.x, (float)app::Screen_get_height(NULL) - w2sGoatPos.y), ImVec4(0.f, 1.f, 0.f, 1.0f));
		//}
	}
}
