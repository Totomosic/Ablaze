#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{

	class QuadtreeNode : public Object
	{
	private:
		QuadtreeNode** children;
		bool enabled;
		float vertexHeight;

	public:
		QuadtreeNode();
		
		String ToString() const override;

	};

}