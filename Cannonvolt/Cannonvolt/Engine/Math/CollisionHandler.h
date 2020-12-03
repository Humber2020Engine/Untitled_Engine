#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "../Rendering/2D/GameObject.h"
//#include "CollisionDetection.h"

class CollisionHandler
{
public:
	CollisionHandler(const CollisionHandler&) = delete;
	CollisionHandler(CollisionHandler&&) = delete;
	CollisionHandler& operator =(const CollisionHandler&) = delete;
	CollisionHandler& operator =(CollisionHandler&&) = delete;

	static CollisionHandler* GetInstance();
	void OnDestroy();
	void AddObject(GameObject* go_);
	void RemoveObject(int location_);
	void AABB();

private:
	CollisionHandler();
	~CollisionHandler();

	static std::unique_ptr<CollisionHandler> collisionInstance;
	friend std::default_delete<CollisionHandler>;

	
	static std::vector<GameObject*> prevCollisions;

	std::vector<GameObject*> gameObjects;

};
#endif // !COLLISIONHANDLER_H
