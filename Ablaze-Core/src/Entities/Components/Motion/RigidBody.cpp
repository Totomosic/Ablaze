#include "RigidBody.h"

namespace Ablaze
{
	namespace Components
	{

		RigidBody::RigidBody(float mass, bool isStatic, const maths::vec3& velocity, const maths::vec3& acceleration, bool gravityAffected)
			: Component(), mass(mass), staticObject(isStatic), velocity(velocity), acceleration(acceleration), gravityAffected(gravityAffected)
		{

		}

		RigidBody::RigidBody() : RigidBody(1)
		{

		}

		RigidBody::~RigidBody()
		{

		}

		float RigidBody::GetMass() const
		{
			return mass;
		}

		const maths::vec3& RigidBody::GetVelocity() const
		{
			return velocity;
		}

		const maths::vec3& RigidBody::GetAcceleration() const
		{
			return acceleration;
		}

		bool RigidBody::AffectedByGravity() const
		{
			return gravityAffected;
		}

		bool RigidBody::IsStatic() const
		{
			return staticObject;
		}

		maths::vec3& RigidBody::Velocity()
		{
			return velocity;
		}

		maths::vec3& RigidBody::Acceleration()
		{
			return acceleration;
		}

		void RigidBody::ApplyForce(const maths::vec3& force)
		{
			// F = ma -> a = F / m
			acceleration += force / mass;
		}

		void RigidBody::SetMass(float mass)
		{
			this->mass = mass;
		}

		void RigidBody::SetVelocity(const maths::vec3& velocity)
		{
			this->velocity = velocity;
		}

		void RigidBody::SetAcceleration(const maths::vec3& acceleration)
		{
			this->acceleration = acceleration;
		}

		void RigidBody::SetGravity(bool gravityAffected)
		{
			this->gravityAffected = gravityAffected;
		}

		void RigidBody::EnableGravity()
		{
			SetGravity(true);
		}

		void RigidBody::DisableGravity()
		{
			SetGravity(false);
		}

		void RigidBody::SetStatic(bool isStatic)
		{
			staticObject = isStatic;
		}

		Component* RigidBody::Clone()
		{
			RigidBody* rb = new RigidBody(mass, staticObject, velocity, acceleration, gravityAffected);
			return rb;
		}

	}
}