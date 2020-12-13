#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();

CollisionHandler::CollisionHandler()
{
	prevCollisions.reserve(10);
}


CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler * CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr) {
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnDestroy()
{
	for (auto prev : prevCollisions) {
		prev = nullptr;
	}
	prevCollisions.clear();
}

void CollisionHandler::AddObject(GameObject * go_)
{
	gameObjects.push_back(go_);
}

void CollisionHandler::RemoveObject(int location_) {
	gameObjects.erase(gameObjects.begin() + location_);
}

void CollisionHandler::AABB()
{
	//Idea is that it will loop over every game object but will not check itself or any checks that have already happened.
	//this is will save time by preventing re checks, though the question of double checking effects may be something
	//to consider for more advanced collision idea's.

	for (size_t i = 0; i < gameObjects.size(); i++) {
		if (!gameObjects[i]->IsStatic() && gameObjects[i]->IsRigid()) {
			for (size_t j = i + 1; j < gameObjects.size(); j++) {
				if (gameObjects[i]->GetBoundingBox().Intersects(&gameObjects[j]->GetBoundingBox()) && gameObjects[j]->IsRigid()) {
					gameObjects[i]->CollisionResponse(gameObjects[j]);
				}
			}
		}
	}
}
