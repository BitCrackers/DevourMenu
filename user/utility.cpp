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
	std::string type = convert_from_string(app::Object_ToString(object, NULL));
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

std::string GetActiveSceneName()
{
	auto activeScene = app::SceneManager_GetActiveScene(NULL);
	auto activeSceneBoxed = (Scene__Boxed*)il2cpp_value_box((Il2CppClass*)app::Scene__TypeInfo, &activeScene);

	return convert_from_string(app::Scene_get_name(activeSceneBoxed, NULL));
}

std::vector<Scene> GetAllScenes()
{
	std::vector<Scene> scenes;
	auto sceneCount = app::SceneManager_get_sceneCount(NULL);

	if (sceneCount == 0)
		return scenes;

	for (int i = 0; i < sceneCount; i++)
	{
		scenes.emplace_back(app::SceneManager_GetSceneAt(i, NULL));
	}

	return scenes;
}

il2cpp::Array<GameObject__Array> GetGameObjectsInActiveScene()
{
	auto activeScene = app::SceneManager_GetActiveScene(NULL);
	auto activeSceneBoxed = (Scene__Boxed*)il2cpp_value_box((Il2CppClass*)app::Scene__TypeInfo, &activeScene);

	return app::Scene_GetRootGameObjects(activeSceneBoxed, NULL);
}

il2cpp::Array<GameObject__Array> GetGameObjectsInSceneAt(int32_t index)
{
	if (index < 0 || index >= app::SceneManager_get_sceneCount(NULL))
		return nullptr;

	auto scene = app::SceneManager_GetSceneAt(index, NULL);
	auto sceneBoxed = (Scene__Boxed*)il2cpp_value_box((Il2CppClass*)app::Scene__TypeInfo, &scene);

	return app::Scene_GetRootGameObjects(sceneBoxed, NULL);
}

std::vector<GameObject*> GetGameObjectsInAllScenes()
{
	std::vector<GameObject*> vGameObjects;
	auto scenes = GetAllScenes();

	for (auto scene : scenes)
	{
		auto sceneBoxed = (Scene__Boxed*)il2cpp_value_box((Il2CppClass*)app::Scene__TypeInfo, &scene);
		il2cpp::Array gObjects = app::Scene_GetRootGameObjects(sceneBoxed, NULL);
		for (auto object : gObjects)
		{
			vGameObjects.emplace_back(object);
		}
	}

	return vGameObjects;
}

il2cpp::Array<Object_1__Array> GetGameObjectsOfType(const char* assemblyName, const char* className)
{
	auto type = app::Type_GetType_2(convert_to_string(std::string(className) + std::string(", ") + std::string(assemblyName)), NULL);
	return app::Object_1_FindObjectsOfType(type, NULL);
}
