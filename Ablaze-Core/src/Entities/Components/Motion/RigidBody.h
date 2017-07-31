#pragma once
#include "Entities/Components/Component.h"

namespace Ablaze
{
	namespace Components
	{

		class RigidBody : public Component
		{
		private:
			float mass;
			maths::vec3 velocity;
			maths::vec3 acceleration;
			bool gravityAffected;
			bool staticObject;

		public:
			RigidBody(float mass, bool staticObject = false, const maths::vec3& velocity = maths::vec3(0.0f), const maths::vec3& acceleration = maths::vec3(0.0f), bool gravityAffected = true);
			RigidBody();
			~RigidBody();

			float GetMass() const;
			const maths::vec3& GetVelocity() const;
			const maths::vec3& GetAcceleration() const;
			bool AffectedByGravity() const;
			bool IsStatic() const;

			maths::vec3& Velocity();
			maths::vec3& Acceleration();

			void ApplyForce(const maths::vec3& force);

			void SetGravity(bool affected);
			void EnableGravity();
			void DisableGravity();
			void SetMass(float mass);
			void SetVelocity(const maths::vec3& velocity);
			void SetAcceleration(const maths::vec3& acceleration);
			void SetStatic(bool isStatic);

			Component* Clone() override;

		};

	}
}