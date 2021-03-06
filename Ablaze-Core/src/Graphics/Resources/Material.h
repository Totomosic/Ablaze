#pragma once
#include "Types.h"
#include "Resource.h"
#include "Graphics/Resources/Shaders/Shader.h"
#include "Graphics/Resources/Imaging/Textures/Texture.h"
#include "Graphics/Resources/Shaders/Uniforms/UniformManager.h"
#include "Graphics/Resources/Imaging/Textures/TextureSet.h"

namespace Ablaze
{

	class MaterialFactory;

	class Material : public Resource
	{
	protected:
		Color diffuseColor;
		const Shader* shader;
		bool depthState;
		bool blendState;
		GLenum depthFunction;
		GLenum srcBlendState;
		GLenum dstBlendState;
		TextureSet textures;
		UniformManager uniforms;

	protected:
		Material(const String& name, const Color& color, const Shader* const shader, const TextureSet& textures, bool depthState, bool blendState, GLenum depthFunc, GLenum srcBlendState, GLenum dstBlendState);
		Material(const String& name, const Color& color, const Shader* const shader, const String& sampler, Texture* texture, bool depthState, bool blendState, GLenum depthFunc, GLenum srcBlendState, GLenum dstBlendState);
		Material();

	public:
		~Material() override;

		const Color& GetColor() const;
		const Shader* const GetShader() const;
		Texture* GetTexture(int index = 0) const;
		bool GetDepthState() const;
		bool GetBlendState() const;		
		GLenum GetDepthFunc() const;
		GLenum GetSrcBlend() const;
		GLenum GetDstBlend() const;
		bool HasTransparency() const;
		bool HasTextures() const;

		void AddTexture(const String& sampler, Texture* texture);
		const TextureSet& GetAllTextures() const;

		void AddUniformFloat(const String& varname, float value);
		void AddUniformVec2(const String& varname, const maths::vec2& value);
		void AddUniformVec3(const String& varname, const maths::vec3& value);
		void AddUniformVec4(const String& varname, const maths::vec4& value);
		void AddUniformColor(const String& varname, const Color& value);
		void AddUniformMat4(const String& varname, const maths::mat4& value);

		void SetColor(const Color& color);
		void SetShader(const Shader* const shader);
		void SetDepthState(bool depthEnabled);
		void SetBlendState(bool blendEnabled);
		void SetDepthFunc(GLenum func);
		void SetSrcBlend(GLenum src);
		void SetDstBlend(GLenum dst);

		virtual void ApplyMaterial() const;

		friend class MaterialFactory;

	};

}