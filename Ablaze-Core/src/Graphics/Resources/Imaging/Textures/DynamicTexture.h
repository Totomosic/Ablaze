#pragma once
#include "Texture.h"
#include "Graphics/Resources/Imaging/Framebuffers/Framebuffer.h"
#include "Entities/GameObject.h"
#include "Scene/LayerMask.h"

namespace Ablaze
{

	enum class UpdateMode
	{
		CreateOnce, CreateEachFrame
	};

	enum class TextureBuffer
	{
		Color, Depth
	};

	class DynamicTexture : public Texture2D
	{
	private:
		Framebuffer* fbo;
		UpdateMode mode;
		TextureBuffer textureType;
		GameObject* camera;
		LayerMask layers;
		bool hasBeenCreated;

	public:
		explicit DynamicTexture(const String& name, int width, int height, UpdateMode creationMethod, LayerMask layers, GameObject* camera = nullptr, TextureBuffer textureType = TextureBuffer::Color);
		~DynamicTexture();

		GLint Bind() override;
		GLint Unbind() override;
		GameObject* GetCamera() const;
		const LayerMask& GetLayerMask() const;
		UpdateMode GetCreationMode() const;
		const Framebuffer* const GetFramebuffer() const;

		void SetCamera(GameObject* camera);
		void Create();

	private:
		void BindFBO();
		void UnbindFBO();

	};

}