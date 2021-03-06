#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "../Engine/Core/CoreEngine.h"

class SceneManager : public GameInterface
{
public:
	SceneManager();
	virtual ~SceneManager();
	virtual bool OnCreate() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Draw() override;

private:
	Scene* currentScene;
	int currentSceneNum;
	void BuildScene();
};
#endif // !SCENEMANAGER_H