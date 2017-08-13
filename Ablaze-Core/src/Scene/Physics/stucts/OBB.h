#pragma once
#include "AABB.h"

namespace Ablaze
{

	struct OBB : public AABB
	{
	private:
		maths::vec3 normals[6];

	public:
		maths::mat4 transform;

	public:
		OBB(const maths::vec3& size, const maths::mat4& transform = maths::mat4::Identity());

		maths::vec3 FLT() const override;
		maths::vec3 FLB() const override;
		maths::vec3 FRB() const override;
		maths::vec3 FRT() const override;
		maths::vec3 BRT() const override;
		maths::vec3 BRB() const override;
		maths::vec3 BLB() const override;
		maths::vec3 BLT() const override;

		maths::vec3* GetCorners() const;
		maths::vec3* GetNormals() const;

		AABB* Clone() const override;

	private:
		void CreateDefaultNormals(); // Front, Back, Right, Left, Top, Bottom
		maths::vec3 GetNormal(int index) const;

	};

}