#include "AABB.h"
#include "Factories/ModelFactory.h"

namespace Ablaze
{

	AABB::AABB(const maths::vec3& size)
		: size(size)
	{
	
	}

	maths::vec3 AABB::FLT() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(-s.x, s.y, s.z);
	}

	maths::vec3 AABB::FLB() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(-s.x, -s.y, s.z);
	}

	maths::vec3 AABB::FRB() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(s.x, -s.y, s.z);
	}

	maths::vec3 AABB::FRT() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(s.x, s.y, s.z);
	}

	maths::vec3 AABB::BRT() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(s.x, s.y, -s.z);
	}

	maths::vec3 AABB::BRB() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(s.x, -s.y, -s.z);
	}

	maths::vec3 AABB::BLB() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(-s.x, -s.y, -s.z);
	}

	maths::vec3 AABB::BLT() const
	{
		maths::vec3 s = size / 2.0f;
		return maths::vec3(-s.x, s.y, -s.z);
	}

	const maths::vec3& AABB::GetSize() const
	{
		return size;
	}

	maths::vec3 AABB::GetCenter() const
	{
		return maths::vec3(0, 0, 0);
	}

	maths::vec3 AABB::GetMax() const
	{
		return FRT();
	}

	maths::vec3 AABB::GetMin() const
	{
		return BLB();
	}

	void AABB::SetSize(const maths::vec3& size)
	{
		this->size = size;
	}

	AABB* AABB::Clone() const
	{
		return new AABB(size);
	}

	AABB AABB::FromModel(Model* model)
	{
		return AABB(model->GetSize());
	}

	AABB AABB::FromModel(const String& modelName)
	{
		return FromModel(ModelFactory::RequestWeak(modelName));
	}

}