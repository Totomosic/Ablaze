#pragma once
#include "AblazeGL.h"
#include "Types.h"
#include "Log.h"

namespace Ablaze
{

	struct BufferElement
	{
		String name;
		uint type;
		uint size;
		uint count;
		uint offset;
		bool normalized;
	};

	class BufferLayout
	{
	private:
		std::unordered_map<String, int> indices;
		std::vector<BufferElement> elements;
		uint size;

	public:
		BufferLayout();

		inline const std::vector<BufferElement>& GetLayout() const { return elements; }
		inline uint GetStride() const { return size; }
		inline const BufferElement& GetElement(const String& elementName) const { return elements[indices.at(elementName)]; }
		inline int GetIndexOf(const String& elementName) const { return indices.at(elementName); }
		inline int GetOffsetOf(const String& elementName) const { return GetElement(elementName).offset; }

		template<class T>
		void Push(const String& name, bool normalized = false)
		{
			AB_FATAL("Unknown type specified: " + String(typeid(T).name()));
		}

		template<>
		void Push<float>(const String& name, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(GLfloat), 1, normalized);
		}

		template<>
		void Push<int>(const String& name, bool normalized)
		{
			Push(name, GL_INT, sizeof(GLint), 1, normalized);
		}

		template<>
		void Push<maths::vec2>(const String& name, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(GLfloat), 2, normalized);
		}

		template<>
		void Push<maths::vec3>(const String& name, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(GLfloat), 3, normalized);
		}

		template<>
		void Push<maths::vec4>(const String& name, bool normalized)
		{
			Push(name, GL_FLOAT, sizeof(GLfloat), 4, normalized);
		}

		template<>
		void Push<Color>(const String& name, bool normalized)
		{
			Push<maths::vec4>(name, normalized);
		}

		static BufferLayout Vertex();

	private:
		void Push(const String& name, uint type, uint size, uint count, bool normalized);

	};

}