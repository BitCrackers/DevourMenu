#include "pch-il2cpp.h"
#include "game.h"
#include "SignatureScan.hpp"

namespace Game {
	SessionHelpers** pSessionHelpers = nullptr;
	AchievementHelpers** pAchievementHelpers = nullptr;
	InGameHelpers** pInGameHelpers = nullptr;
	OptionsHelpers** pOptionsHelpers = nullptr;
	RankHelpers** pRankHelpers = nullptr;
	SaveHelpers** pSaveHelpers = nullptr;

	Scene DontSaveOnLoadScene = { 0 };

	void GetGameData()
	{
		while (not (*Game::pOptionsHelpers)) { /* wait for static pointer to be available */ }
		DontSaveOnLoadScene = app::GameObject_get_scene((GameObject*)(*Game::pOptionsHelpers), NULL);
		
	}
}