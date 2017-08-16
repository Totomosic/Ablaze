#pragma once
#include "../Component.h"
#include <functional>

namespace Ablaze
{
	namespace Components
	{

		class Clickable : public Component
		{
		private:
			std::vector<std::function<void(const Clickable*)>> callbacks;

		public:
			Clickable();
			Clickable(const std::function<void(const Clickable*)>& callback);

			const std::vector<std::function<void(const Clickable*)>>& GetCallbacks() const;

			void PushCallback(const std::function<void(const Clickable*)>& callback);
			void Trigger() const;

		};

	}
}