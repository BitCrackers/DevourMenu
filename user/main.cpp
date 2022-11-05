#include "pch-il2cpp.h"
#include "main.h"
#include "il2cpp-init.h"
#include <VersionHelpers.h>
#include "crc32.h"
#include <shellapi.h>
#include <iostream>
#include "game.h"
#include "_hooks.h"
#include "logger.h"
#include "state.hpp"
#include "version.h"
#include "utility.h"
#include <fstream>
#include <sstream>
#include "gitparams.h"

// test autoRelease main ver increment

HMODULE hModule;
HANDLE hUnloadEvent;

std::string GetCRC32(std::filesystem::path filePath) {
	CRC32 crc32;
	char buffer[4096] = { 0 };

	std::ifstream fin(filePath, std::ifstream::binary);

	while (!fin.eof()) {
		fin.read(&buffer[0], 4096);
		auto readSize = fin.gcount();
		crc32.add(&buffer[0], (size_t) readSize);
	}
	//LOG_DEBUG("CRC32 of \"" + filePath.u8string() + "\" is " + crc32.getHash());
	return crc32.getHash();
}

bool GameVersionCheck() {
	auto modulePath = getModulePath(NULL);
	auto gameAssembly = modulePath.parent_path() / "GameAssembly.dll";
	auto steamApi = modulePath.parent_path() / "DEVOUR_Data" / "Plugins" / "x86_64" / "steam_api64.dll";

	if (!IsWindows10OrGreater()) {
		DLog.Error("Version of windows not supported exiting!");
		MessageBox(NULL, L"This version of Windows is not supported!", L"DevourMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	if (!std::filesystem::exists(gameAssembly)) {
		DLog.Error("GameAssembly.dll was not found");
		MessageBox(NULL, L"Unable to locate GameAssembly.dll", L"DevourMenu", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		return false;
	}

	std::string gameAssemblyCRC = GetCRC32(gameAssembly); //We won't use this, but it will log it

	return true;
}

#define ToString(s) stringify(s)
#define stringify(s) #s

#define GAME_STATIC_POINTER(f,c,m) \
	do \
	{ \
		assert(cctor_finished(c##__TypeInfo->_0.klass)); \
		f = &(c##__TypeInfo->static_fields->m); \
		std::ostringstream ss; \
		ss << std::internal << std::setfill('0') << std::hex << std::setw(8) \
		 << stringify(f) << " is 0x" << f << " -> 0x" << *f; \
		LOG_DEBUG(ss.str()); \
	} while (0);

void Run(LPVOID lpParam) {
#if _DEBUG
	new_console();
#endif

	DLog.Create();
	if (!GameVersionCheck()) {
		fclose(stdout);
		FreeConsole();
		FreeLibraryAndExitThread((HMODULE)lpParam, 0);
		return;
	}
	hModule = (HMODULE)lpParam;
	init_il2cpp();
	ScopedThreadAttacher managedThreadAttached;
	{
		std::ostringstream ss;
		ss << "\n\tDevourMenu - " << __DATE__ << " - " << __TIME__ << std::endl; // Log devourmenu info
		ss << "\tBuild: " << _CONFIGURATION_NAME << std::endl;
		ss << "\tCommit: " << GetGitCommit() << " - " << GetGitBranch() << std::endl; // Log git info
		ss << "\tDEVOUR Version: " << getGameVersion() << std::endl; // Log among us info
		LOG_INFO(ss.str());
	}

#if _DEBUG
	#define DO_APP_FUNC(r, n, p, s) if(!n) printf("Unable to locate %s\n", #n)
	#include "il2cpp-functions.h"
	#undef DO_APP_FUNC
#endif

	State.Load();
#if _DEBUG
	hUnloadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
#endif
	DetourInitilization();

#if _DEBUG
	managedThreadAttached.detach();
	DWORD dwWaitResult = WaitForSingleObject(hUnloadEvent, INFINITE);
	if (dwWaitResult != WAIT_OBJECT_0) {
		STREAM_ERROR("Failed to watch unload signal! dwWaitResult = " << dwWaitResult << " Error " << GetLastError());
		return;
	}

	DetourUninitialization();
	fclose(stdout);
	FreeConsole();
	CloseHandle(hUnloadEvent);
	FreeLibraryAndExitThread(hModule, 0);
#endif
}
