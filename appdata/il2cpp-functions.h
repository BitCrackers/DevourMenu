using namespace app;

DO_APP_FUNC(Type*, Type_GetType, (String* typeName, MethodInfo* method), "mscorlib, System.Type System.Type::GetType(System.String)");

DO_APP_FUNC(GameObject*, Component_get_gameObject, (Component_1* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.GameObject UnityEngine.Component::get_gameObject()");
DO_APP_FUNC(Transform*, Component_get_transform, (Component_1* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Component::get_transform()");

DO_APP_FUNC(void, Object_DestroyImmediate, (Object_1* obj, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Object::DestroyImmediate(UnityEngine.Object)");
DO_APP_FUNC(Component_1*, Component_GetComponent, (Component_1* __this, Type* type, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Component UnityEngine.Component::GetComponent(System.Type)");

DO_APP_FUNC(Transform*, GameObject_get_transform, (GameObject* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.GameObject::get_transform()");
DO_APP_FUNC(Transform*, Transform_GetRoot, (Transform* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Transform::GetRoot()");
DO_APP_FUNC(String*, Component_get_tag, (Component_1* __this, MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.Component::get_tag()");
DO_APP_FUNC(void, GameObject_set_layer, (GameObject* __this, int32_t value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.GameObject::set_layer(System.Int32)");
DO_APP_FUNC(int32_t, GameObject_get_layer, (GameObject* __this, MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.GameObject::get_layer()");
DO_APP_FUNC(int32_t, LayerMask_NameToLayer, (String* layerName, MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.LayerMask::NameToLayer(System.String)");
DO_APP_FUNC(Object_1*, Object_1_FindObjectOfType, (Type* type, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Object UnityEngine.Object::FindObjectOfType(System.Type)");
DO_APP_FUNC(Object_1__Array*, Object_1_FindObjectsOfType, (Type* type, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Object[] UnityEngine.Object::FindObjectsOfType(System.Type)");
DO_APP_FUNC(String*, Scene_GetNameInternal, (int32_t sceneHandle, MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.SceneManagement.Scene::GetNameInternal(System.Int32)");
DO_APP_FUNC(void, SceneManager_Internal_ActiveSceneChanged, (Scene previousActiveScene, Scene newActiveScene, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.SceneManagement.SceneManager::Internal_ActiveSceneChanged(UnityEngine.SceneManagement.Scene, UnityEngine.SceneManagement.Scene)");
DO_APP_FUNC(Vector3, Transform_get_position, (Transform* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Transform::get_position()");
DO_APP_FUNC(void, Transform_set_position, (Transform* __this, Vector3 value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Transform::set_position(UnityEngine.Vector3)");
DO_APP_FUNC(float, Vector2_Distance, (Vector2 a, Vector2 b, MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Vector2::Distance(UnityEngine.Vector2, UnityEngine.Vector2)");
DO_APP_FUNC(bool, Collider2D_OverlapPoint, (Collider2D* __this, Vector2 point, MethodInfo* method), "UnityEngine.Physics2DModule, System.Boolean UnityEngine.Collider2D::OverlapPoint(UnityEngine.Vector2)");
DO_APP_FUNC(String*, Application_get_version, (MethodInfo* method), "UnityEngine.CoreModule, System.String UnityEngine.Application::get_version()");
DO_APP_FUNC(void, Renderer_set_enabled, (Renderer* __this, bool value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Renderer::set_enabled(System.Boolean)");
DO_APP_FUNC(int32_t, Camera_GetAllCameras, (Camera__Array* cameras, MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Camera::GetAllCameras(UnityEngine.Camera[])");
DO_APP_FUNC(int32_t, Camera_get_allCamerasCount, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Camera::get_allCamerasCount()");
DO_APP_FUNC(Camera*, Camera_get_main, (MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Camera UnityEngine.Camera::get_main()");
DO_APP_FUNC(void, Camera_set_orthographicSize, (Camera* __this, float value, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Camera::set_orthographicSize(System.Single)");
DO_APP_FUNC(float, Camera_get_orthographicSize, (Camera* __this, MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Camera::get_orthographicSize()");
DO_APP_FUNC(Color, SpriteRenderer_get_color, (SpriteRenderer* __this, MethodInfo* method), "UnityEngine.CoreModule, UnityEngine.Color UnityEngine.SpriteRenderer::get_color()");
DO_APP_FUNC(float, Time_get_fixedDeltaTime, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_fixedDeltaTime()");
DO_APP_FUNC(float, Time_get_realtimeSinceStartup, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_realtimeSinceStartup()");
DO_APP_FUNC(float, Time_get_time, (MethodInfo* method), "UnityEngine.CoreModule, System.Single UnityEngine.Time::get_time()");

DO_APP_FUNC(int32_t, Screen_get_width, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Screen::get_width()");
DO_APP_FUNC(int32_t, Screen_get_height, (MethodInfo* method), "UnityEngine.CoreModule, System.Int32 UnityEngine.Screen::get_height()");
DO_APP_FUNC(bool, Screen_get_fullScreen, (MethodInfo* method), "UnityEngine.CoreModule, System.Boolean UnityEngine.Screen::get_fullScreen()");

DO_APP_FUNC(void, Debug_Log, (Object* message, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::Log(System.Object)");
DO_APP_FUNC(void, Debug_LogError, (Object* message, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::LogError(System.Object)");
DO_APP_FUNC(void, Debug_LogException, (Exception* exception, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::LogException(System.Exception)");
DO_APP_FUNC(void, Debug_LogWarning, (Object* message, MethodInfo* method), "UnityEngine.CoreModule, System.Void UnityEngine.Debug::LogWarning(System.Object)");
DO_APP_FUNC(String*, Object_ToString, (Object* __this, MethodInfo* method), "mscorlib, System.String System.Object::ToString()");

DO_APP_FUNC(bool, Object_1_op_Implicit, (Object_1* exists, MethodInfo* method), "UnityEngine.CoreModule, System.Boolean UnityEngine.Object::op_Implicit(UnityEngine.Object)");

// DEVOUR
DO_APP_FUNC(void, NolanBehaviour_StartCarry, (NolanBehaviour* __this, String* objectName, MethodInfo* method), "Assembly-CSharp, System.Void NolanBehaviour::StartCarry(System.String)");
DO_APP_FUNC(void, NolanBehaviour_PlopObject, (NolanBehaviour* __this, MethodInfo* method), "Assembly-CSharp, System.Void NolanBehaviour::PlopObject()");

DO_APP_FUNC(AchievementHelpers*, AchievementHelpers_get_singleton, (MethodInfo* method), "Assembly-CSharp, AchievementHelpers AchievementHelpers::get_singleton()");
DO_APP_FUNC(void, AchievementHelpers_Unlock, (AchievementHelpers* __this, String* achievementName, bool skipStoreStats, MethodInfo* method), "Assembly-CSharp, System.Void AchievementHelpers::Unlock(System.String, System.Boolean)");
DO_APP_FUNC(bool, AchievementHelpers_ShowHardModeUnlocked, (AchievementHelpers* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean AchievementHelpers::ShowHardModeUnlocked()");
DO_APP_FUNC(bool, AchievementHelpers_ShowHardRobeUnlocked, (AchievementHelpers* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean AchievementHelpers::ShowHardRobeUnlocked()");
DO_APP_FUNC(bool, AchievementHelpers_ShowNightmareModeUnlocked, (AchievementHelpers* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean AchievementHelpers::ShowNightmareModeUnlocked()");

DO_APP_FUNC(UIOutfitSelectionType*, Menu_2_SetupOutfit, (MenuM_2* __this, CharacterOutfit* outfit, MethodInfo* method), "Assembly-CSharp, UIOutfitSelectionType Horror.Menu::SetupOutfit(CharacterOutfit)");
DO_APP_FUNC(UIPerkSelectionType*, Menu_2_SetupPerk, (MenuM_2* __this, CharacterPerk* perk, MethodInfo* method), "Assembly-CSharp, UIPerkSelectionType Horror.Menu::SetupPerk(CharacterPerk)");
DO_APP_FUNC(UIFlashlightSelectionType*, Menu_2_SetupFlashlight, (MenuM_2* __this, CharacterFlashlight* flashlight, MethodInfo* method), "Assembly-CSharp, UIFlashlightSelectionType Horror.Menu::SetupFlashlight(CharacterFlashlight)");
DO_APP_FUNC(UIPetSelectionType*, Menu_2_SetupPet, (MenuM_2* __this, CharacterPet* pet, MethodInfo* method), "Assembly-CSharp, UIPetSelectionType Horror.Menu::SetupPet(CharacterPet)");

DO_APP_FUNC(bool, OptionsHelpers_IsCharacterUnlocked, (OptionsHelpers* __this, String* prefab, MethodInfo* method), "Assembly-CSharp, System.Boolean OptionsHelpers::IsCharacterUnlocked(System.String)");
DO_APP_FUNC(bool, OptionsHelpers_IsRobeUnlocked, (OptionsHelpers* __this, String* robe, MethodInfo* method), "Assembly-CSharp, System.Boolean OptionsHelpers::IsRobeUnlocked(System.String)");

DO_APP_FUNC(bool, SurvivalLobbyController_CanReady, (SurvivalLobbyController* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean SurvivalLobbyController::CanReady()");
DO_APP_FUNC(bool, SurvivalLobbyController_PlayableCharacterSelected, (SurvivalLobbyController* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean SurvivalLobbyController::PlayableCharacterSelected()");
DO_APP_FUNC(bool, SurvivalLobbyController_UnlockedCharacterSelected, (SurvivalLobbyController* __this, MethodInfo* method), "Assembly-CSharp, System.Boolean SurvivalLobbyController::UnlockedCharacterSelected()");

DO_APP_FUNC(bool, LockedInteractable_CanInteract, (LockedInteractable* __this, GameObject* character, MethodInfo* method), "Assembly-CSharp, System.Boolean LockedInteractable::CanInteract(UnityEngine.GameObject)");

DO_APP_FUNC(void, PrefabId__ctor, (PrefabId__Boxed* __this, int32_t value, MethodInfo* method), "bolt, System.Void Photon.Bolt.PrefabId::.ctor(System.Int32)");
DO_APP_FUNC(String*, PrefabId_ToString, (PrefabId__Boxed* __this, MethodInfo* method), "bolt, System.String Photon.Bolt.PrefabId::ToString()");