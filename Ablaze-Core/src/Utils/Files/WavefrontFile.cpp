#include "WavefrontFile.h"
#include "Factories/Models/WavefrontWriter.h"
#include "Factories/ModelFactory.h"

namespace Ablaze
{

	WavefrontFile::WavefrontFile(const String& filepath) : TextFile(filepath)
	{
	
	}

	void WavefrontFile::WriteModel(Model* model)
	{
		Internal::WavefrontWriter::WriteToFile(this, model);
	}

	void WavefrontFile::WriteModel(const String& modelName)
	{
		WriteModel(ModelFactory::RequestWeak(modelName));
	}

}