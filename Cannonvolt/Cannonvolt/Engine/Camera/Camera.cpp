#include "Camera.h"
#include "../Core/CoreEngine.h"


Camera::Camera() : position(glm::vec3())
{
	fieldOfView = 45.0f;
	forward = glm::vec3(0, 0, 1.0f);
	up = glm::vec3(0, 1.0f, 0);
	worldUp = up;
	nearPlane = 2.0f;
	farPlane = 50.0f;
	yaw = -90.0f;
	pitch = 0.0f;

	perspective = glm::perspective(fieldOfView,
		CoreEngine::GetInstance()->GetWindowSize().x /
		CoreEngine::GetInstance()->GetWindowSize().y,
		nearPlane, farPlane);

	orthographic = glm::ortho(0.0f, CoreEngine::GetInstance()->GetWindowSize().x,
		0.0f, CoreEngine::GetInstance()->GetWindowSize().y, -1.0f, 1.0f);

	UpdateCameraVectors();
}

Camera::~Camera()
{
	OnDestroy();
}

void Camera::SetPosition(glm::vec3 position_)
{
	position = position_;
	UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
	yaw = yaw_;
	pitch = pitch_;
	UpdateCameraVectors();
}

void Camera::Translate(const glm::vec3 movement_)
{
	SetPosition(position + movement_);
}

glm::mat4 Camera::GetView() const
{
	return glm::lookAt(position, position + forward, up);
}

glm::mat4 Camera::GetPerspective() const
{
	return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
	return orthographic;
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}

glm::vec2 Camera::GetClippingPlanes() const
{
	return glm::vec2(nearPlane, farPlane);

}

std::vector<float> Camera::GetFrustumPlanes()
{
	std::vector<float> frustum;
	frustum.reserve(4);

	std::vector<float> frustum;
	frustum.reserve(4);

	//Left

	frustum.push_back(position.x);

	//Right

	frustum.push_back(position.x + CoreEngine::GetInstance()->GetWindowSize().x);

	//Top

	frustum.push_back(position.y + CoreEngine::GetInstance()->GetWindowSize().y);

	//Bottom
	frustum.push_back(position.y);

	return frustum;
}

//AABB culling
bool Camera::FrustumCull(std::vector<float> frustum_, BoundingBox* box_)
{
	if (box_->pos.x + box_->dimentions.x >= frustum_[0]
		&& box_->pos.x <= frustum_[1]
		&& box_->pos.y <= frustum_[2]
		&& box_->pos.y + box_->dimentions.y >= frustum_[3])
	{
		return true;
	}

	return false;
}

void Camera::UpdateCameraVectors()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	forward = glm::normalize(forward);

	right = glm::normalize(glm::cross(forward, worldUp));

	up = glm::normalize(glm::cross(right, forward));
}

void Camera::OnDestroy() {

}