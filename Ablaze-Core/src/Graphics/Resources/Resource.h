#pragma once
#include "Types.h"
#include "Object.h"

namespace Ablaze
{
	
	class Texture;
	class Model;
	class Shader;
	class Asset;
	class Font;

	template<typename T>
	class Resource : public Object
	{
	private:
		T* m_ResourcePtr;

	public:
		Resource(T* resourcePtr);
		~Resource();

		T* Get() const;
		T* operator*() const;

		String ToString() const override;

	};

}