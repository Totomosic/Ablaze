#pragma once
#include "Texture.h"
#include "Graphics/Resources/Imaging/Framebuffers/Framebuffer.h"
#include "Entities/GameObject.h"
#include "Scene/LayerMask.h"
#include "Graphics/Resources/Shaders/Uniforms/UniformManager.h"
#include "Graphics/Resources/Shaders/ShaderManager.h"

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
		UniformManager uniforms;
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
		UniformManager& GetUniforms();

		void SetCamera(GameObject* camera);
		void SetClearColor(const Color& color);
		void Create();

	private:
		void BindFBO();
		void UnbindFBO();

	};

}