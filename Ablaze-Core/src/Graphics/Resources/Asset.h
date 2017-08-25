#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{

	class Asset : public Object
	{
	protected:
		String name;

		Asset(const String& name);
		virtual ~Asset();

	public:
		const String& GetName() const;
		void SetName(const String& name);

		String ToString() const override;

	};

}