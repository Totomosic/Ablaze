#include "CameraComponent.h"
#include "Entities/GameObject.h"
#include "../Motion/Transform.h"

namespace Ablaze
{
	namespace Components
	{

		Components::Camera::Camera(const Viewport& viewport, Projection type, float fieldOfView, Angle Angle, float nearPlane, float farPlane) : Component(),
			viewport(viewport), projection(type), nearPlane(nearPlane), farPlane(farPlane)
		{
			this->fov = (Angle == Angle::Degrees ? maths::ToRadians(fieldOfView) : fieldOfView);
			if (projection == Projection::Perspective)
			{
				projectionMatrix = maths::mat4::Perspective(fov, viewport.GetAspect(), nearPlane, farPlane);
			}
			else
			{
				projectionMatrix = maths::mat4::Orthographic(viewport.GetX(), viewport.GetX() + viewport.GetWidth(), viewport.GetY(), viewport.GetY() + viewport.GetHeight(), nearPlane, farPlane);
			}
		}

		maths::mat4 Camera::GetViewMatrix() const
		{
			if (owner->HasComponent<Components::Transform>())
			{
				return owner->GetComponent<Components::Transform>()->GetModelMatrix().Inverse();
			}
			return maths::mat4::Identity();
		}

		const maths::mat4& Camera::GetProjectionMatrix() const
		{
			return projectionMatrix;
		}

		const Viewport& Camera::GetViewport() const
		{
			return viewport;
		}

		const Projection& Camera::GetProjection() const
		{
			return projection;
		}

		float Camera::GetNearPlane() const
		{
			return nearPlane;
		}

		float Camera::GetFarPlane() const
		{
			return farPlane;
		}

		float Camera::GetFOV() const
		{
			return fov;
		}

		Component* Camera::Clone()
		{
			Camera* camera = new Camera(viewport, projection, fov, Angle::Radians, nearPlane, farPlane);
			return camera;
		}

		void Camera::CreateProjectionMatrix()
		{
			if (projection == Projection::Perspective)
			{
				projectionMatrix = maths::mat4::Perspective(fov, viewport.GetAspect(), nearPlane, farPlane);
			}
			else
			{
				projectionMatrix = maths::mat4::Orthographic(viewport.GetX(), viewport.GetX() + viewport.GetWidth(), viewport.GetY(), viewport.GetY() + viewport.GetHeight(), nearPlane, farPlane);
			}
		}

	}
}