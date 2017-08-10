#pragma once
#include "Viewport.h"
#include "Maths/Maths.h"
#include "Types.h"
#include "Enums.h"
#include "Imaging/Framebuffers/Framebuffer.h"

namespace Ablaze
{

	class Window
	{
	private:
		GLFWwindow *window;
		maths::vec2 position;
		String title;
		Framebuffer* framebuffer;

	public:
		Window(int width, int height, String title, const Color& clearColor = Color(0, 0, 0, 0));
		Window();

		int GetWidth() const;
		int GetHeight() const;
		const String& GetTitle() const;
		const Color& GetClearColor() const;
		GLFWwindow* GetWindowPtr() const;
		const Framebuffer* GetFramebuffer() const;
		const Viewport& GetViewport() const;

		void SetWidth(int w);
		void SetHeight(int h);
		void SetSize(const maths::vec2& size);
		void SetTitle(const String& title);
		void SetClearColor(Color clearColor);

		bool ShouldClose() const;

		void Clear(GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) const;
		void SwapBuffers() const;
		void Update();

		static void SetHint(int hintName, int value);

	private:
		void Load(int width, int height, const Color& clearColor);
		void SetContext();
		static void Reshape(GLFWwindow* window, int width, int height);
		static void ErrorCallback(int code, const char* error);
	};

}