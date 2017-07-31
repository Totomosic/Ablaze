#pragma once
#include "Types.h"
#include <fstream>
#include <Windows.h>

namespace Ablaze
{

	class FileSystem
	{
	public:
		static bool FileExists(const String& path);
		static int64 GetFileSize(const String& path);

		static byte* ReadFile(const String& path, int64* length);
		static bool ReadFile(const String& path, void* buffer, int64 size = -1);
		static String ReadTextFile(const String& path);

		static bool WriteFile(const String& path, byte* buffer, int64 length, bool overrideFile = true);
		static bool WriteTextFile(const String& path, const String& text, bool overrideFile = true);

		static void DeleteDataFile(const String& path);
	};

}