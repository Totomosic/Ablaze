#include "DynamicTexture.h"
#include "Scene/SceneManager.h"

namespace Ablaze
{

	DynamicTexture::DynamicTexture(const String& name, int width, int height, UpdateMode creationMethod, GameObject* camera, LayerMask layers, TextureBuffer textureType) : Texture2D(name, width, height),
		mode(creationMethod), camera(camera), layers(layers), textureType(textureType)
	{
		hasBeenCreated = false;
		fbo = new Framebuffer(width, height, Color::Black(), false);
		if (textureType == TextureBuffer::Color)
		{
			fbo->CreateColorBufferTexture(this);
			fbo->CreateDepthBufferTexture();
		}
		else
		{
			fbo->CreateDepthBufferTexture(this);
			fbo->CreateColorBufferTexture(Attachment::Color0);
		}
	}

	DynamicTexture::~DynamicTexture()
	{
		delete fbo;
		Texture2D::~Texture2D();
	}

	GLint DynamicTexture::Bind()
	{
		return Texture2D::Bind();
	}

	GLint DynamicTexture::Unbind()
	{
		return Texture2D::Unbind();
	}

	UpdateMode DynamicTexture::GetCreationMode() const
	{
		return mode;
	}

	GameObject* DynamicTexture::GetCamera() const
	{
		return camera;
	}

	const Framebuffer* const DynamicTexture::GetFramebuffer() const
	{
		return fbo;
	}

	const LayerMask& DynamicTexture::GetLayerMask() const
	{
		return layers;
	}

	void DynamicTexture::SetCamera(GameObject* camera)
	{
		this->camera = camera;
		if (mode == UpdateMode::CreateOnce)
		{
			hasBeenCreated = false;
		}
	}

	void DynamicTexture::Create()
	{
		if ((mode == UpdateMode::CreateOnce && !hasBeenCreated) || mode == UpdateMode::CreateEachFrame)
		{
			BindFBO();
			std::vector<Layer*> layerVector = SceneManager::CurrentScene()->GetLayers(layers.mask);
			for (Layer* layer : layerVector)
			{
				GameObject* originalCamera = layer->GetCamera();
				layer->SetCamera(camera);
				layer->Render();
				layer->SetCamera(originalCamera);
			}
		}
	}

	void DynamicTexture::BindFBO()
	{
		fbo->Bind();
		fbo->Clear();
	}

	void DynamicTexture::UnbindFBO()
	{
		fbo->Unbind();
	}

}