#include "Physics.h"
#include "../Rendering/2D/GameObject.h"

#define Gravity glm::vec2(0.0f, -9.8f)

Physics::Physics() : velocity(glm::vec2(0)), acceleration(glm::vec2(0)), parent(nullptr), isStatic(false), 
isRigid(false), gravity(0), applyDrag(false), speedCap(glm::vec2(60))
{

}

Physics::~Physics() {
	parent = nullptr;
}

void Physics::OnCreate(GameObject* parent_) {
	parent = parent_;
}

void Physics::Update(const float deltaTime)
{
	if (!isStatic) {
		//Velocity Cap (Prevents the GameObject from moveing too fast in any direction.
		//Would like a more natural version of this so as to decrease run cost. perhaps a opposing force relative
		//To velocity would work?
		if (velocity.x > speedCap.x) { velocity.x = speedCap.x; }
		else if (velocity.x < -speedCap.x) { velocity.x = -speedCap.x; }

		if (velocity.y > speedCap.y) { velocity.y = speedCap.y; }
		else if (velocity.y < -speedCap.y) { velocity.y = -speedCap.y; }

		parent->Translate(velocity * deltaTime + (0.5f * acceleration * std::powf(deltaTime, 2)));

		if (velocity.y > -35.0f) { acceleration = gravity + acceleration; }
		velocity += acceleration * deltaTime;
		acceleration = glm::vec2(0);

		if (applyDrag) { Drag(deltaTime); }

		std::string blank = "";
		blank.append(std::to_string(velocity.x) + " " + std::to_string(velocity.y) + "\n");

		printf(blank.c_str());
	}
}

void Physics::ApplyForce(glm::vec2 force_, float rotation_)
{
	SetAcceleration(glm::mat2(glm::cos(glm::radians(rotation_)), -glm::sin(glm::radians(rotation_)),
		glm::sin(glm::radians(rotation_)), glm::cos(glm::radians(rotation_))) * force_);

}
void Physics::RigidbodyCollision(GameObject* obj)
{
	glm::vec2 depth = parent->GetBoundingBox().CollisionDepth(&obj->GetBoundingBox());

	//velocity -= depth;

	parent->Translate(depth);
}

void Physics::SetStatic(bool static_)
{
	isStatic = static_;
}

bool Physics::GetStatic() const
{
	return isStatic;
}

void Physics::ApplyGravity(bool state_)
{
	if (state_) {
		gravity = Gravity;
	}
	else {
		gravity = glm::vec2(0);
	}
}

void Physics::SetRigidBody(bool state)
{
	isRigid = state;
}

bool Physics::GetRigid() const
{
	return isRigid;
}

void Physics::ApplyDrag(bool state)
{
	applyDrag = state;
}

void Physics::SetSpeedLimit(glm::vec2 limit)
{
	speedCap = limit;
}

void Physics::Drag(float deltaTime)
{
	float drag = 14 * deltaTime;
	if (velocity.x > 0) {
		if (velocity.x <= drag) { velocity.x = 0; }
		else { velocity.x -= drag; }
	}
	else if (velocity.x < 0) {
		if (velocity.x >= -drag) { velocity.x = 0; }
		else { velocity.x += drag; }
	}
}

void Physics::SetAcceleration(glm::vec2 acc_)
{
	acceleration = acc_;
}
