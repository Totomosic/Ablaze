#pragma once
#include <vector>
#include "Material.h"
#include "Model.h"
#include "Maths/Maths.h"
#include "Types.h"

namespace Ablaze
{

	class MeshFactory;

	class Mesh
	{
	private:
		String name;
		std::vector<Material*>* materials;
		std::vector<Model*>* models;
		std::vector<maths::mat4>* transforms;

	protected:
		Mesh(const String& name, std::vector<Model*>* models, std::vector<Material*>* materials);
		Mesh(const String& name, Model* model, Material* material, const maths::mat4& transform = maths::mat4::Identity());
		Mesh(const Mesh& other) = delete;

	public:		
		virtual ~Mesh();

		const String& GetName() const;
		const std::vector<Model*>& Models() const;
		const std::vector<Material*>& Materials() const;
		const std::vector<maths::mat4>& Transforms() const;
		int GetLength() const;

		void AddModel(Model* model, Material* modelMaterial, const maths::mat4& transform = maths::mat4::Identity());
		void AddModel(const String& modelName, Material* modelMaterial, const maths::mat4& transform = maths::mat4::Identity());
		void AddModel(Model* model, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		void AddModel(const String& modelName, const String& materialName, const maths::mat4& transform = maths::mat4::Identity());
		Model* GetModel(int index) const;
		void GetModel(int index, Model* model, Material* material, maths::mat4& transform) const;

		Material* GetMaterial(int index) const;

		const maths::mat4& GetTransform(int index) const;

		friend class MeshFactory;

	};

}