#include "TextFile.h"
#include "Utils\Virtual File System\VFS.h"

namespace Ablaze
{

	TextFile::TextFile(const String& path) : DataFile(path, FileType::Text)
	{

	}

	TextFile::TextFile(const String& path, const String& data) : DataFile(path, FileType::Text)
	{
		WriteTo(path, data);
	}

	void TextFile::Write(const String& data) const
	{
		WriteTo(physicalPath, data);
	}

	void TextFile::WriteTo(const String& path, const String& data) const
	{
		FileSystem::WriteTextFile(path, data);
	}

	String TextFile::Read() const
	{
		return FileSystem::ReadTextFile(physicalPath);
	}

}