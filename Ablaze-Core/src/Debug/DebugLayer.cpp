#include "DebugLayer.h"
#include "Scene/Scene.h"
#include "Entities/Camera.h"
#include "RenderEngine/Interfaces/Renderer.h"
#include "Graphics/Context.h"
#include "RenderEngine/structs/Commands/Commands.h"

namespace Ablaze
{

	void DebugLayer::Enable()
	{
		enabled = true;
		debugLayer = new Layer("_DEBUG_LAYER_", new Renderer(), new Camera(Context::Window()->GetViewport(), maths::vec3(), maths::mat4::Identity(), Projection::Orthographic, 1, Angle::Radians, -100, 100));
	}

	void DebugLayer::Disable()
	{
		enabled = false;
	}

	void DebugLayer::RenderTexture(Texture* const texture, const maths::vec2& position, const maths::vec2& size)
	{
		Renderable* rectangle = new Renderable(nullptr, maths::mat4::Translation(maths::vec3(position, 0)));
		debugLayer->GetRenderer()->PushCommand(new RenderCommand(rectangle));
		Camera* camera = (Camera*)debugLayer->GetCamera();
		debugLayer->GetRenderer()->Execute(camera->ViewMatrix(), camera->ProjectionMatrix());
	}

}