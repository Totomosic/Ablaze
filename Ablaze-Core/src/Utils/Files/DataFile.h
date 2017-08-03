#pragma once
#include "Types.h"
#include "Enums.h"
#include "Log.h"

namespace Ablaze
{

	enum class OpenMode
	{
		Read, Write
	};

	class DataFile
	{
	protected:
		String physicalPath;
		FileType type;
		HANDLE handle;
		bool isOpen;

	protected:
		DataFile(const String& physicalPath, FileType type);

		HANDLE OpenInternal(OpenMode mode, bool clearFile);

	public:
		const String& GetPath() const;
		FileType GetType() const;
		bool IsOpen() const;
		HANDLE GetHandle() const;

		virtual HANDLE Open(OpenMode openMode);
		virtual void Close();

		virtual void Write(byte* data, int64 length);
		virtual void AddData(byte* data, int64 length);
		virtual void CopyTo(const String& filepath);
		virtual void Clear();

		virtual byte* Read(int64* outLength);
		virtual void Read(void* buffer, int64 length);

		virtual void Delete();

	};

}