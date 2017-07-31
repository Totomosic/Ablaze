#pragma once
#include "Enums.h"
#include "Object.h"

namespace Ablaze
{

	class Renderer;

	class Command : public Object
	{
	protected:
		CommandType type;

	public:
		Command(const CommandType& type);

		const CommandType& GetType() const;
		virtual void Execute(Renderer& renderer) = 0;

		String ToString() const override;

	};

}