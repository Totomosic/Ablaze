#pragma once
#include "Background.h"

namespace Ablaze
{

	class Menu : public Background
	{
	private:
		std::vector<GameObject*> widgets;

	public:
		Menu(const maths::vec3& position, const maths::vec2& size, const Color& color, const maths::mat4& transform = maths::mat4::Identity());
		Menu(float x, float y, float z, const maths::vec2& size, const Color& color, const maths::mat4& transform = maths::mat4::Identity());
		Menu(float x, float y, float z, float w, float h, const Color& color, const maths::mat4& transform = maths::mat4::Identity());
		Menu(const maths::vec3& position, float w, float h, const Color& color, const maths::mat4& transform = maths::mat4::Identity());
		Menu(float x, float y, const maths::vec2& size, const Color& color, const maths::mat4& transform = maths::mat4::Identity());
		Menu(float x, float y, float w, float h , const Color& color, const maths::mat4& transform = maths::mat4::Identity());

		GameObject* GetWidget(int index = 0) const;
		void PushWidget(GameObject* widget);

	};

}