#pragma once
#include "Types.h"
#include "Layer.h"

namespace Ablaze
{

	struct LayerMask
	{
	public:
		int64 mask;

	public:
		LayerMask();
		LayerMask(int64 mask);
		LayerMask(const String& layer);
		LayerMask(const String& layer0, const String& layer1);
		LayerMask(const String& layer0, const String& layer1, const String& layer2);

		void AddLayer(const String& layer);
		void AddLayer(Layer* layer);

		static LayerMask All();
	};

}