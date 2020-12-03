#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>
#include <vector>
#include "../Core/Debug.h"


/*
Used to determine what and how information is displayed to the screen and 
uses frustum culling to prevent redundent rendering
*/

struct BoundingBox;

class Camera
{
public:
	Camera();
	~Camera();

	void SetPosition(glm::vec3 position_);
	void SetRotation(float yaw_, float pitch_);

	glm::mat4 GetView() const;
	glm::mat4 GetPerspective() const;
	glm::mat4 GetOrthographic() const;
	glm::vec3 GetPosition() const;
	glm::vec2 GetClippingPlanes() const;

	std::vector<glm::vec4> GetFrustumPlanes();

	bool FrustumCull(std::vector<glm::vec4> frustum_, BoundingBox* box_);

	void Translate(glm::vec3 movement_);


private: 
	void UpdateCameraVectors();
	
	glm::vec3 position;

	glm::mat4 perspective;
	glm::mat4 orthographic;

	float fieldOfView;
	float yaw, pitch;
	float nearPlane, farPlane;

	glm::vec3 forward, up, right, worldUp;

	void OnDestroy();
};

#endif // !CAMERA_H
