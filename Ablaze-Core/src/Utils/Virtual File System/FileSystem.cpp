#include "FileSystem.h"
#include "Log.h"
#include "Utils/Files/DataFile.h"

namespace Ablaze
{

	void CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped)
	{
	}

	static HANDLE OpenFileForReading(const String& path)
	{
		return CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
	}

	static int64 GetFileSizeInternal(HANDLE file)
	{
		LARGE_INTEGER size;
		GetFileSizeEx(file, &size);
		return size.QuadPart;
	}

	static bool ReadFileInternal(HANDLE file, void* buffer, int64 size)
	{
		OVERLAPPED ol = { 0 };
		return ReadFileEx(file, buffer, size, &ol, FileIOCompletionRoutine);
	}

	bool FileSystem::FileExists(const String& path)
	{
		DWORD result = GetFileAttributes(path.c_str());
		return !(result == INVALID_FILE_ATTRIBUTES && GetLastError() == ERROR_FILE_NOT_FOUND);
	}

	int64 FileSystem::GetFileSize(HANDLE handle)
	{
		if (handle == INVALID_HANDLE_VALUE)
			return -1;
		int64 result = GetFileSizeInternal(handle);
		return result;
	}

	bool FileSystem::ReadFile(HANDLE handle, void* buffer, int64 size)
	{
		if (handle == INVALID_HANDLE_VALUE)
			return false;

		if (size < 0)
			size = GetFileSizeInternal(handle);

		bool result = ReadFileInternal(handle, buffer, size);
		return result;
	}

	byte* FileSystem::ReadFile(HANDLE handle, int64* length)
	{
		int64 size = GetFileSizeInternal(handle);
		*length = size;
		byte* buffer = new byte[size];
		bool result = ReadFileInternal(handle, buffer, size);
		if (!result)
			delete buffer;
		return result ? buffer : nullptr;
	}

	String FileSystem::ReadTextFile(HANDLE handle)
	{
		int64 size = GetFileSizeInternal(handle);
		String result(size, 0);
		bool success = ReadFileInternal(handle, &result[0], size);
		if (success)
		{
			// Strip carriage returns
			result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
		}
		return success ? result : String();
	}

	bool FileSystem::WriteFile(HANDLE handle, byte* buffer, int64 length)
	{
		if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
		{
			AB_WARN("Failed to write to unopened file");
			return false;
		}

		DWORD written;
		bool result = ::WriteFile(handle, buffer, length, &written, NULL);
		return result;
	}

	bool FileSystem::WriteTextFile(HANDLE handle, const String& text)
	{
		return WriteFile(handle, (byte*)&text[0], text.length());
	}

	HANDLE FileSystem::OpenFile(const String& path, OpenMode mode, bool clearFile, bool appendData)
	{
		if (mode == OpenMode::Write)
		{
			HANDLE file = CreateFile(path.c_str(), (appendData) ? GENERIC_WRITE : FILE_APPEND_DATA, 0, NULL, (clearFile) ? CREATE_ALWAYS : OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (file == INVALID_HANDLE_VALUE)
			{
				AB_WARN("Failed to open file: " + path + ". With error: " + std::to_string(GetLastError()));
			}
			return file;
		}
		else if (mode == OpenMode::Read)
		{
			HANDLE file = OpenFileForReading(path);
			if (file == INVALID_HANDLE_VALUE)
			{
				AB_WARN("Failed to open file: " + path + ". With error: " + std::to_string(GetLastError()));
			}
			return file;
		}
		return nullptr;
	}

	void FileSystem::CloseFile(HANDLE handle)
	{
		CloseHandle(handle);
	}

	void FileSystem::DeleteDataFile(const String& path)
	{
		DeleteFile(path.c_str());
	}

}