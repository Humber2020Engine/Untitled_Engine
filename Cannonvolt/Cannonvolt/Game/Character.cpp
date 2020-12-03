#include "Character.h"
#include "../Engine/Graphics/ShaderHandler.h"
#include "../Engine/Rendering/SceneGraph.h"
#include "FireBall.h"

std::map<std::string, bool> Character::modules = std::map<std::string, bool>();

Character::Character() : GameObject(new Sprite(ShaderHandler::GetInstance()->GetShader("basicShader"),"Mario", this)) {


}

Character::~Character()
{

}

bool Character::OnCreate()
{
	SetTag("Mario");
	SetGravity(true);
	SetRigid(true);
	SetDrag(true);
	return true;
}

void Character::Update(const float deltaTime_)
{
	if (modules["Flight"]) {
		ApplyForce(glm::vec2(80.0f, 0.0f));
	}
	GameObject::Update(deltaTime_);
}

bool Character::IsDead()
{
	return dead;
}

void Character::Kill()
{
	dead = true;
}

void Character::LoadMods()
{
	modules["Movement"] = false;
	modules["Jump"] = false;
	modules["Shoot"] = false;
	modules["Flight"] = false;
}

bool Character::GetMod(std::string name_)
{
	return modules[name_];
}

void Character::SetMod(std::string name_, bool state_)
{
	modules[name_] = state_;
}

//TODO: math is wrong for rotation.
void Character::Shot()
{
	SceneGraph::GetInstance()->AddGameObject(new FireBall(GetPosition(), GetRotation() + IsFliped() ? 180 : 0),"FireBall");
}

void Character::CollisionResponse(GameObject* obj)
{
	GameObject::CollisionResponse(obj);
}