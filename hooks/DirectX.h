#pragma once
#include "resources.h"
#include "directx11.h"
#include <vector>
#include <unordered_map>
#include <imgui/imgui.h>

struct MapTexture {
	D3D11Image mapImage;
	float x_offset;
	float y_offset;
	float scale;
};

extern D3D_PRESENT_FUNCTION oPresent;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

namespace DirectX {
	extern HWND window;
	extern HANDLE hRenderSemaphore;
	void Shutdown();
	ImVec2 GetWindowSize();
}
