#pragma once
#include "../Component.h"

namespace Ablaze
{
	namespace Components
	{

		class Transform : public Component
		{
		private:
			maths::vec3 position;
			maths::mat4 rotation;
			maths::vec3 scale;

		public:
			Transform(const maths::vec3& position, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
			Transform();

			Component* Clone() override;

			maths::vec3 GetPosition() const;
			maths::vec3 GetNievePosition() const; // Does not account for rotation, could be inaccurate
			maths::mat4 GetRotation() const;
			const maths::vec3& GetScale() const;
			maths::mat4 GetModelMatrix() const;
			maths::vec3 Forward() const;
			maths::vec3 Right() const;
			maths::vec3 Up() const;

			void SetPosition(const maths::vec3& position);
			void SetRotation(const maths::mat4& rotation);
			void SetScale(const maths::vec3& scale);
			void SetScale(float scale);

			void Rotate(float angle, const maths::vec3& axis, Space space = Space::Local, Angle Angle = Angle::Radians);
			void Translate(const maths::vec3& translation, Space space = Space::World);
			void TranslateX(float amount, Space space = Space::World);
			void TranslateY(float amount, Space space = Space::World);
			void TranslateZ(float amount, Space space = Space::World);

		};
	}
}