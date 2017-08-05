#pragma once
#include "Types.h"
#include "RenderEngine\structs\Model.h"
#include "RenderEngine\Models\Rectangle.h"
#include "RenderEngine\Models\Cuboid.h"
#include "RenderEngine\Models\Tile.h"
#include "Scene\Terrain\Terrain.h"
#include "Models\WavefrontLoader.h"
#include "Graphics\Fonts\Font.h"
#include "Log.h"
#include <map>

namespace Ablaze
{

	class ModelFactory
	{
	private:
		static std::unordered_map<String, std::pair<Model*, int>*>* models;

	public:
		ModelFactory() { }

		static Model* Request(const String& modelName);
		static Model* Request(Model* model);
		static Model* RequestWeak(const String& modelName);
		static Model* RequestWeak(Model* model);
		static bool Release(const String& modelName);
		static bool Release(Model* model);

		static Model* Build(const String& modelName, WavefrontFile* const file);
		static Rectangle* BuildRectangle(const String& modelName, const maths::vec2& size, const Color& color = Color::White());
		static Cuboid* BuildCuboid(const String& modelName, const maths::vec3& size, const Color& color = Color::White());
		static Sphere* BuildSphere(const String& modelName, float radius, const Color& color = Color::White());
		static Tile* BuildTile(const String& modelName, const maths::vec2& size, const Color& color = Color::White());
		static Model* BuildText(const String& textName, const String& text, Font* font, const Color& color = Color::White());
		static Terrain* BuildTerrain(const String& terrainName, const maths::vec2& size, int vertexResolution);

		static void Order(const String& modelName, WavefrontFile* const file);
		static void OrderRectangle(const String& modelName, const maths::vec2& size, const Color& color = Color::White());
		static void OrderCuboid(const String& modelName, const maths::vec3& size, const Color& color = Color::White());
		static void OrderSphere(const String& modelName, float radius, const Color& color = Color::White());
		static void OrderTile(const String& modelName, const maths::vec2& size, const Color& color = Color::White());
		static void OrderText(const String& textName, const String& text, Font* font, const Color& color = Color::Black());
		static void OrderTerrain(const String& terrainName, const maths::vec2& size, int vertexResolution);

		static Rectangle* FabricateRectangle(const maths::vec2& size, const Color& color = Color::White());
		static Cuboid* FabricateCuboid(const maths::vec3& size, const Color& color = Color::White());
		static Sphere* FabricateSphere(float radius, const Color& color = Color::White());
		static Tile* FabricateTile(const maths::vec2& size, const Color& color = Color::White());
		static Model* FabricateText(const String& text, Font* font, const Color& color = Color::White());
		static Terrain* FabricateTerrain(const maths::vec2& size, int vertexResolution);

		static bool Exists(const String& modelName);
		static bool Exists(Model* model);

		static int RequestReferenceCount(const String& modelName);
		static int RequestReferenceCount(Model* model);

	private:
		static void Increment(const String& model);
		static void Decrement(const String& model);
		static void CreateNew(Model* model, int referenceCount);
		static bool ContainsKey(const String& key);

	};

}