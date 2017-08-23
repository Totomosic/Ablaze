#pragma once
#include "Types.h"
#include "Log.h"
#include "Graphics/Resources/Mesh.h"
#include "ModelFactory.h"
#include "MaterialFactory.h"
#include "FontFactory.h"

namespace Ablaze
{

	class MeshFactory
	{
	private:
		static std::unordered_map<String, std::pair<Mesh*, int>*> meshes;
		static uint unnamedCount;

	public:
		MeshFactory() { }

		static Mesh* Request(const String& meshName);
		static Mesh* Request(Mesh* mesh);
		static Mesh* RequestWeak(const String& meshName);
		static Mesh* RequestWeak(Mesh* mesh);
		static bool Release(const String& meshName);
		static bool Release(Mesh* mesh);

		static Mesh* Build(const String& meshName, Model* model, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* Build(const String& meshName, Model* model, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* Build(const String& meshName, const String& modelName, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* Build(const String& meshName, const String& modelName, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildRectangle(const String& meshName, const maths::vec2& size, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildRectangle(const String& meshName, const maths::vec2& size, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildCuboid(const String& meshName, const maths::vec3& size, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildCuboid(const String& meshName, const maths::vec3& size, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildText(const String& textName, const String& text, Font* font, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildText(const String& textName, const String& text, Font* font, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildText(const String& textName, const String& text, const String& fontName, float fontSizeize, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildText(const String& textName, const String& text, const String& fontName, float fontSizeize, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());

		static Mesh* BuildUnnamed(Model* model, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildUnnamed(Model* model, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildUnnamed(const String& modelName, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildUnnamed(const String& modelName, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildRectangleUnnamed(const maths::vec2& size, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildRectangleUnnamed(const maths::vec2& size, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildCuboidUnnamed(const maths::vec3& size, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildCuboidUnnamed(const maths::vec3& size, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildTextUnnamed(const String& text, Font* font, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildTextUnnamed(const String& text, Font* font, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildTextUnnamed(const String& text, const String& fontName, float fontSize, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static Mesh* BuildTextUnnamed(const String& text, const String& fontName, float fontSize, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());

		static void Order(const String& meshName, Model* model, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static void Order(const String& meshName, Model* model, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static void Order(const String& meshName, const String& modelName, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static void Order(const String& meshName, const String& modelName, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderRectangle(const String& meshName, const maths::vec2& size, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderRectangle(const String& meshName, const maths::vec2& size, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderCuboid(const String& meshName, const maths::vec3& size, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderCuboid(const String& meshName, const maths::vec3& size, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderText(const String& textName, const String& text, Font* font, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderText(const String& textName, const String& text, Font* font, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderText(const String& textName, const String& text, const String& fontName, float fontSize, const Color& color, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		static void OrderText(const String& textName, const String& text, const String& fontName, float fontSize, const Color& color, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());

		static bool Exists(const String& meshName);
		static bool Exists(Mesh* mesh);

		static int RequestReferenceCount(const String& meshName);
		static int RequestReferenceCount(Mesh* mesh);

	private:
		static void Increment(const String& mesh);
		static void Decrement(const String& mesh);
		static void CreateNew(Mesh* mesh, int referenceCount);
		static bool ContainsKey(const String& key);

	};

}