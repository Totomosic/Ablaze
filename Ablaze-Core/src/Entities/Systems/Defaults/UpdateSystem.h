#pragma once
#include "Entities/Systems/System.h"

namespace Ablaze
{

	class UpdateSytem : public System
	{
	public:
		UpdateSytem();

		void Run() override;

	};

}