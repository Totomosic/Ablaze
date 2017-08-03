#include "VFS.h"
#include "Log.h"

namespace Ablaze
{

	std::unordered_map<String, std::vector<String>*> VFS::m_MountPoints = std::unordered_map<String, std::vector<String>*>();

	void VFS::Mount(const String& virtualPath, const String& physicalPath)
	{
		if (ContainsVPath(virtualPath))
		{
			m_MountPoints[virtualPath]->push_back(physicalPath);
		}
		else
		{
			m_MountPoints[virtualPath] = new std::vector<String>();
			m_MountPoints[virtualPath]->push_back(physicalPath);
		}
	}

	bool VFS::ResolvePhysicalPath(const String& virtualPath, String& outPPath, int pathIndex)
	{
		if (virtualPath.front() == '/')
		{
			std::vector<String> dirs = Utils::SplitString(virtualPath, "/");
			String dir = dirs.front();
			if (ContainsVPath(dir) && dirs.size() == 2)
			{
				if (pathIndex == -1)
				{
					for (String physPath : *(m_MountPoints[dir]))
					{
						String suggestedPath = physPath + dirs[1];
						if (FileSystem::FileExists(suggestedPath))
						{
							outPPath = suggestedPath;
							return true;
						}
					}
					AB_ERROR("Unabled to find file: " + virtualPath);
					return false;
				}
				else
				{
					outPPath = (*(m_MountPoints[dir]))[pathIndex] + dirs[1];
					return true;
				}
			}
			return false;
		}
		else
		{
			// Not a virtual path so return path
			AB_INFO("VFS received a path that was not recognised as virtual: '" + virtualPath + "', if you wish to use a virtual path, prefix path with /. Eg. '/res/texture.png'");
			outPPath = virtualPath;
			return true;
		}
	}

	String VFS::ResolvePhysicalPath(const String& virtualPath, int pathIndex)
	{
		String s = "Not Found";
		ResolvePhysicalPath(virtualPath, s, pathIndex);
		return s;
	}

	bool VFS::FileExists(const String& virtualPath)
	{
		String temp;
		return ResolvePhysicalPath(virtualPath, temp);
	}

	int64 VFS::GetFileSize(const String& path)
	{
		HANDLE file = FileSystem::OpenFile(path, OpenMode::Read, false, false);
		int64 val = FileSystem::GetFileSize(file);
		FileSystem::CloseFile(file);
		return val;
	}

	int64 VFS::GetFileSize(const DataFile* const file)
	{
		return FileSystem::GetFileSize(file->GetHandle());
	}

	TextFile* VFS::RetrieveTextFile(const String& path)
	{
		return RetrieveFile<TextFile>(path);
	}

	TextFile* VFS::CreateTextFile(const String& path)
	{
		return CreateNewFile<TextFile>(path);
	}

	TextFile* VFS::WriteTextFile(const String& path, const String& data)
	{
		TextFile* file = CreateTextFile(path);
		file->Write(data);
		return file;
	}

	bool VFS::ContainsVPath(const String& virtualPath)
	{
		return m_MountPoints.find(virtualPath) != m_MountPoints.end();
	}
}