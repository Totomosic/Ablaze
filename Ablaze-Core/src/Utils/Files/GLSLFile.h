#pragma once
#include "TextFile.h"

namespace Ablaze
{

	class VFS;

	class GLSLFile : public TextFile
	{
	protected:
		GLSLFile(const String& path);

	public:
		friend class VFS;

	};

}