#pragma once
#include "Entities/GameObject.h"
#include "Entities/GameObjects.h"

namespace Ablaze
{

	class Widget : public GameObject
	{
	protected:
		maths::vec2 size;

	public:
		Widget(const maths::vec2& size);
		Widget(const maths::vec3& position, const maths::vec2& size, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));
		Widget(float x, float y, float z, const maths::vec2& size, const maths::mat4& rotation = maths::mat4::Identity(), const maths::vec3& scale = maths::vec3(1, 1, 1));

		maths::vec3 Position() const;
		const maths::vec2& Size() const;

	};

}