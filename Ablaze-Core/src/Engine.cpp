#include "Engine.h"
#include "Log.h"
#include "Entities\GameObject.h"
#include "Graphics\Textures\TextureManager.h"

namespace Ablaze
{

	uint AblazeEngine::maxEntities = 100000;

	void AblazeEngine::Init()
	{
		GLint result = glewInit();
		if (result != GLEW_OK)
		{			
			AB_FATAL("Unable to init GLEW");
		}

		Random::Initialise();
		GameObject::Initialise();
		TextureManager::Initialise();
	}

	void AblazeEngine::Terminate()
	{
		glfwTerminate();
	}

}