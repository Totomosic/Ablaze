#include "ModelFactory.h"

namespace Ablaze
{

	std::unordered_map<String, std::pair<Model*, int>*>* ModelFactory::models = new std::unordered_map<String, std::pair<Model*, int>*>();

	Model* ModelFactory::Request(const String& modelName)
	{
		if (ContainsKey(modelName))
		{
			auto pair = (*models)[modelName];
			pair->second += 1;
			return pair->first;
		}
		AB_ERROR("Requested model that does not exist: " + modelName);
		return nullptr;
	}

	Model* ModelFactory::Request(Model* model)
	{
		return Request(model->GetName());
	}

	Model* ModelFactory::RequestWeak(const String& modelName)
	{
		Model* model = Request(modelName);
		Decrement(model->GetName());
		return model;
	}

	Model* ModelFactory::RequestWeak(Model* model)
	{
		return RequestWeak(model->GetName());
	}

	bool ModelFactory::Release(const String& modelName)
	{
		if (ContainsKey(modelName))
		{
			auto pair = (*models)[modelName];
			pair->second--;
			if (pair->second <= 0)
			{
				models->erase(modelName);
				delete pair->first;
				delete pair;
				return true;
			}
			return false;
		}
		AB_WARN("Attempted to release model that did not exist: " + modelName);
		return false;
	}

	bool ModelFactory::Release(Model* model)
	{
		return Release(model->GetName());
	}

	Model* ModelFactory::Build(const String& modelName, WavefrontFile* const file)
	{
		Model* model = Internal::WavefrontLoader::LoadModel(modelName, file);
		CreateNew(model, 1);
		return model;
	}

	Ablaze::Rectangle* ModelFactory::BuildRectangle(const String& modelName, const maths::vec2& size, const Color& color)
	{
		Ablaze::Rectangle* rect = new Ablaze::Rectangle(modelName, size, color);
		CreateNew(rect, 1);
		return rect;
	}

	Cuboid* ModelFactory::BuildCuboid(const String& modelName, const maths::vec3& size, const Color& color)
	{
		Cuboid* cuboid = new Cuboid(modelName, size, color);
		CreateNew(cuboid, 1);
		return cuboid;
	}

	Sphere* ModelFactory::BuildSphere(const String& modelName, float radius, const Color& color)
	{
		Sphere* sphere = new Sphere(modelName, radius, color);
		CreateNew(sphere, 1);
		return sphere;
	}

	Tile* ModelFactory::BuildTile(const String& modelName, const maths::vec2& size, const Color& color)
	{
		Tile* tile = new Tile(modelName, size, color);
		CreateNew(tile, 1);
		return tile;
	}

	Model* ModelFactory::BuildText(const String& textName, const String& text, Font* font, const Color& color)
	{
		Model* textModel = font->CreateModel(textName, text, color);
		CreateNew(textModel, 1);
		return textModel;
	}

	Terrain* ModelFactory::BuildTerrain(const String& terrainName, const maths::vec2& size, int vertexResolution)
	{
		Terrain* terrain = new Terrain(terrainName, size, vertexResolution);
		CreateNew(terrain, 1);
		return terrain;
	}

	void ModelFactory::Order(const String& modelName, WavefrontFile* const file)
	{
		Decrement(Build(modelName, file)->GetName());
	}

	void ModelFactory::OrderRectangle(const String& modelName, const maths::vec2& size, const Color& color)
	{
		Decrement(BuildRectangle(modelName, size, color)->GetName());
	}

	void ModelFactory::OrderCuboid(const String& modelName, const maths::vec3& size, const Color& color)
	{
		Decrement(BuildCuboid(modelName, size, color)->GetName());
	}

	void ModelFactory::OrderSphere(const String& modelName, float radius, const Color& color)
	{
		Decrement(BuildSphere(modelName, radius, color)->GetName());
	}

	void ModelFactory::OrderTile(const String& modelName, const maths::vec2& size, const Color& color)
	{
		Decrement(BuildTile(modelName, size, color)->GetName());
	}

	void ModelFactory::OrderText(const String& textName, const String& text, Font* font, const Color& color)
	{
		Decrement(BuildText(textName, text, font, color)->GetName());
	}

	void ModelFactory::OrderTerrain(const String& terrainName, const maths::vec2& size, int vertexResolution)
	{
		Decrement(BuildTerrain(terrainName, size, vertexResolution)->GetName());
	}

	Rectangle* ModelFactory::FabricateRectangle(const maths::vec2& size, const Color& color)
	{
		String hashedName = "Rectangle(" + std::to_string(size.x) + "," + std::to_string(size.y) + ")Color(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return (Rectangle*)Request(hashedName);
		}
		return BuildRectangle(hashedName, size, color);
	}

	Cuboid* ModelFactory::FabricateCuboid(const maths::vec3& size, const Color& color)
	{
		String hashedName = "Cuboid(" + std::to_string(size.x) + "," + std::to_string(size.y) + "," + std::to_string(size.z) + ")Color(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return (Cuboid*)Request(hashedName);
		}
		return BuildCuboid(hashedName, size, color);
	}

	Sphere* ModelFactory::FabricateSphere(float radius, const Color& color)
	{
		String hashedName = "Sphere(" + std::to_string(radius) + ")Color(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return (Sphere*)Request(hashedName);
		}
		return BuildSphere(hashedName, radius, color);
	}

	Tile* ModelFactory::FabricateTile(const maths::vec2& size, const Color& color)
	{
		String hashedName = "Tile(" + std::to_string(size.x) + "," + std::to_string(size.y) + ")Color(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return (Tile*)Request(hashedName);
		}
		return BuildTile(hashedName, size, color);
	}

	Model* ModelFactory::FabricateText(const String& text, Font* font, const Color& color)
	{
		String hashedName = "Text(" + text + ")Font(" + font->GetName() + std::to_string(font->GetSize()) + ")Color(" + std::to_string(color.r) + "," + std::to_string(color.g) + "," + std::to_string(color.b) + "," + std::to_string(color.a) + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return Request(hashedName);
		}
		return BuildText(hashedName, text, font, color);
	}

	Terrain* ModelFactory::FabricateTerrain(const maths::vec2& size, int vertexResolution)
	{
		String hashedName = "Terrain(" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")res(" + std::to_string(vertexResolution) + ")_HASHED_";
		if (ContainsKey(hashedName))
		{
			return (Terrain*)Request(hashedName);
		}
		return BuildTerrain(hashedName, size, vertexResolution);
	}

	bool ModelFactory::Exists(const String& modelName)
	{
		return ContainsKey(modelName);
	}

	bool ModelFactory::Exists(Model* model)
	{
		return Exists(model->GetName());
	}

	int ModelFactory::RequestReferenceCount(const String& modelName)
	{
		if (ContainsKey(modelName))
		{
			return (*models)[modelName]->second;
		}
		AB_WARN("Requested model does not exist: " + modelName);
		return 0;
	}

	int ModelFactory::RequestReferenceCount(Model* model)
	{
		return RequestReferenceCount(model->GetName());
	}

	void ModelFactory::Increment(const String& modelName)
	{
		(*models)[modelName]->second++;
	}

	void ModelFactory::Decrement(const String& modelName)
	{
		(*models)[modelName]->second--;
	}

	void ModelFactory::CreateNew(Model* model, int referenced)
	{
		(*models)[model->GetName()] = new std::pair<Model*, int>(model, referenced);
	}

	bool ModelFactory::ContainsKey(const String& key)
	{
		return models->count(key) == 1;
	}

}