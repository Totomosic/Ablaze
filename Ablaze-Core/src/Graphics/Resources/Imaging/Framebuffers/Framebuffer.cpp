#include "Framebuffer.h"
#include "Graphics/Context.h"
#include "Log.h"

namespace Ablaze
{

	const Framebuffer* Framebuffer::currentlyBound = nullptr;

	Framebuffer::Framebuffer(int width, int height, bool window)
		: viewport(Viewport(0, 0, width, height))
	{
		id = 0;
	}

	Framebuffer::Framebuffer(int width, int height, const Color& clearColor, bool create)
		: viewport(Viewport(0, 0, width, height)), clearColor(clearColor)
	{
		Create();
		if (create)
		{
			CreateColorBufferTexture(Attachment::Color0);
			CreateDepthBufferTexture();
		}
	}

	Framebuffer::~Framebuffer()
	{
		for (auto pair : textures)
		{
			delete pair.second;
		}
		glDeleteFramebuffers(1, &id);
	}

	void Framebuffer::Bind() const
	{
		if (currentlyBound != this)
		{
			viewport.Bind();
			glBindFramebuffer(GL_FRAMEBUFFER, id);
			currentlyBound = this;
		}
	}

	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		currentlyBound = nullptr;
	}

	void Framebuffer::Clear(ClearBuffer buffer) const
	{
		Bind();
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear((GLbitfield)buffer);
	}

	const Viewport& Framebuffer::GetViewport() const
	{
		return viewport;
	}

	int Framebuffer::GetWidth() const
	{
		return viewport.GetWidth();
	}

	int Framebuffer::GetHeight() const
	{
		return viewport.GetHeight();
	}

	GLuint Framebuffer::GetID() const
	{
		return id;
	}

	const Color& Framebuffer::GetClearColor() const
	{
		return clearColor;
	}

	void Framebuffer::SetWidth(int width)
	{
		viewport.SetWidth(width);
	}

	void Framebuffer::SetHeight(int height)
	{
		viewport.SetHeight(height);
	}

	void Framebuffer::SetClearColor(const Color& color)
	{
		clearColor = color;
	}

	void Framebuffer::CopyToScreen(ClearBuffer buffer) const
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glBlitFramebuffer(0, 0, GetWidth(), GetHeight(), 0, 0, Context::Window()->GetWidth(), Context::Window()->GetHeight(), (GLbitfield)buffer, GL_NEAREST);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	Texture2D* Framebuffer::CreateColorBufferTexture(Attachment attachment)
	{
		return CreateColorBufferTexture(new Texture2D("_FRAMEBUFFER_COLOR_BUFFER_TEXTURE_ATTACH_", GetWidth(), GetHeight()), attachment);		
	}

	Texture2D* Framebuffer::CreateColorBufferTexture(Texture2D* texture, Attachment attachment)
	{
		Bind();
		texture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->GetWidth(), texture->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		texture->SetTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		texture->SetTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture->SetTextureParameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
		texture->SetTextureParameter(GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_FRAMEBUFFER, (GLenum)attachment, GL_TEXTURE_2D, texture->GetID(), 0);
		glDrawBuffer((GLenum)attachment);
		textures[attachment] = texture;
		return texture;
	}

	Texture2D* Framebuffer::CreateDepthBufferTexture()
	{
		return CreateDepthBufferTexture(new Texture2D("_FRAMEBUFFER_DEPTH_BUFFER_TEXTURE_ATTACH_", GetWidth(), GetHeight()));		
	}

	Texture2D* Framebuffer::CreateDepthBufferTexture(Texture2D* texture)
	{
		Bind();
		texture->Bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, texture->GetWidth(), texture->GetHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
		texture->SetTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		texture->SetTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		texture->SetTextureParameter(GL_TEXTURE_WRAP_S, GL_CLAMP);
		texture->SetTextureParameter(GL_TEXTURE_WRAP_T, GL_CLAMP);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0);
		textures[Attachment::Depth0] = texture;
		return texture;
	}

	Texture2D* Framebuffer::GetTextureAttachment(Attachment attachment)
	{
		return textures[attachment];
	}

	bool Framebuffer::CheckFramebufferCompleteness() const
	{
		Bind();
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			AB_ERROR("Framebuffer is not complete with error: " + std::to_string(status));
			return false;
		}
		return true;
	}

	Framebuffer* Framebuffer::Screen(int width, int height)
	{
		return new Framebuffer(width, height, true);
	}

	const Framebuffer* const Framebuffer::GetCurrentlyBound()
	{
		return currentlyBound;
	}

	void Framebuffer::Create()
	{
		glGenFramebuffers(1, &id);
	}

}