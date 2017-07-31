#include "FileSystem.h"
#include "Log.h"

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

	int64 FileSystem::GetFileSize(const String& path)
	{
		HANDLE file = OpenFileForReading(path);
		if (file == INVALID_HANDLE_VALUE)
			return -1;
		int64 result = GetFileSizeInternal(file);
		CloseHandle(file);
		return result;
	}

	bool FileSystem::ReadFile(const String& path, void* buffer, int64 size)
	{
		HANDLE file = OpenFileForReading(path);
		if (file == INVALID_HANDLE_VALUE)
			return false;

		if (size < 0)
			size = GetFileSizeInternal(file);

		bool result = ReadFileInternal(file, buffer, size);
		CloseHandle(file);
		return result;
	}

	byte* FileSystem::ReadFile(const String& path, int64* length)
	{
		HANDLE file = OpenFileForReading(path);
		int64 size = GetFileSizeInternal(file);
		*length = size;
		byte* buffer = new byte[size];
		bool result = ReadFileInternal(file, buffer, size);
		CloseHandle(file);
		if (!result)
			delete buffer;
		return result ? buffer : nullptr;
	}

	String FileSystem::ReadTextFile(const String& path)
	{
		HANDLE file = OpenFileForReading(path);
		int64 size = GetFileSizeInternal(file);
		String result(size, 0);
		bool success = ReadFileInternal(file, &result[0], size);
		CloseHandle(file);
		if (success)
		{
			// Strip carriage returns
			result.erase(std::remove(result.begin(), result.end(), '\r'), result.end());
		}
		return success ? result : String();
	}

	bool FileSystem::WriteFile(const String& path, byte* buffer, int64 length, bool overrideFile)
	{
		HANDLE file = CreateFile(path.c_str(), (overrideFile) ? GENERIC_WRITE : FILE_APPEND_DATA, 0, NULL, (overrideFile) ? CREATE_ALWAYS : OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file == INVALID_HANDLE_VALUE)
		{
			AB_WARN("Failed to write file: " + path + ". With error: " + std::to_string(GetLastError()));
			return false;
		}

		//int64 size = GetFileSizeInternal(file);
		DWORD written;
		bool result = ::WriteFile(file, buffer, length, &written, NULL);
		CloseHandle(file);
		if (!result)
		{
			AB_WARN("Failed to write file: " + path + ". With error: " + std::to_string(GetLastError()));
		}
		return result;
	}

	bool FileSystem::WriteTextFile(const String& path, const String& text, bool overrideFile)
	{
		return WriteFile(path, (byte*)&text[0], text.length(), overrideFile);
	}

	void FileSystem::DeleteDataFile(const String& path)
	{
		DeleteFile(path.c_str());
	}

}