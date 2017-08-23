#pragma once
#include "structs/Structs.h"
#include "Types.h"
#include "Resource.h"

namespace Ablaze
{

	class ModelFactory;
	class Font;

	namespace Internal
	{
		class WavefrontLoader;
	}

	class Model : public Resource
	{
	protected:
		VertexArray* vao;
		VertexBuffer* vbo;
		IndexBuffer* indexBuffer;
		maths::vec3 size;

	protected:
		Model(const String& name, VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, const maths::vec3& size);
		Model(const Model& other) = delete;

	public:
		~Model() override;

		VertexArray* GetVertexArray() const;
		VertexBuffer* GetVertexBuffer() const;
		IndexBuffer* GetIndexBuffer() const;
		const maths::vec3& GetSize() const;

		void SetVertexBuffer(VertexBuffer* vbo);
		void SetIndexBuffer(IndexBuffer* ibo);
		void SetColor(const Color& color);

		void Bind() const;
		void Unbind() const;

		friend class ModelFactory;
		friend class Font;
		friend class Internal::WavefrontLoader;
	};

}