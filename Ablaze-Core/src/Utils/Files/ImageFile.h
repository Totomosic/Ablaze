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
		byte* ReadImage(GLsizei* width, GLsizei* height, uint* bpp);

		friend class VFS;

	};

}