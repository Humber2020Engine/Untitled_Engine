#include "SceneGraph.h"
#include "../Graphics/ShaderHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<SceneGraph> SceneGraph::sceneGraphInstance = nullptr;

std::map<std::string, GameObject*> SceneGraph::sceneGameObjects = std::map<std::string, GameObject*>();

SceneGraph * SceneGraph::GetInstance()
{
	if (sceneGraphInstance.get() == nullptr) {
		sceneGraphInstance.reset(new SceneGraph);
	}
	return sceneGraphInstance.get();
}

void SceneGraph::AddGameObject(GameObject * go_, std::string name_)
{
	if (sceneGameObjects.find(name_) == sceneGameObjects.end()) {
		go_->SetName(name_);
		sceneGameObjects[name_] = go_;
	}
	else {
		Debug::Warning("Trying to add a GameObject with a name " + name_ +
			" that already exist.", "SceneGraph.cpp", __LINE__);

		bool check = false;
		int loop = 1;
		std::string newName = name_ + std::to_string(loop);
		while(!check){
			if (sceneGameObjects.find(newName) == sceneGameObjects.end()) {
				check = true;
			}
			else {
				loop++;
				newName = name_ + std::to_string(loop);
			}
		}
		go_->SetName(newName);
		sceneGameObjects[newName] = go_;
	}
	CollisionHandler::GetInstance()->AddObject(go_);

}

void SceneGraph::RemoveGameObject(std::string name_)
{
	std::map<std::string, GameObject*>::iterator obj = sceneGameObjects.find(name_);
	int i = 0;
	for (auto g : sceneGameObjects) {
		if (g.first == name_) {
			delete g. second;
			g.second = nullptr;

			sceneGameObjects.erase(obj);

			CollisionHandler::GetInstance()->RemoveObject(i);
			return;
		}
		i++;
	}

	Debug::Error("No game object of that name has been found.", "SceneGraph.cpp", __LINE__);
}

GameObject * SceneGraph::GetGameObject(std::string name_)
{
	if (sceneGameObjects.find(name_) != sceneGameObjects.end()) {
		return sceneGameObjects[name_];
	}
	return nullptr;
}

void SceneGraph::Update(const float deltaTime_)
{
	for (auto go : sceneGameObjects) {
		go.second->Update(deltaTime_);
	}
	CollisionHandler::GetInstance()->AABB();
}

void SceneGraph::Draw(Camera * camera_)
{
	glClearColor(0, 0, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(ShaderHandler::GetInstance()->GetShader("basicShader"));

	std::vector<float> frustum = CoreEngine::GetInstance()->GetCamera()->GetFrustumPlanes();
	for (auto entry : sceneGameObjects) {
		if (CoreEngine::GetInstance()->GetCamera()->FrustumCull(frustum, &entry.second->GetBoundingBox())) {
			entry.second->Draw(camera_);
		}
	}
}

void SceneGraph::OnDestroy()
{
	if (sceneGameObjects.size() > 0) {
		for (auto go : sceneGameObjects) {
			delete go.second;
			go.second = nullptr;
		}
		sceneGameObjects.clear();
	}
}

SceneGraph::SceneGraph()
{
}

SceneGraph::~SceneGraph()
{
	OnDestroy();
}
