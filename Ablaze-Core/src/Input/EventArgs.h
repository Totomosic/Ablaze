#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{

	struct EventArgs : public Object
	{
	private:

	public:
		String ToString() const override;

	};

}