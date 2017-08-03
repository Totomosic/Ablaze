#pragma once
#include "structs/Structs.h"
#include "Types.h"

namespace Ablaze
{

	class ModelFactory;
	class Font;

	namespace Internal
	{
		class WavefrontLoader;
	}

	class Model
	{
	protected:
		String name;
		VAO* vao;
		VBO* vbo;
		IndexBuffer* indexBuffer;
		maths::vec3 size;

	protected:
		Model(const String& name, VBO* vertexBuffer, IndexBuffer* indexBuffer, const maths::vec3& size);
		Model(const Model& other) = delete;

	public:
		virtual ~Model();

		const String& GetName() const;
		VAO* GetVAO() const;
		VBO* GetVBO() const;
		IndexBuffer* GetIndexBuffer() const;
		const maths::vec3& GetSize() const;

		void SetVBO(VBO* vbo);
		void SetIndexBuffer(IndexBuffer* ibo);

		void Bind() const;
		void Unbind() const;

		friend class ModelFactory;
		friend class Font;
		friend class Internal::WavefrontLoader;
	};

}