#include "SceneManager.h"
#include "TestScene.h"



SceneManager::SceneManager() : GameInterface(), currentScene(nullptr), currentSceneNum(0)
{

}


SceneManager::~SceneManager()
{
	delete currentScene;
	currentScene = nullptr;
}

bool SceneManager::OnCreate()
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0) {
		currentScene = new TestScene();
		if (!currentScene->OnCreate()) {
			Debug::FatalError("Scene has failed on create", "SceneManager.cpp", __LINE__);
			return false;
		}
		return true;
	}
	Debug::FatalError("Engine scene number is not zero", "SceneManager.cpp", __LINE__);
	return false;
}

void SceneManager::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene()) {
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void SceneManager::Draw()
{
	currentScene->Draw();
}

void SceneManager::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene()) {

	case 1:
		
		break;
	default:
		currentScene = new TestScene();
		break;
	}

	if (!currentScene->OnCreate()) {
		Debug::FatalError("Scene has failed on create", "SceneManager.cpp", __LINE__);
		CoreEngine::GetInstance()->Exit();
	}
	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
}
