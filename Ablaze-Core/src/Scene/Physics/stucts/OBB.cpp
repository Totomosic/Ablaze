#include "OBB.h"

namespace Ablaze
{

	OBB::OBB(const maths::vec3& size, const maths::mat4& transform) : AABB(size),
		transform(transform)
	{
		CreateDefaultNormals();
	}

	maths::vec3 OBB::FLT() const
	{
		return (transform * maths::vec4(AABB::FLT(), 1)).xyz();
	}

	maths::vec3 OBB::FLB() const
	{
		return (transform * maths::vec4(AABB::FLB(), 1)).xyz();
	}

	maths::vec3 OBB::FRB() const
	{
		return (transform * maths::vec4(AABB::FRB(), 1)).xyz();
	}

	maths::vec3 OBB::FRT() const
	{
		return (transform * maths::vec4(AABB::FRT(), 1)).xyz();
	}

	maths::vec3 OBB::BRT() const
	{
		return (transform * maths::vec4(AABB::BRT(), 1)).xyz();
	}

	maths::vec3 OBB::BRB() const
	{
		return (transform * maths::vec4(AABB::BRB(), 1)).xyz();
	}

	maths::vec3 OBB::BLB() const
	{
		return (transform * maths::vec4(AABB::BLB(), 1)).xyz();
	}

	maths::vec3 OBB::BLT() const
	{
		return (transform * maths::vec4(AABB::BLT(), 1)).xyz();
	}

	maths::vec3* OBB::GetCorners() const
	{
		return new maths::vec3[8]{ FLT(), FLB(), FRB(), FRT(), BRT(), BRB(), BLB(), BLT() };
	}

	maths::vec3* OBB::GetNormals() const
	{
		return new maths::vec3[6]{ GetNormal(0), GetNormal(1), GetNormal(2), GetNormal(3), GetNormal(4), GetNormal(5) };
	}

	AABB* OBB::Clone() const
	{
		OBB* obb = new OBB(size, transform);
		return obb;
	}

	void OBB::CreateDefaultNormals()
	{
		normals[0] = maths::vec3(0, 0, 1);
		normals[1] = maths::vec3(0, 0, -1);
		normals[2] = maths::vec3(1, 0, 0);
		normals[3] = maths::vec3(-1, 0, 0);
		normals[4] = maths::vec3(0, 1, 0);
		normals[5] = maths::vec3(0, -1, 0);
	}

	maths::vec3 OBB::GetNormal(int index) const
	{
		return (transform * maths::vec4(normals[index], 0)).xyz();
	}

}