#pragma once
#include "Image.h"

namespace Ablaze
{

	class Bitmap : public Image
	{
	public:
		Bitmap(const String& path);
		Bitmap(const ImageFile* const file);

	};

}