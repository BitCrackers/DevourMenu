#include "pch-il2cpp.h"
#include "gui-helpers.hpp"
#include "keybinds.h"
#include "state.hpp"
#include "game.h"
#include "logger.h"
#include "DirectX.h"
#include <DirectX.h>

using namespace ImGui;

bool CustomListBoxPair(const char* label, int* value, const std::vector<std::pair<const char*, const char*>> list, float width, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto leftArrow = "##" + std::string(label) + "Left";
	auto rightArrow = "##" + std::string(label) + "Right";

	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	bool response = BeginCombo(comboLabel.c_str(), (*value >= 0 ? list.at(*value).first : nullptr), ImGuiComboFlags_NoArrowButton | flags);
	if (response) {
		response = false;
		for (size_t i = 0; i < list.size(); i++) {
			bool is_selected = (*value == i);
			if (Selectable(list.at(i).first, is_selected)) {
				*value = (int)i;
				response = true;
			}
			if (is_selected)
				SetItemDefaultFocus();
		}
		EndCombo();
	}

	PopItemWidth();
	SameLine(0, spacing);

	const bool LeftResponse = ArrowButton(leftArrow.c_str(), ImGuiDir_Left);
	if (LeftResponse) {
		*value -= 1;
		if (*value < 0) *value = int(list.size() - 1);
		return LeftResponse;
	}
	SameLine(0, spacing);
	const bool RightResponse = ArrowButton(rightArrow.c_str(), ImGuiDir_Right);
	if (RightResponse) {
		*value += 1;
		if (*value > (int)(list.size() - 1)) *value = 0;
		return RightResponse;
	}
	SameLine(0, spacing);
	ImGui::Text(label);

	return response;
}

bool CustomListBoxInt(const char* label, int* value, const std::vector<const char*> list, float width, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto leftArrow = "##" + std::string(label) + "Left";
	auto rightArrow = "##" + std::string(label) + "Right";

	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	bool response = BeginCombo(comboLabel.c_str(), (*value >= 0 ? list.at(*value) : nullptr), ImGuiComboFlags_NoArrowButton | flags);
	if (response) {
		response = false;
		for (size_t i = 0; i < list.size(); i++) {
			bool is_selected = (*value == i);
			if (Selectable(list.at(i), is_selected)) {
				*value = (int)i;
				response = true;
			}
			if (is_selected)
				SetItemDefaultFocus();
		}
		EndCombo();
	}

	PopItemWidth();
	SameLine(0, spacing);

	const bool LeftResponse = ArrowButton(leftArrow.c_str(), ImGuiDir_Left);
	if (LeftResponse) {
		*value -= 1;
		if (*value < 0) *value = int(list.size() - 1);
		return LeftResponse;
	}
	SameLine(0, spacing);
	const bool RightResponse = ArrowButton(rightArrow.c_str(), ImGuiDir_Right);
	if (RightResponse) {
		*value += 1;
		if (*value > (int)(list.size() - 1)) *value = 0;
		return RightResponse;
	}
	SameLine(0, spacing);
	ImGui::Text(label);

	return response;
}

bool CustomListBoxIntMultiple(const char* label, std::vector<std::pair<const char*, bool>>* list, float width, bool resetButton, ImGuiComboFlags flags) {
	auto comboLabel = "##" + std::string(label);
	auto buttonLabel = "Reset##" + std::string(label);
	ImGuiStyle& style = GetStyle();
	float spacing = style.ItemInnerSpacing.x;
	PushItemWidth(width);
	size_t countSelected = 0;
	for (auto& pair : *list) {
		if (pair.second) {
			countSelected++;
		}
	}
	std::string preview;
	if (countSelected > 0) {
		char buf[32] = { 0 };
		sprintf_s(buf, "%zu item(s) selected", countSelected);
		preview = buf;
	}
	else
		preview = label;
	bool response = BeginCombo(comboLabel.c_str(), preview.c_str(), flags);
	if (response) {
		response = false;
		for (auto& pair : *list) {
			if (strcmp(pair.first, "") == 0) // ignore all entries with empty labels so we can create padding
				continue;
			if (Selectable(pair.first, pair.second)) {
				pair.second ^= 1;
				response = true;
			}
			if (pair.second)
				SetItemDefaultFocus();
		}
		EndCombo();
	}

	PopItemWidth();

	if (resetButton)
	{
		SameLine(0, spacing);
		const bool resetResponse = ImGui::Button(buttonLabel.c_str());
		if (resetResponse) {
			for (auto& pair : *list)
				pair.second = false;
			return resetResponse;
		}
	}
	
	return response;
}

bool SteppedSliderFloat(const char* label, float* v, float v_min, float v_max, float v_step, const char* format = "%.3f", ImGuiSliderFlags flags = 0) {
	char text_buf[64] = {};
	ImFormatString(text_buf, IM_ARRAYSIZE(text_buf), format, *v);

	const int stepCount = int((v_max - v_min) / v_step);
	int v_i = int((*v - v_min) / v_step);
	const bool valueChanged = SliderInt(label, &v_i, 0, stepCount, text_buf);

	*v = v_min + float(v_i) * v_step;
	return valueChanged;
}

bool HotKey(uint8_t& key)
{
	ImGui::Text("[ %s ]", KeyBinds::ToString(key));

	if (!IsItemHovered())
		return false;

	SetTooltip("Press any key to change the keybind, ESC to reset");
	for (uint8_t vKey : KeyBinds::GetValidKeys()) {
		if (KeyBinds::IsKeyDown(vKey)) {
			key = (vKey != VK_ESCAPE ? vKey : 0x00);
			return true;
		}
	}

	return false;
}
