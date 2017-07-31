#include "BoundingBox.h"

namespace Ablaze
{

	BoundingBox::BoundingBox(const maths::vec3& size)
		: size(size)
	{
	
	}

	const maths::vec3& BoundingBox::GetSize() const
	{
		return size;
	}

	maths::vec3 BoundingBox::GetCenter() const
	{
		return maths::vec3(0, 0, 0);
	}

	maths::vec3 BoundingBox::GetMax() const
	{
		return size / 2.0f;
	}

	maths::vec3 BoundingBox::GetMin() const
	{
		return size / -2.0f;
	}

	void BoundingBox::SetSize(const maths::vec3& size)
	{
		this->size = size;
	}

	BoundingBox* BoundingBox::Clone() const
	{
		return new BoundingBox(size);
	}

}