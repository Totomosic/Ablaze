#pragma once
#include "Types.h"
#include <Windows.h>

namespace Ablaze
{

	enum class OpenMode;

	class FileSystem
	{
	public:
		static bool FileExists(const String& path);
		static int64 GetFileSize(HANDLE handle);

		static byte* ReadFile(HANDLE handle, int64* length);
		static bool ReadFile(HANDLE handle, void* buffer, int64 size = -1);
		static String ReadTextFile(HANDLE handle);

		static bool WriteFile(HANDLE handle, byte* buffer, int64 length);
		static bool WriteTextFile(HANDLE handle, const String& text);

		static HANDLE OpenFile(const String& path, OpenMode mode, bool createNewFile, bool appendData);
		static void CloseFile(HANDLE handle);

		static void DeleteDataFile(const String& path);
	};

}