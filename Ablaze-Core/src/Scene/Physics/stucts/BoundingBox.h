#pragma once
#include "Maths/Maths.h"
#include "Types.h"

namespace Ablaze
{

	class Model;

	struct BoundingBox
	{
	public:
		maths::vec3 size;

	public:
		BoundingBox(const maths::vec3& size);

		const maths::vec3& GetSize() const;
		maths::vec3 GetCenter() const; // always (0, 0, 0)
		maths::vec3 GetMax() const;
		maths::vec3 GetMin() const;

		void SetSize(const maths::vec3& size);

		BoundingBox* Clone() const;

		static BoundingBox FromModel(Model* model);
		static BoundingBox FromModel(const String& modelName);

	};

}