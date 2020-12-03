#include "Platform.h"
#include "../Engine/Graphics/ShaderHandler.h"

Platform::Platform() : GameObject(new Sprite(ShaderHandler::GetInstance()->GetShader("basicShader"), "Blue", this))
{
}

Platform::~Platform()
{
}

bool Platform::OnCreate()
{
	SetStatic(true);
	SetRigid(true);
	SetScale(glm::vec2(10.0f));
	SetTag("Ground");
	return true;
}

void Platform::Update(const float deltaTime_)
{
}
