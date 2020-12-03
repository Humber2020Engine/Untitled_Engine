#include "FireBall.h"
#include "../Engine/Graphics/ShaderHandler.h"

FireBall::FireBall(glm::vec2 position_, float angle_) : GameObject(new Sprite(ShaderHandler::GetInstance()->GetShader("basicShader"), "Blue", this)) {

	SetPosition(position_);
	SetRotation(angle_);
	SetScale(glm::vec2(10, 10));
	SetGravity(false);
	SetRigid(false);
}

FireBall::~FireBall()
{

}

void FireBall::Update(const float deltaTime_)
{
	//Apply Const Speed
	ApplyForce(glm::vec2(8.0f, 0.0f));
	GameObject::Update( deltaTime_);
}

void FireBall::CollisionResponse(GameObject* obj)
{
}

