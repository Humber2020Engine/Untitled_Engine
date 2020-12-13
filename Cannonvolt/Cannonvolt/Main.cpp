#include "Engine/Core/CoreEngine.h"
#include "Game/SceneManager.h"
#include "Engine/Modules/Platformer.h"
#include "Engine/Modules/Flight.h"

int main(int argc, char* argv[]) {
	//Set game interface here 
	CoreEngine::GetInstance()->SetGameInterface(new SceneManager);

	std::vector<Modular_Base*> mods;
	mods.reserve(3);
	//mods.push_back(new Platformer());
	mods.push_back(new Flight());

	if (!CoreEngine::GetInstance()->OnCreate("Game211 Midstone", 800, 600, mods)) {
		return 0;
	}

	CoreEngine::GetInstance()->Run();

	return 0;
}