#pragma once
#include "GameObject.h"
#include "Graphics/Viewport.h"

namespace Ablaze
{

	namespace Components
	{
		class Camera;
	}

	class Camera : public GameObject
	{
	protected:
		static bool firstCamera;

	public:
		Camera(const Viewport& viewport, const maths::vec3& position, const maths::mat4& rotation = maths::mat4::Identity(), Projection type = Projection::Perspective, float fov = (float)M_PI / 3.0f, Angle angle = Angle::Radians, float near = 1.0f, float far = 1000.0f);
		Camera();

		Components::Camera* CameraComponent() const;
		maths::mat4 ProjectionMatrix() const;
		maths::mat4 ViewMatrix() const;

		Ray ScreenPointToWorldRay(const maths::vec3& point) const;
		maths::vec3 ScreenPointToWorldPoint(const maths::vec3& point) const;

		static Camera* Main();

	};

}