#pragma once
#include "Renderable.h"
#include "Object.h"
#include "RenderEngine/structs/Commands/Command.h"
#include <deque>

namespace Ablaze
{

	class Renderer : public Object
	{
	private:
		std::deque<Command*> commandQueue;
		maths::mat4 viewMatrix;
		maths::mat4 projectionMatrix;

	public:
		Renderer();

		void PushCommand(Command* command);
		void PopCommand();

		void Execute(const maths::mat4& viewMatrix, const maths::mat4& projectionMatrix);

		const maths::mat4& GetViewMatrix() const;
		const maths::mat4& GetProjectionMatrix() const;
		void SetViewMatrix(const maths::mat4& viewMatrix);
		void SetProjectionMatrix(const maths::mat4& projectionMatrix);

		String ToString() const override;

	};

}                  