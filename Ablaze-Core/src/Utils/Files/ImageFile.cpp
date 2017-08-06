#include "ImageFile.h"
#include "Graphics/Imaging/ImageLoader.h"

namespace Ablaze
{

	ImageFile::ImageFile(const String& path) : DataFile(path, FileType::Image)
	{
	
	}
	
	byte* ImageFile::ReadImage(GLsizei* width, GLsizei* height, uint* bpp)
	{
		return Internal::LoadTextureImage(physicalPath, width, height, bpp);
	}

}