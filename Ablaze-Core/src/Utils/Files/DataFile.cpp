#include "DataFile.h"
#include "Utils\Virtual File System\VFS.h"

namespace Ablaze
{
	
	DataFile::DataFile(const String& filepath, FileType type)
		: physicalPath(filepath), type(type)
	{
		handle = nullptr;
		isOpen = false;
	}

	const String& DataFile::GetPath() const
	{
		return physicalPath;
	}

	FileType DataFile::GetType() const
	{
		return type;
	}

	bool DataFile::IsOpen() const
	{
		return isOpen;
	}

	HANDLE DataFile::GetHandle() const
	{
		return handle;
	}

	HANDLE DataFile::Open(bool clearFile)
	{
		handle = FileSystem::OpenFile(physicalPath, clearFile);
		isOpen = true;
		return handle;
	}

	void DataFile::Close()
	{
		FileSystem::CloseFile(handle);
		handle = nullptr;
		isOpen = false;
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
		HANDLE file = FileSystem::OpenFile(filepath, false);
		FileSystem::WriteFile(file, data, length);
		FileSystem::CloseFile(file);
	}

	void DataFile::CopyTo(const String& filepath)
	{
		int64 length;
		byte* data = Read(&length);
		HANDLE file = FileSystem::OpenFile(VFS::ResolvePhysicalPath(filepath, 0), false);
		FileSystem::WriteFile(handle, data, length);
		FileSystem::CloseFile(file);
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