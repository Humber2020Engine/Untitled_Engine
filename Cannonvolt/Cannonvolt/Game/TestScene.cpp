#include "TestScene.h"



TestScene::TestScene() : Scene() {

}

TestScene::~TestScene() {

}

bool TestScene::OnCreate()
{
	Debug::Info("Creating Game Scene", "GameScene.cpp", __LINE__);

	CoreEngine::GetInstance()->SetCamera(new Camera);
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	character.OnCreate();
	character.SetPosition(glm::vec2(200.0f, 200.0f));
	character.SetScale(glm::vec2(0.10f, 0.10f));

	controller.Init(&character);
	gameManger.OnCreate(&character);

	SceneGraph::GetInstance()->AddGameObject(&character, "Mario");

	Platform* grass;
	for (int i = 0; i < 8; i++) {
		grass = new Platform();
		grass->OnCreate();
		grass->SetPosition(glm::vec2(50.0f * i, 0.0f));
		platforms.push_back(grass);
		SceneGraph::GetInstance()->AddGameObject(platforms[i]);
		grass = nullptr;
	}

	spike.OnCreate(glm::vec2(40, 40));
	SceneGraph::GetInstance()->AddGameObject(&spike, "Spike");

	return true;
}

void TestScene::Update(const float deltaTime_)
{
	controller.Update(deltaTime_);
	gameManger.Update();
	SceneGraph::GetInstance()->Update(deltaTime_);
}

void TestScene::Draw()
{
	SceneGraph::GetInstance()->Draw(CoreEngine::GetInstance()->GetCamera());
}
