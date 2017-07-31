#include "Camera.h"
#include "GameObjects.h"
#include "Components\Rendering\CameraComponent.h"
#include "Components\Misc\Identifier.h"
#include "Tags.h"

namespace Ablaze
{

	bool Camera::firstCamera = true;

	Camera::Camera(const Viewport& viewport, const maths::vec3& position, const maths::mat4& rotation, Projection type, float fov, Angle angle, float nearPlane, float farPlane) : GameObject(position, rotation)
	{
		AddComponent(new Components::Camera(viewport, type, fov, angle, nearPlane, farPlane));
		if (firstCamera)
		{
			firstCamera = false;
			AddComponent(new Components::Identifier(Tags::MainCamera));
		}
	}

	Camera::Camera() : Camera(Viewport(), maths::vec3(0, 0, 0))
	{
	
	}

	Components::Camera* Camera::CameraComponent() const
	{
		return GetComponent<Components::Camera>();
	}

	maths::mat4 Camera::ProjectionMatrix() const
	{
		return CameraComponent()->GetProjectionMatrix();
	}

	maths::mat4 Camera::ViewMatrix() const
	{
		return CameraComponent()->GetViewMatrix();
	}

	Camera* Camera::Main()
	{
		return (Camera*)GameObjects::GetWithName("Main Camera");
	}

}