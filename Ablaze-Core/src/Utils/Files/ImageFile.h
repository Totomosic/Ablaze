#pragma once
#include "DataFile.h"

namespace Ablaze
{

	class VFS;

	class ImageFile : public DataFile
	{
	protected:
		ImageFile(const String& physicalPath);

	public:
		friend class VFS;

	};

}