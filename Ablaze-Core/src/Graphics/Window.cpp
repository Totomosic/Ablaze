#include "Window.h"
#include "Context.h"

#include "Types.h"
#include "Input/Input.h"
#include "Log.h"
#include "Engine.h"

namespace Ablaze
{

	Window::Window(int width, int height, String title, const Color& clearColor)
	{
		this->title = title;
		framebuffer = nullptr;
		
		Load(width, height, clearColor);

		framebuffer = Framebuffer::Screen(width, height);
		framebuffer->SetClearColor(clearColor);
	}

	Window::Window() : Window(800, 600, "", Color(0, 0, 0))
	{
		
	}

	int Window::GetWidth() const
	{
		return framebuffer->GetWidth();
	}

	int Window::GetHeight() const
	{
		return framebuffer->GetHeight();
	}

	String Window::GetTitle() const
	{
		return title;
	}

	const Viewport& Window::GetViewport() const
	{
		return framebuffer->GetViewport();
	}

	const Color& Window::GetClearColor() const
	{
		return framebuffer->GetClearColor();
	}

	GLFWwindow* Window::GetWindowPtr() const
	{
		return window;
	}

	const Framebuffer* Window::GetFramebuffer() const
	{
		return framebuffer;
	}

	void Window::SetSize(const maths::vec2& size)
	{
		framebuffer->SetWidth(size.x);
		framebuffer->SetHeight(size.y);
		glfwSetWindowSize(window, size.x, size.y);
		framebuffer->GetViewport().Bind();
	}

	void Window::SetWidth(int width)
	{
		framebuffer->SetWidth(width);
		SetSize(maths::vec2(GetWidth(), GetHeight()));
	}

	void Window::SetHeight(int height)
	{
		framebuffer->SetHeight(height);
		SetSize(maths::vec2(GetWidth(), GetHeight()));
	}

	void Window::SetTitle(const String& title)
	{
		this->title = title;
		glfwSetWindowTitle(window, title.c_str());
	}

	void Window::SetClearColor(Color clearColor)
	{
		framebuffer->SetClearColor(clearColor);
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::Clear(GLbitfield mask) const
	{
		framebuffer->Clear(mask);
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(window);
	}

	void Window::Update()
	{
		Input::PollEvents();
		GLenum error = glGetError();
		if (error != GL_NO_ERROR)
		{
			AB_FATAL(String("OpenGL Error: ") + String((const char*)glewGetErrorString(error)) + String(" (") + std::to_string(error) + String(") "));
		}
	}

	void Window::Load(int width, int height, const Color& clearColor)
	{
		glfwSetErrorCallback(ErrorCallback);
		if (!glfwInit())
		{
			AB_FATAL("Unable to initialise GLFW");
		}
		glfwWindowHint(GLFW_SAMPLES, 4);
		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window)
		{
			AB_FATAL("Window initialisation failed");
		}		
		SetContext();
	}

	void Window::SetContext()
	{
		glfwMakeContextCurrent(window);
		Context::SetWindow(this);

		glfwSetFramebufferSizeCallback(window, Reshape);

		glfwSetMouseButtonCallback(window, Mouse::_MouseButtonCallback);
		glfwSetCursorPosCallback(window, Mouse::_MousePosCallback);
		glfwSetScrollCallback(window, Mouse::_MouseScrollCallback);
		glfwSetCursorEnterCallback(window, Mouse::_MouseEnteredCallback);
		glfwSetKeyCallback(window, Keyboard::_KeyboardKeyCallback);
		glfwSetCharCallback(window, Keyboard::_KeyboardCharCallback);
	}

	void Window::Reshape(GLFWwindow* window, int width, int height)
	{
		Context::Window()->SetSize(maths::vec2(width, height));
	}

	void Window::ErrorCallback(int code, const char* error)
	{
		AB_ERROR(error);
		AB_ERROR(code);
	}

}