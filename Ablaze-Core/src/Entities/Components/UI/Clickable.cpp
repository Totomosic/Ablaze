#include "Clickable.h"

namespace Ablaze
{
	namespace Components
	{

		Clickable::Clickable()
		{
		
		}

		Clickable::Clickable(const std::function<void(const Clickable*)>& callback) : Clickable()
		{
			PushCallback(callback);
		}

		const std::vector<std::function<void(const Clickable*)>>& Clickable::GetCallbacks() const
		{
			return callbacks;
		}

		void Clickable::PushCallback(const std::function<void(const Clickable*)>& callback)
		{
			callbacks.push_back(callback);
		}

		void Clickable::Trigger() const
		{
			for (auto function : callbacks)
			{
				function(this);
			}
		}

	}
}