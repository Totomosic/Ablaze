#include "DebugLayer.h"
#include "Scene/Scene.h"
#include "Graphics/Context.h"
#include "AblazeGL.h"

namespace Ablaze
{

	Shader* DebugLayer::textureShader = nullptr;

	void DebugLayer::Initialise()
	{
		String vData =
#include "Shaders/DebugTexture_v.glsl"
			;
		String fData =
#include "Shaders/DebugTexture_f.glsl"
			;
		textureShader = Shader::FromSource("_DEBUG_TEXTURE_SHADER_", vData, fData);
		textureShader->Enable();
		textureShader->SetUniform("viewMatrix", maths::mat4::Identity());
		textureShader->SetUniform("projectionMatrix", maths::mat4::Orthographic(0, Context::Window()->GetWidth(), -Context::Window()->GetHeight(), 0, -100, 100));
	}

	void DebugLayer::RenderTexture(Texture* const texture, const maths::vec2& position, const maths::vec2& size)
	{
		// replace with opengl code, make friend of rectangle class.
		Rectangle* rect = new Rectangle("", size, Color::White());
		textureShader->Enable();
		textureShader->SetUniform("modelMatrix", maths::mat4::Translation(maths::vec3(position * maths::vec2(1, -1), 0)));

		glDisable(GL_DEPTH_TEST);
		textureShader->SetTexture(*texture, "tex");
		rect->Bind();
		glDrawElements(rect->GetVertexArray()->GetPrimitiveType(), rect->GetVertexArray()->GetRenderCount(), GL_UNSIGNED_INT, nullptr);

		delete rect;
	}

}