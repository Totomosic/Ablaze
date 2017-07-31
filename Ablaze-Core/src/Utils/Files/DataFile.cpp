#include "DataFile.h"
#include "Utils\Virtual File System\VFS.h"

namespace Ablaze
{
	
	DataFile::DataFile(const String& filepath, FileType type)
		: physicalPath(filepath), type(type)
	{
	
	}

	const String& DataFile::GetPath() const
	{
		return physicalPath;
	}

	FileType DataFile::GetType() const
	{
		return type;
	}

	void DataFile::Write(byte* data, int64 length)
	{
		WriteTo(physicalPath, data, length);
	}

	void DataFile::WriteTo(const String& filepath)
	{
		// Needs to be overridden
	}

	void DataFile::WriteTo(const String& filepath, byte* data, int64 length)
	{
		FileSystem::WriteFile(filepath, data, length);
	}

	void DataFile::CopyTo(const String& filepath)
	{
		int64 length;
		byte* data = Read(&length);
		FileSystem::WriteFile(VFS::ResolvePhysicalPath(filepath, 0), data, length);
	}

	byte* DataFile::Read(int64* outLength)
	{
		return FileSystem::ReadFile(physicalPath, outLength);
	}

	void DataFile::Read(void* buffer, int64 length)
	{
		FileSystem::ReadFile(physicalPath, buffer, length);
	}

	void DataFile::Delete()
	{
		FileSystem::DeleteDataFile(physicalPath);
	}

}