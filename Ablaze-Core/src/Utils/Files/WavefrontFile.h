#pragma once
#include "TextFile.h"

namespace Ablaze
{

	class VFS;

	class WavefrontFile : public TextFile
	{
	protected:
		WavefrontFile(const String& filepath);
		WavefrontFile(const String& filepath, const String& data);

	public:
		friend class VFS;

	};

}