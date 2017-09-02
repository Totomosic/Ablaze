#include "Transform.h"
#include "Entities/GameObject.h"
#include "Log.h"

namespace Ablaze
{
	namespace Components
	{

		Transform::Transform(const maths::vec3& position, const maths::mat4& rotation, const maths::vec3& scale) : Component(), 
			position(position), rotation(rotation), scale(scale)
		{
			
		}

		Transform::Transform() : Transform(maths::vec3(0, 0, 0))
		{
		
		}

		Component* Transform::Clone()
		{
			Transform* t = new Transform(position, rotation, scale);
			return t;
		}

		maths::vec3 Transform::GetPosition() const
		{
 			if (owner->HasParent())
			{
				return owner->Parent()->Transform()->GetModelMatrix().GetColumn(3).xyz() + position;
			}
			return position;
		}

		maths::vec3 Transform::GetNievePosition() const
		{
			if (owner->HasParent())
			{
				return owner->Parent()->Transform()->GetNievePosition() + position;
			}
			return position;
		}

		maths::mat4 Transform::GetRotation() const
		{
			if (owner->HasParent())
			{
				return rotation * owner->Parent()->Transform()->GetRotation();
			}
			return rotation;
		}

		maths::vec3 Transform::GetScale() const
		{
			if (owner->HasParent())
			{
				return owner->Parent()->Transform()->GetScale() * scale;
			}
			return scale;
		}

		maths::mat4 Transform::GetModelMatrix() const
		{
			if (owner->HasParent())
			{
				return owner->Parent()->Transform()->GetModelMatrix() * maths::mat4::Translation(position) * rotation * maths::mat4::Scale(scale);
			}
			return maths::mat4::Translation(position) * rotation * maths::mat4::Scale(scale);
		}

		maths::vec3 Transform::Forward() const
		{
			maths::mat4 rot = GetRotation().Inverse();
			return maths::vec3(-rot.values[2 + 0 * 4], -rot.values[2 + 1 * 4], -rot.values[2 + 2 * 4]);
		}

		maths::vec3 Transform::Right() const
		{
			maths::mat4 rot = GetRotation().Inverse();
			return maths::vec3(rot.values[0 + 0 * 4], rot.values[0 + 1 * 4], rot.values[0 + 2 * 4]);
		}

		maths::vec3 Transform::Up() const
		{
			maths::mat4 rot = GetRotation().Inverse();
			return maths::vec3(rot.values[1 + 0 * 4], rot.values[1 + 1 * 4], rot.values[1 + 2 * 4]);
		}

		void Transform::SetPosition(const maths::vec3& position)
		{
			this->position = position;
		}

		void Transform::SetRotation(const maths::mat4& rotation)
		{
			this->rotation = rotation;
		}

		void Transform::SetScale(const maths::vec3& scale)
		{
			this->scale = scale;
		}

		void Transform::SetScale(float scale)
		{
			SetScale(maths::vec3(scale, scale, scale));
		}

		void Transform::Rotate(float angle, const maths::vec3& axis, Space space, Angle Angle)
		{
			maths::vec3 rotAxis = axis;
			if (space == Space::World)
			{
				rotAxis = (rotation.Inverse() * maths::vec4(rotAxis, 0)).xyz();
			}
			if (Angle == Angle::Degrees)
			{
				angle = maths::ToRadians(angle);
			}
			maths::mat4 rotationMatrix = maths::mat4::Rotation(angle, rotAxis);
			rotation *= rotationMatrix;
		}

		void Transform::Translate(const maths::vec3& translation, Space space)
		{
			if (space == Space::Local)
			{
				// TODO: alter translation to be relative to forward vector
			}
			position += translation;
		}

		void Transform::TranslateX(float amount, Space space)
		{
			if (space == Space::Local)
			{

			}
			Translate(maths::vec3(amount, 0, 0));
		}

		void Transform::TranslateY(float amount, Space space)
		{
			if (space == Space::Local)
			{

			}
			Translate(maths::vec3(0, amount, 0));
		}

		void Transform::TranslateZ(float amount, Space space)
		{
			if (space == Space::Local)
			{

			}
			Translate(maths::vec3(0, 0, amount));
		}

	}
}