#include "Resource.h"

namespace Ablaze
{

	Resource::Resource(const String& name)
		: name(name)
	{
	
	}

	Resource::~Resource()
	{
	
	}

	const String& Resource::GetName() const
	{
		return name;
	}

	void Resource::SetName(const String& name)
	{
		this->name = name;
	}

	String Resource::ToString() const
	{
		return GetName();
	}

}