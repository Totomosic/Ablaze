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

	public:
		void Write(const String& data);
		void WriteLine(const String& line);
		String Read() const;

		friend class VFS;
	};

}