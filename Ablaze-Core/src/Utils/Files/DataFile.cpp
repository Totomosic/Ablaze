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

	HANDLE DataFile::OpenInternal(OpenMode mode, bool appendData)
	{
		handle = FileSystem::OpenFile(physicalPath, mode, true, appendData);
		isOpen = true;
		return handle;
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

	HANDLE DataFile::Open(OpenMode mode)
	{
		return OpenInternal(mode, true);
	}

	void DataFile::Close()
	{
		FileSystem::CloseFile(handle);
		handle = nullptr;
		isOpen = false;
	}

	void DataFile::Write(byte* data, int64 length)
	{
		bool opened = true;
		if (!isOpen)
		{
			Open(OpenMode::Write);
			opened = true;
		}
		Clear();
		FileSystem::WriteFile(handle, data, length);
		if (opened)
		{
			Close();
		}
	}

	void DataFile::AddData(byte* data, int64 length)
	{
		FileSystem::WriteFile(handle, data, length);
	}

	void DataFile::CopyTo(const String& filepath)
	{
		int64 length;
		byte* data = Read(&length);
		HANDLE file = FileSystem::OpenFile(VFS::ResolvePhysicalPath(filepath, 0), OpenMode::Write, true, false);
		FileSystem::WriteFile(file, data, length);
		FileSystem::CloseFile(file);
	}

	void DataFile::Clear()
	{
		bool opened = false;
		if (isOpen)
		{
			opened = true;
			Close();
		}
		OpenInternal(OpenMode::Write, false);
		FileSystem::WriteTextFile(handle, "");
		if (!opened)
		{
			Close();
		}
	}

	byte* DataFile::Read(int64* outLength)
	{
		bool opened = false;
		if (!isOpen)
		{
			Open(OpenMode::Read);
			opened = true;
		}
		byte* data = FileSystem::ReadFile(handle, outLength);
		if (opened)
		{
			Close();
		}
		return data;
	}

	void DataFile::Read(void* buffer, int64 length)
	{
		bool opened = false;
		if (!isOpen)
		{
			Open(OpenMode::Read);
			opened = true;
		}
		FileSystem::ReadFile(handle, buffer, length);
		if (opened)
		{
			Close();
		}
	}

	void DataFile::Delete()
	{
		FileSystem::DeleteDataFile(physicalPath);
	}

}