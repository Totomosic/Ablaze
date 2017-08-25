#include "Resource.h"

namespace Ablaze
{

	template<typename T>
	Resource<T>::Resource(T* resourcePtr)
		: m_ResourcePtr(resourcePtr)
	{
		
	}

	template<typename T>
	Resource<T>::~Resource()
	{
	
	}

	template<typename T>
	T* Resource<T>::Get() const
	{
		return m_ResourcePtr;
	}

	template<typename T>
	T* Resource<T>::operator*() const
	{
		return Get();
	}

	template<typename T>
	String Resource<T>::ToString() const
	{
		return String("Resource: ") + (typeid(T).name());
	}

	template class Resource<Texture>;
	template class Resource<Model>;
	template class Resource<Font>;
	template class Resource<Shader>;
	template class Resource<Asset>;

}