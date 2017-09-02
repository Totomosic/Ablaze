#pragma once
#include "Maths/Maths.h"
#include "Types.h"

namespace Ablaze
{

	class Model;

	struct AABB
	{
	public:
		maths::vec3 size;

	public:
		AABB(const maths::vec3& size);

		virtual maths::vec3 FLT() const;
		virtual maths::vec3 FLB() const;
		virtual maths::vec3 FRB() const;
		virtual maths::vec3 FRT() const;
		virtual maths::vec3 BRT() const;
		virtual maths::vec3 BRB() const;
		virtual maths::vec3 BLB() const;
		virtual maths::vec3 BLT() const;

		const maths::vec3& GetSize() const;
		maths::vec3 GetCenter() const; // always (0, 0, 0)
		virtual maths::vec3 GetMax() const;
		virtual maths::vec3 GetMin() const;
		
		void SetSize(const maths::vec3& size);

		virtual AABB Clone() const;

		static AABB FromModel(Model* model);
		static AABB FromModel(const String& modelName);

	};

}