#pragma once
#include "Utils/Files/WavefrontFile.h"
#include "Utils/Virtual File System/VFS.h"
#include "Graphics/Resources/Model.h"

namespace Ablaze
{
	namespace Internal
	{

		class WavefrontWriter
		{
		public:
			WavefrontWriter() { }

			static void WriteToFile(WavefrontFile* file, Model* model);

		};

	}
}