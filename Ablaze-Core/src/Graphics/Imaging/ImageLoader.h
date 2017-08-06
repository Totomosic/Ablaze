#pragma once
#include <FreeImage.h>
#include "Types.h"
#include "Log.h"

namespace Ablaze
{
	namespace Internal
	{
		static byte* LoadTextureImage(String filename, GLsizei* width, GLsizei* height, uint* bpp)
		{
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			FIBITMAP *dib = nullptr;

			fif = FreeImage_GetFileType(filename.c_str(), 0);
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(filename.c_str());
			if (fif == FIF_UNKNOWN)
			{
				AB_ERROR("Unable to identify file: " + filename);
				return nullptr;
			}

			if (FreeImage_FIFSupportsReading(fif))
			{
				dib = FreeImage_Load(fif, filename.c_str());
			}
			if (!dib)
			{
				AB_ERROR("Unable to identify file: " + filename);
				return nullptr;
			}

			//retrieve the image data
			byte* pixels = FreeImage_GetBits(dib);
			//get the image width and height

			uint w = FreeImage_GetWidth(dib);
			uint h = FreeImage_GetHeight(dib);
			uint b = FreeImage_GetBPP(dib);

			*width = w;
			*height = h;
			*bpp = b;
			int size = w * h * (b / 8);
			byte* result = new byte[size];
			memcpy(result, pixels, size);

			FreeImage_Unload(dib);

			return result;
		}
	}
}