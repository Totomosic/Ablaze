#pragma once
#include "Utils/Files/ImageFile.h"
#include "ImageLoader.h"
#include "Types.h"
#include "Log.h"

namespace Ablaze
{

	class Texture2D;

	class Image
	{
	protected:
		int width;
		int height;
		uint bpp;

		byte* pixels;

	protected:
		Image(const String& path);
		Image(const ImageFile* const file);
		Image(int width, int height, uint bpp, byte* pixels);

	public:
		virtual ~Image();

		int GetWidth() const;
		int GetHeight() const;
		uint GetBPP() const;
		byte* GetPixels() const;
		Color GetPixel(int x, int y) const;

		Texture2D* ToTexture2D() const;

		static Image* FromTexture2D(Texture2D* const texture);

	private:

	};

}