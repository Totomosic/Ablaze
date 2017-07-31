#pragma once
#include "DataFile.h"

namespace Ablaze
{

	class VFS;

	class FontFile : public DataFile
	{
	private:

	protected:
		FontFile(const String& filepath);

	public:
		friend class VFS;

	};

}