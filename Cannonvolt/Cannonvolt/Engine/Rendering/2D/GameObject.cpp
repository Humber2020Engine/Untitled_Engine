#include "GameObject.h"

GameObject::GameObject(Sprite* sprite_, glm::vec2 position_)
{
	sprite = sprite_;
	position = position_;
	rotation = 0;
	scale = glm::vec2(1.0f,1.0);
	tag = "GameObject";
	name = "GameObject";
	hit = false;

	if (sprite) {
		box = sprite->GetBoundingBox();
		box.pos = position;
	}

	physics.OnCreate(this);
}

GameObject::~GameObject()
{
	delete sprite;
	sprite = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	physics.Update(deltaTime_);
}


void GameObject::Draw(Camera* camera_)
{
	if (sprite) {
		sprite->Draw(camera_);
	}
}

glm::vec2 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetRotation() const
{
	return rotation;
}

glm::vec2 GameObject::GetScale() const
{
	return scale;
}

BoundingBox GameObject::GetBoundingBox() const
{
	return box;
}

std::string GameObject::GetTag() const
{
	return tag;
}

std::string GameObject::GetName() const
{
	return name;
}

bool GameObject::GetHit() const
{
	return hit;
}

Sprite* GameObject::GetSprite() const
{
	return sprite;
}

//TODO: do this after the question
void GameObject::SetPosition(glm::vec2 position_)
{
	position = position_;
	if (sprite) {
		box.pos = position_;
	}
}

void GameObject::SetRotation(float rotation_)
{
	rotation = rotation_;
}

void GameObject::SetScale(glm::vec2 scale_)
{
	scale = scale_;
	if (sprite) {
		sprite->SetScale(scale);
		box.dimentions = sprite->GetScale();
	}
}

void GameObject::SetTag(std::string tag_)
{
	tag = tag_;
}

void GameObject::SetHit(bool hit_, int buttonType_)
{
	hit = hit_;
}

void GameObject::SetName(std::string name_)
{
	name = name_;
}

void GameObject::Translate(glm::vec2 trans_)
{
	SetPosition(position + trans_);
}

void GameObject::CollisionResponse(GameObject* obj)
{
	physics.RigidbodyCollision(obj);
}

void GameObject::ApplyForce(glm::vec2 force_, float rotation_)
{
	physics.ApplyForce(force_, rotation_);
}

bool GameObject::IsStatic() const
{
	return physics.GetStatic();
}

void GameObject::SetStatic(bool static_)
{
	return physics.SetStatic(static_);
}

void GameObject::SetGravity(bool grav)
{
	physics.ApplyGravity(grav);
}

bool GameObject::IsRigid() const
{
	return physics.GetRigid();
}

void GameObject::SetRigid(bool rig)
{
	physics.SetRigidBody(rig);
}

void GameObject::SetDrag(bool drag)
{
	physics.ApplyDrag(drag);
}

void GameObject::SetSpeedLimit(glm::vec2 limit)
{
	physics.SetSpeedLimit(limit);
}

void GameObject::Flip(bool invert_)
{
	sprite->SetFlip(invert_);
}

bool GameObject::IsFliped() const
{
	return sprite->GetFlip();
}
