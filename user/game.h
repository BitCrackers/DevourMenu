#pragma once

using namespace app;

namespace Game {
	constexpr size_t MAX_PLAYERS = 4;
	
	extern SessionHelpers** pSessionHelpers;
	extern AchievementHelpers** pAchievementHelpers;
	extern InGameHelpers** pInGameHelpers;
	extern OptionsHelpers** pOptionsHelpers;
	extern RankHelpers** pRankHelpers;
	extern SaveHelpers** pSaveHelpers;

	extern il2cpp::Array<Object_1__Array> s_SurvivalInteractables;
	extern il2cpp::Array<Object_1__Array> s_KeyInteractables;
	extern il2cpp::Array<Object_1__Array> s_GoatInteractables;
}