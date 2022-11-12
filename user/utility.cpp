#include "pch-il2cpp.h"
#include "utility.h"
#include "state.hpp"
#include "game.h"
#include "gitparams.h"
#include "logger.h"
#include "profiler.h"
#include <random>

int randi(int lo, int hi) {
	int n = hi - lo + 1;
	int i = rand() % n;
	if (i < 0) i = -i;
	return lo + i;
}

std::filesystem::path getModulePath(HMODULE hModule) {
	TCHAR buff[MAX_PATH];
	GetModuleFileName(hModule, buff, MAX_PATH);
	return std::filesystem::path(buff);
}

std::string getGameVersion() {
	if (app::Application_get_version != nullptr)
		return convert_from_string(app::Application_get_version(NULL));
	else
		return "unavailable";
}

Vector2 Rotate(const Vector2& vec, float degrees)
{
	float f = 0.017453292f * degrees;
	float num = cos(f);
	float num2 = sin(f);
	return { vec.x * num - num2 * vec.y, vec.x * num2 + num * vec.y };
}

bool Equals(const Vector2& vec1, const Vector2& vec2) {
	return vec1.x == vec2.x && vec1.y == vec2.y;
}

std::string ToString(Object* object) {
	std::string type = convert_from_string(Object_ToString(object, NULL));
	if (type == "System.String") {
		return convert_from_string((String*)object);
	}
	return type;
}

#define ADD_QUOTES_HELPER(s) #s
#define ADD_QUOTES(s) ADD_QUOTES_HELPER(s)

std::string GetGitCommit()
{
#ifdef GIT_CUR_COMMIT
	return ADD_QUOTES(GIT_CUR_COMMIT);
#endif
	return "unavailable";
}

std::string GetGitBranch()
{
#ifdef GIT_BRANCH
	return ADD_QUOTES(GIT_BRANCH);
#endif
	return "unavailable";
}

float GetDistanceBetweenPoints_Unity(const Vector2& p1, const Vector2& p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

float GetDistanceBetweenPoints_ImGui(const ImVec2& p1, const ImVec2& p2)
{
	float dx = p1.x - p2.x, dy = p1.y - p2.y;
	return sqrtf(dx * dx + dy * dy);
}

bool Object_1_IsNotNull(app::Object_1* obj)
{
	return app::Object_1_op_Implicit(obj, nullptr);
}

bool Object_1_IsNull(app::Object_1* obj)
{
	return !Object_1_IsNotNull(obj);
}

NolanBehaviour* GetLocalPlayer()
{
	for (auto p : GetAllPlayers())
	{
		if (p->fields._._._._._entity->fields._entity->fields.IsOwner)
			return p;
	}
	return nullptr;
}

il2cpp::List<List_1_NolanBehaviour_> GetAllPlayers()
{
	return (*Game::pInGameHelpers)->fields.m_Survival->fields.m_PlayerNolanBehaviours;
}

il2cpp::Array<DoorBehaviour__Array> GetAllDoors()
{
	return (*Game::pInGameHelpers)->fields.m_Survival->fields.doorBehaviours;
}

bool IsOwner(NolanBehaviour* player)
{
	return player->fields._._._._._entity->fields._entity->fields.IsOwner;
}

bool IsInGame()
{
	return (*Game::pOptionsHelpers)->fields.inGame;
}

//TODO: FIX THIS
std::string GetPrefabName(int32_t prefabId)
{
	PrefabId__Boxed* cPrefabId = (PrefabId__Boxed*)il2cpp_object_new((Il2CppClass*)PrefabId__TypeInfo);
	PrefabId__ctor(cPrefabId, prefabId, NULL);
	return convert_from_string(PrefabId_ToString(cPrefabId, NULL));
}