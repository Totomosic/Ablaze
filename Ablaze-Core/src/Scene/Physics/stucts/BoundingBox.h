#pragma once
#include "Maths\Maths.h"

namespace Ablaze
{

	struct BoundingBox
	{
	maths::vec3 size;

	public:
		BoundingBox(const maths::vec3& size);

		const maths::vec3& GetSize() const;
		maths::vec3 GetCenter() const; // always (0, 0, 0)
		maths::vec3 GetMax() const;
		maths::vec3 GetMin() const;

		void SetSize(const maths::vec3& size);

		BoundingBox* Clone() const;

	};

}