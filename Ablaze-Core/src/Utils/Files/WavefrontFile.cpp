#include "WavefrontFile.h"
#include "Factories/Models/WavefrontWriter.h"

namespace Ablaze
{

	WavefrontFile::WavefrontFile(const String& filepath) : TextFile(filepath)
	{
	
	}

	WavefrontFile::WavefrontFile(const String& filepath, const String& data) : TextFile(filepath, data)
	{
	
	}

	void WavefrontFile::Write(Model* model)
	{
		Internal::WavefrontWriter::WriteToFile(this, model);
	}

}