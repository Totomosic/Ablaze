#pragma once
#include "TextFile.h"
#include "RenderEngine/structs/Model.h"

namespace Ablaze
{

	class VFS;

	class WavefrontFile : public TextFile
	{
	protected:
		WavefrontFile(const String& filepath);
		WavefrontFile(const String& filepath, const String& data);

	public:
		void Write(Model* model);

		friend class VFS;

	};

}