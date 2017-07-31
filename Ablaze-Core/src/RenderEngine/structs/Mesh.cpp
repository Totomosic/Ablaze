#include "Mesh.h"
#include "Factories\ModelFactory.h"
#include "Factories\MaterialFactory.h"

namespace Ablaze
{

	Mesh::Mesh(const String& name, std::vector<Model*>* models, std::vector<Material*>* materials)
		: name(name), models(models), materials(materials)
	{

	}

	Mesh::Mesh(const String& name, Model* model, Material* material, const maths::mat4& transform)
		: name(name)
	{
		models = new std::vector<Model*>();
		materials = new std::vector<Material*>();
		transforms = new std::vector<maths::mat4>();
		models->push_back(model);
		materials->push_back(material);
		transforms->push_back(transform);
	}

	Mesh::~Mesh()
	{
		delete models;
		delete materials;
		delete transforms;
	}

	const String& Mesh::GetName() const
	{
		return name;
	}

	const std::vector<Model*>& Mesh::Models() const
	{
		return *models;
	}

	const std::vector<Material*>& Mesh::Materials() const
	{
		return *materials;
	}

	const std::vector<maths::mat4>& Mesh::Transforms() const
	{
		return *transforms;
	}

	int Mesh::GetLength() const
	{
		return models->size();
	}

	void Mesh::AddModel(Model* model, Material* material, const maths::mat4& transform)
	{
		models->push_back(model);
		materials->push_back(material);
		transforms->push_back(transform);
	}

	void Mesh::AddModel(const String& modelName, Material* material, const maths::mat4& transform)
	{
		AddModel(ModelFactory::Request(modelName), material, transform);
	}

	void Mesh::AddModel(Model* model, const String& materialName, const maths::mat4& transform)
	{
		AddModel(model, MaterialFactory::Request(materialName), transform);
	}

	void Mesh::AddModel(const String& modelName, const String& materialName, const maths::mat4& transform)
	{
		AddModel(modelName, MaterialFactory::Request(materialName), transform);
	}

	Model* Mesh::GetModel(int index) const
	{
		return (*models)[index];
	}

	Material* Mesh::GetMaterial(int index) const
	{
		return (*materials)[index];
	}

	void Mesh::GetModel(int index, Model* model, Material* material, maths::mat4& transform) const
	{
		model = (*models)[index];
		material = (*materials)[index];
		transform = (*transforms)[index];
	}

	const maths::mat4& Mesh::GetTransform(int index) const
	{
		return (*transforms)[index];
	}

}