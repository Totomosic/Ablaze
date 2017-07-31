#pragma once
#include "../Component.h"
#include "Graphics/Viewport.h"

namespace Ablaze
{
	namespace Components
	{
		class Camera : public Component
		{
		private: 
			Viewport viewport;
			maths::mat4 projectionMatrix;
			Projection projection;

			float fov; // Perspective projection only, in radians
			float nearPlane;
			float farPlane;

		public:
			Camera(const Viewport& viewport, Projection type, float fieldOfView = (float)M_PI / 3.0f, Angle Angle = Angle::Radians, float near = 1.0f, float far = 1000.0f);

			maths::mat4 GetViewMatrix() const;
			const maths::mat4& GetProjectionMatrix() const;
			const Viewport& GetViewport() const;
			const Projection& GetProjection() const;
			float GetNearPlane() const;
			float GetFarPlane() const;
			float GetFOV() const;

			Component* Clone() override;

		private:
			void CreateProjectionMatrix();

		};
	}
}