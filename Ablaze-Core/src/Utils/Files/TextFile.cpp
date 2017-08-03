#include "TextFile.h"
#include "Utils\Virtual File System\VFS.h"

namespace Ablaze
{

	TextFile::TextFile(const String& path) : DataFile(path, FileType::Text)
	{

	}

	void TextFile::Write(const String& data)
	{
		DataFile::Write((byte*)data.c_str(), data.length());
	}

	void TextFile::WriteLine(const String& line)
	{
		String data = (line + "\n");
		DataFile::AddData((byte*)data.c_str(), data.length());
	}

	String TextFile::Read() const
	{
		if (!isOpen)
		{
			AB_ERROR("File with path: " + physicalPath + " was not opened before reading.");
		}
		return FileSystem::ReadTextFile(handle);
	}

}