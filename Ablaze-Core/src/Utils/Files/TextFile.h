#pragma once
#include "DataFile.h"

namespace Ablaze
{

	class VFS;

	class TextFile : public DataFile
	{
	private:

	protected:
		TextFile(const String& filepath);
		TextFile(const String& filepath, const String& data);

	public:
		void Write(const String& data) const;
		void WriteTo(const String& filepath, const String& data) const;
		void WriteLine(const String& line) const;
		String Read() const;

		friend class VFS;
	};

}