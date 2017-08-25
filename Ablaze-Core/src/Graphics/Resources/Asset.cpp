#include "Asset.h"

namespace Ablaze
{

	Asset::Asset(const String& name)
		: name(name)
	{
	
	}

	Asset::~Asset()
	{
	
	}

	const String& Asset::GetName() const
	{
		return name;
	}

	void Asset::SetName(const String& name)
	{
		this->name = name;
	}

	String Asset::ToString() const
	{
		return GetName();
	}

}