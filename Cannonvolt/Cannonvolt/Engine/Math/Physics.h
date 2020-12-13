#pragma once
#include <glm/glm.hpp>

class GameObject;

class Physics {
public:
	Physics();
	~Physics();

	void OnCreate(GameObject* parent_);

	void Update(const float deltaTime);

	//Setters

	void ApplyForce(glm::vec2 force_, float rotation_);

	void RigidbodyCollision(GameObject* obj);

	void SetStatic(bool static_);

	bool GetStatic() const;

	void ApplyGravity(bool state);

	void SetRigidBody(bool state);
	bool GetRigid() const;

	void ApplyDrag(bool state);
	void SetSpeedLimit(glm::vec2 limit);

private:
	void Drag(float deltaTime_);

	void SetAcceleration(glm::vec2 acc_);

	GameObject* parent;

	glm::vec2 velocity, acceleration;

	bool isStatic;
	bool isRigid;
	bool applyDrag;
	
	glm::vec2 gravity;
	glm::vec2 speedCap;
};