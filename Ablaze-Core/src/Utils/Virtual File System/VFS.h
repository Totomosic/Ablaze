#pragma once
#include <map>
#include <vector>
#include "Types.h"
#include "FileSystem.h"

#include "Utils\Files\TextFile.h"
#include "Utils\Funcs.h"

namespace Ablaze
{

	class VFS
	{
	private:
		static std::unordered_map<String, std::vector<String>*> m_MountPoints;

	public:
		static void Mount(const String& virtualPath, const String& physicalPath);

		static bool ResolvePhysicalPath(const String& path, String& outPhysPath, int pathIndex = -1);
		static String ResolvePhysicalPath(const String& path, int pathIndex = -1);

		static bool FileExists(const String& path);
		static int64 GetFileSize(const String& path);
		static int64 GetFileSize(const DataFile* const file);

		static TextFile* CreateTextFile(const String& path);
		static TextFile* RetrieveTextFile(const String& path);
		static TextFile* WriteTextFile(const String& path, const String& data);

		template<class File> static File* RetrieveFile(const String& path)
		{
			return new File(ResolvePhysicalPath(path));
		}

		template<class File> static File* CreateNewFile(const String& path, int pathIndex = 0)
		{
			return new File(ResolvePhysicalPath(path, pathIndex));
		}

	private:
		static bool ContainsVPath(const String& virtualPath);

	};

}