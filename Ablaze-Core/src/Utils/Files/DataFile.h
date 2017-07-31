#pragma once
#include "Types.h"
#include "Enums.h"

namespace Ablaze
{

	class DataFile
	{
	protected:
		String physicalPath;
		FileType type;

	protected:
		DataFile(const String& physicalPath, FileType type);

	public:
		const String& GetPath() const;
		FileType GetType() const;

		virtual void Write(byte* data, int64 length);
		virtual void WriteTo(const String& filepath);
		virtual void WriteTo(const String& filepath, byte* data, int64 length);
		virtual void CopyTo(const String& filepath);

		virtual byte* Read(int64* outLength);
		virtual void Read(void* buffer, int64 length);

		virtual void Delete();

	};

}