#pragma once
#include "directx11.h"
#include <vector>
#include <unordered_map>
#include <imgui/imgui.h>

extern D3D_PRESENT_FUNCTION oPresent;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

namespace DirectX {
	extern HWND window;
	extern HANDLE hRenderSemaphore;
	void Shutdown();
	ImVec2 GetWindowSize();
}
