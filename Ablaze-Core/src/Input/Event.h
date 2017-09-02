#pragma once
#include "EventArgs.h"
#include <functional>

namespace Ablaze
{

	class Event : public Object
	{
	protected:
		using Fn = void(*)(void*, const Event&);
		std::vector<std::pair<Fn, void*>> targets;

		template<class C, void(C::*M)(const Event&)>
		static void Invoke(void *instance, const Event& e)
		{
			(static_cast<C*>(instance)->*M)(e);
		}

	public:
		Event()
		{
		
		}

		template<class C, void(C::*M)(const Event&)>
		void Subscribe(C* const instance)
		{
			auto pair = std::make_pair(&Invoke<C, M>, instance);
			targets.push_back(pair);
		}

		void Trigger()
		{
			for (auto pair : targets) {
				(pair.first)(pair.second, *this);
			}
		}

		String ToString() const override
		{
			return "Event";
		}

	};

}