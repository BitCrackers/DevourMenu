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

	extern Scene DontSaveOnLoadScene;

	extern void GetGameData();
}