#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{

	class Resource : public Object
	{
	protected:
		String name;

		Resource(const String& name);
		virtual ~Resource();

	public:
		const String& GetName() const;
		void SetName(const String& name);

		String ToString() const override;

	};

}