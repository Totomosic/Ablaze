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

	public:
		void WriteModel(Model* model);
		void WriteModel(const String& modelName);

		friend class VFS;

	};

}