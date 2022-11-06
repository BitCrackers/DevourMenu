#pragma once
#include <vector>
#include <imgui/imgui.h>
#include <filesystem>
#include "game.h"

#define UNIQUE_NAME(prefix)	_CONCAT(prefix ## _, __COUNTER__) ## _CONCAT(at, __LINE__)

#define _synchronized(lock, name, mtx)	if (lock name(mtx); true)
#define synchronized_read(smtx)	_synchronized(std::shared_lock<decltype(smtx)>, UNIQUE_NAME(rdLock), smtx)
#define synchronized_write(mtx)	_synchronized(std::unique_lock<decltype(mtx)>, UNIQUE_NAME(lock), mtx)
/*
	it mimics the behaviour of the Java construct
	"synchronized(this) { }"
*/
#define synchronized(mtx)	synchronized_write(mtx)
/*
	to secure a code-block, use the following syntax:
	"{ SYNCHRONIZED(mutex); <commands> }"
*/
#define SYNCHRONIZED(mtx)	std::scoped_lock UNIQUE_NAME(lock)(mtx)

int randi(int lo, int hi);
std::filesystem::path getModulePath(HMODULE hModule);
std::string getGameVersion();

// TO-DO:
// some C++ wizardry to allow overloading on pointer types w/ different base type (then we can rename both to just GetEventPlayer)
bool Equals(const Vector2& vec1, const Vector2& vec2);
std::string ToString(Object* object);
std::string GetGitCommit();
std::string GetGitBranch();
float GetDistanceBetweenPoints_Unity(const Vector2& p1, const Vector2& p2);
float GetDistanceBetweenPoints_ImGui(const ImVec2& p1, const ImVec2& p2);

bool Object_1_IsNotNull(app::Object_1* unity_object);
bool Object_1_IsNull(app::Object_1* unity_object);

il2cpp::List<List_1_NolanBehaviour_> GetAllPlayers();
il2cpp::Array<DoorBehaviour__Array> GetAllDoors();
bool IsOwner(NolanBehaviour * player);
bool IsInGame();