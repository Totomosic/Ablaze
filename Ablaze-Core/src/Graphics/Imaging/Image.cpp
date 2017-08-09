#include "Image.h"

namespace Ablaze
{

	Image::Image(int width, int height, uint bpp, byte* pixels)
		: width(width), height(height), bpp(bpp), pixels(pixels)
	{

	}

	Image::Image(const String& path)
	{
		pixels = Internal::LoadTextureImage(path, &width, &height, &bpp);
	}

	Image::Image(const ImageFile* const file) : Image(file->GetPath())
	{
		
	}

	int Image::GetWidth() const
	{
		return width;
	}

	int Image::GetHeight() const
	{
		return height;
	}

	uint Image::GetBPP() const
	{
		return bpp;
	}

	byte* Image::GetPixels() const
	{
		return pixels;
	}

	Color Image::GetPixel(int x, int y) const
	{
		// TODO: Fix
		return Color();
	}

	Texture2D* Image::ToTexture2D() const
	{
		// TODO: implement
		return nullptr;
	}

}