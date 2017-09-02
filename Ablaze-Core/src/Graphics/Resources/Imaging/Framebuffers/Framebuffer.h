#pragma once
#include "Factories/TextureFactory.h"
#include "Graphics/Viewport.h"
#include "Enums.h"

namespace Ablaze
{

	class Framebuffer
	{
	private:
		static const Framebuffer* currentlyBound;

		GLuint id;
		Viewport viewport;
		Color clearColor;
		std::unordered_map<Attachment, Texture2D*> textures;

	private:
		Framebuffer(int width, int height, bool window);

	public:
		Framebuffer(int width, int height, const Color& clearColor = Color::Black(), bool create = true);
		~Framebuffer();

		void Bind() const;
		void Unbind() const;
		void Clear(ClearBuffer buffer = ClearBuffer::Color | ClearBuffer::Depth) const;
		const Viewport& GetViewport() const;

		int GetWidth() const;
		int GetHeight() const;
		GLuint GetID() const;
		const Color& GetClearColor() const;

		void SetWidth(int width);
		void SetHeight(int height);
		void SetClearColor(const Color& color);

		void CopyToScreen(ClearBuffer buffer = ClearBuffer::Color | ClearBuffer::Depth) const;

		Texture2D* CreateColorBufferTexture(Attachment attachment = Attachment::Color0);
		Texture2D* CreateColorBufferTexture(Texture2D* texture, Attachment attachment = Attachment::Color0);
		Texture2D* CreateDepthBufferTexture();
		Texture2D* CreateDepthBufferTexture(Texture2D* texture);
		Texture2D* GetTextureAttachment(Attachment attachment = Attachment::Color0);

		bool CheckFramebufferCompleteness() const;

		static Framebuffer* Screen(int width, int height);
		static const Framebuffer* const GetCurrentlyBound();

	private:
		void Create();

	};

}