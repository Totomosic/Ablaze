#include "MeshFactory.h"
#include "Graphics/Resources/Fonts/Font.h"

namespace Ablaze
{

	std::unordered_map<String, std::pair<Mesh*, int>*> MeshFactory::meshes = std::unordered_map<String, std::pair<Mesh*, int>*>();
	uint MeshFactory::unnamedCount = 0;

	Mesh* MeshFactory::Request(const String& meshName)
	{
		if (ContainsKey(meshName))
		{
			auto pair = meshes[meshName];
			pair->second += 1;
			for (int i = 0; i < pair->first->GetLength(); i++)
			{
				ModelFactory::Request(pair->first->GetModel(i));
				MaterialFactory::Request(pair->first->GetMaterial(i));
			}
			return pair->first;
		}
		AB_ERROR("Requested mesh that does not exist: " + meshName);
		return nullptr;
	}

	Mesh* MeshFactory::Request(Mesh* mesh)
	{
		return Request(mesh->GetName());
	}

	Mesh* MeshFactory::RequestWeak(const String& meshName)
	{
		Mesh* mesh = Request(meshName);
		Decrement(mesh->GetName());
		return mesh;
	}

	Mesh* MeshFactory::RequestWeak(Mesh* mesh)
	{
		return RequestWeak(mesh->GetName());
	}

	bool MeshFactory::Release(const String& meshName)
	{
		if (ContainsKey(meshName))
		{
			auto pair = meshes[meshName];
			pair->second--;
			if (pair->second <= 0)
			{
				for (int i = 0; i < pair->first->GetLength(); i++)
				{
					ModelFactory::Release(pair->first->GetModel(i));
					MaterialFactory::Release(pair->first->GetMaterial(i));
				}		
				meshes.erase(meshName);
				delete pair->first;
				delete pair;
				return true;
			}
			return false;
		}
		AB_WARN("Attempted to release a mesh that does not exist: " + meshName);
		return false;
	}

	bool MeshFactory::Release(Mesh* mesh)
	{
		return Release(mesh->GetName());
	}

	Mesh* MeshFactory::Build(const String& meshName, Model* model, Material* material, const maths::mat4& transform)
	{
		if (ContainsKey(meshName))
		{
			AB_FATAL("Attempted to build mesh with a name that already exists: " + meshName);
			return nullptr;
		}
		Mesh* mesh = new Mesh(meshName, model, material, transform);
		CreateNew(mesh, 1);
		return mesh;
	}

	Mesh* MeshFactory::Build(const String& meshName, Model* model, const String& materialName, const maths::mat4& transform)
	{
		return Build(meshName, model, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::Build(const String& meshName, const String& modelName, Material* material, const maths::mat4& transform)
	{
		return Build(meshName, ModelFactory::Request(modelName), material, transform);
	}

	Mesh* MeshFactory::Build(const String& meshName, const String& modelName, const String& materialName, const maths::mat4& transform)
	{
		return Build(meshName, modelName, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildRectangle(const String& meshName, const maths::vec2& size, const Color& color, Material* material, const maths::mat4& transform)
	{
		return Build(meshName, ModelFactory::FabricateRectangle(size, color), material, transform);
	}

	Mesh* MeshFactory::BuildRectangle(const String& meshName, const maths::vec2& size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildRectangle(meshName, size, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildCuboid(const String& meshName, const maths::vec3& size, const Color& color, Material* material, const maths::mat4& transform)
	{
		return Build(meshName, ModelFactory::FabricateCuboid(size, color), material, transform);
	}

	Mesh* MeshFactory::BuildCuboid(const String& meshName, const maths::vec3& size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildCuboid(meshName, size, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildText(const String& textName, const String& text, Font* font, const Color& color, Material* material, const maths::mat4& transform)
	{
		return Build(textName, ModelFactory::FabricateText(text, font, color), material, transform);
	}

	Mesh* MeshFactory::BuildText(const String& textName, const String& text, Font* font, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildText(textName, text, font, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildText(const String& textName, const String& text, const String& fontName, float size, const Color& color, Material* material, const maths::mat4& transform)
	{
		return BuildText(textName, text, FontFactory::Request(fontName, size), color, material, transform);
	}

	Mesh* MeshFactory::BuildText(const String& textName, const String& text, const String& fontName, float size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildText(textName, text, fontName, size, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildUnnamed(Model* model, Material* material, const maths::mat4& transform)
	{
		unnamedCount++;
		return Build("_MESH_BUILD_UNNAMED_" + std::to_string(unnamedCount) + "_", model, material, transform);
	}

	Mesh* MeshFactory::BuildUnnamed(Model* model, const String& materialName, const maths::mat4& transform)
	{
		return BuildUnnamed(model, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildUnnamed(const String& modelName, Material* material, const maths::mat4& transform)
	{
		return BuildUnnamed(ModelFactory::Request(modelName), material, transform);
	}

	Mesh* MeshFactory::BuildUnnamed(const String& modelName, const String& materialName, const maths::mat4& transform)
	{
		return BuildUnnamed(modelName, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildRectangleUnnamed(const maths::vec2& size, const Color& color, Material* material, const maths::mat4& transform)
	{
		unnamedCount++;
		return Build("_MESH_BUILD_UNNAMED_" + std::to_string(unnamedCount) + "_", ModelFactory::FabricateRectangle(size, color), material, transform);
	}

	Mesh* MeshFactory::BuildRectangleUnnamed(const maths::vec2& size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildRectangleUnnamed(size, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildCuboidUnnamed(const maths::vec3& size, const Color& color, Material* material, const maths::mat4& transform)
	{
		unnamedCount++;
		return Build("_MESH_BUILD_UNNAMED_" + std::to_string(unnamedCount) + "_", ModelFactory::FabricateCuboid(size, color), material, transform);
	}

	Mesh* MeshFactory::BuildCuboidUnnamed(const maths::vec3& size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildCuboidUnnamed(size, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildTextUnnamed(const String& text, Font* font, const Color& color, Material* material, const maths::mat4& transform)
	{
		unnamedCount++;
		return Build("_MESH_BUILD_UNNAMED_" + std::to_string(unnamedCount) + "_", ModelFactory::FabricateText(text, font, color), material, transform);
	}

	Mesh* MeshFactory::BuildTextUnnamed(const String& text, Font* font, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildTextUnnamed(text, font, color, MaterialFactory::Request(materialName), transform);
	}

	Mesh* MeshFactory::BuildTextUnnamed(const String& text, const String& fontName, float size, const Color& color, Material* material, const maths::mat4& transform)
	{
		return BuildTextUnnamed(text, FontFactory::Request(fontName, size), color, material, transform);
	}

	Mesh* MeshFactory::BuildTextUnnamed(const String& text, const String& fontName, float size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		return BuildTextUnnamed(text, fontName, size, color, MaterialFactory::Request(materialName), transform);
	}

	void MeshFactory::Order(const String& meshName, Model* model, Material* material, const maths::mat4& transform)
	{
		Decrement(Build(meshName, model, material, transform)->GetName());
	}

	void MeshFactory::Order(const String& meshName, Model* model, const String& materialName, const maths::mat4& transform)
	{
		Order(meshName, model, MaterialFactory::Request(materialName), transform);
	}

	void MeshFactory::Order(const String& meshName, const String& modelName, Material* material, const maths::mat4& transform)
	{
		Order(meshName, ModelFactory::Request(modelName), material, transform);
	}

	void MeshFactory::Order(const String& meshName, const String& modelName, const String& materialName, const maths::mat4& transform)
	{
		Order(meshName, modelName, MaterialFactory::Request(materialName), transform);
	}

	void MeshFactory::OrderRectangle(const String& meshName, const maths::vec2& size, const Color& color, Material* material, const maths::mat4& transform)
	{
		Decrement(BuildRectangle(meshName, size, color, material, transform)->GetName());
	}

	void MeshFactory::OrderRectangle(const String& meshName, const maths::vec2& size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		OrderRectangle(meshName, size, color, MaterialFactory::Request(materialName), transform);
	}

	void MeshFactory::OrderCuboid(const String& meshName, const maths::vec3& size, const Color& color, Material* material, const maths::mat4& transform)
	{
		Decrement(BuildCuboid(meshName, size, color, material, transform)->GetName());
	}

	void MeshFactory::OrderCuboid(const String& meshName, const maths::vec3& size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		OrderCuboid(meshName, size, color, MaterialFactory::Request(materialName), transform);
	}

	void MeshFactory::OrderText(const String& textName, const String& text, Font* font, const Color& color, Material* material, const maths::mat4& transform)
	{
		Decrement(BuildText(textName, text, font, color, material, transform)->GetName());
	}

	void MeshFactory::OrderText(const String& textName, const String& text, Font* font, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		OrderText(textName, text, font, color, MaterialFactory::Request(materialName), transform);
	}

	void MeshFactory::OrderText(const String& textName, const String& text, const String& fontName, float size, const Color& color, Material* material, const maths::mat4& transform)
	{
		Decrement(BuildText(textName, text, fontName, size, color, material, transform)->GetName());
	}

	void MeshFactory::OrderText(const String& textName, const String& text, const String& fontName, float size, const Color& color, const String& materialName, const maths::mat4& transform)
	{
		OrderText(textName, text, fontName, size, color, MaterialFactory::Request(materialName), transform);
	}

	bool MeshFactory::Exists(const String& meshName)
	{
		return ContainsKey(meshName);
	}

	bool MeshFactory::Exists(Mesh* mesh)
	{
		return Exists(mesh->GetName());
	}

	int MeshFactory::RequestReferenceCount(const String& meshName)
	{
		if (ContainsKey(meshName))
		{
			return meshes[meshName]->second;
		}
		AB_WARN("Attempting to request reference count of mesh that does not exist: " + meshName);
		return 0;
	}

	int MeshFactory::RequestReferenceCount(Mesh* mesh)
	{
		return RequestReferenceCount(mesh->GetName());
	}

	void MeshFactory::Increment(const String& meshName)
	{
		meshes[meshName]->second++;
	}

	void MeshFactory::Decrement(const String& meshName)
	{
		meshes[meshName]->second--;
	}

	void MeshFactory::CreateNew(Mesh* mesh, int referenceCount)
	{
		meshes[mesh->GetName()] = new std::pair<Mesh*, int>(mesh, referenceCount);
	}

	bool MeshFactory::ContainsKey(const String& key)
	{
		return meshes.find(key) != meshes.end();
	}

}