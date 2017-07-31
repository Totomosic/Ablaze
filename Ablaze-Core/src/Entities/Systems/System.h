#pragma once
#include "Entities/GameObjects.h"
#include "Entities/Components/Components.h"
#include "Graphics/Time.h"
#include "Types.h"
#include "Log.h"

namespace Ablaze
{

	class System
	{
	protected:
		System() { }

	public:		
		virtual ~System() { }

		virtual void Run() = 0;

	};

}