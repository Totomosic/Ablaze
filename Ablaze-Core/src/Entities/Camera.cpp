#include "Camera.h"
#include "GameObjects.h"
#include "Components\Rendering\CameraComponent.h"
#include "Components\Misc\Identifier.h"
#include "Components\Motion\Transform.h"
#include "Graphics\Context.h"
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

	maths::vec3 Camera::ScreenPointToWorldPoint(const maths::vec3& point) const
	{
		maths::vec4 screenPosition = maths::vec4(point, 1);
		maths::vec4 worldSpace = ViewMatrix().Inverse() * screenPosition;
		return worldSpace.xyz();
	}

	Ray Camera::ScreenPointToWorldRay(const maths::vec3& point) const
	{
		maths::vec4 screenPosition = maths::vec4(point, 1);
		screenPosition.z = -1;
		screenPosition = ProjectionMatrix().Inverse() * screenPosition;
		maths::vec4 worldSpace = ViewMatrix().Inverse() * screenPosition;
		return Ray(Transform()->GetPosition(), worldSpace.xyz());
	}

	Camera* Camera::Main()
	{
		return (Camera*)GameObjects::GetWithName("Main Camera");
	}

}