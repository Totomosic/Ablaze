#include "Ablaze.h"

using namespace Ablaze;

class Game : public Application
{
private:
	Scene* scene;

public:

	void Init() override
	{
		Window::SetHint(GLFW_SAMPLES, 4);
		BuildWindow(1280, 720, "Ablaze: ", Color(100, 200, 255));
		VFS::Mount("shader", "");
		VFS::Mount("textures", "");
		VFS::Mount("res", "res/");

		Texture2D* metallic = TextureFactory::Build2D("Metallic", VFS::RetrieveFile<ImageFile>("/res/rustediron2_metallic.png"));
		Texture2D* albedo = TextureFactory::Build2D("Albedo", VFS::RetrieveFile<ImageFile>("/res/rustediron2_basecolor.png"));
		Texture2D* roughness = TextureFactory::Build2D("Roughness", VFS::RetrieveFile<ImageFile>("/res/rustediron2_roughness.png"));
		Texture2D* normal = TextureFactory::Build2D("Normal", VFS::RetrieveFile<ImageFile>("/res/rustediron2_normal.png"));
		Texture2D* ao = TextureFactory::Build2D("AO", VFS::RetrieveFile<ImageFile>("/res/rustediron2_ao.png"));

		TextureFactory::Order2D("GroundAlbedo", VFS::RetrieveFile<ImageFile>("/res/streakedmetal-albedo.png"));
		TextureFactory::Order2D("GroundRoughness", VFS::RetrieveFile<ImageFile>("/res/streakedmetal-roughness.png"));
		TextureFactory::Order2D("GroundMetallic", VFS::RetrieveFile<ImageFile>("/res/streakedmetal-metalness.png"));

		TextureFactory::Order2D("OctoAlbedo", VFS::RetrieveFile<ImageFile>("/res/octostoneAlbedo.png"));
		TextureFactory::Order2D("OctoRoughness", VFS::RetrieveFile<ImageFile>("/res/octostoneRoughness2.png"));
		TextureFactory::Order2D("OctoMetallic", VFS::RetrieveFile<ImageFile>("/res/octostoneMetallic.png"));
		TextureFactory::Order2D("OctoAO", VFS::RetrieveFile<ImageFile>("/res/octostoneAmbient_Occlusionc.png"));
		TextureFactory::Order2D("OctoNormal", VFS::RetrieveFile<ImageFile>("/res/octostoneNormalc.png"));

		//Texture2D* metallic = TextureFactory::Build2D("Metallic", VFS::RetrieveFile<ImageFile>("/res/bamboo-wood-semigloss-metal.png"));
		//Texture2D* albedo = TextureFactory::Build2D("Albedo", VFS::RetrieveFile<ImageFile>("/res/bamboo-wood-semigloss-albedo.png"));
		//Texture2D* roughness = TextureFactory::Build2D("Roughness", VFS::RetrieveFile<ImageFile>("/res/bamboo-wood-semigloss-roughness.png"));
		//Texture2D* normal = TextureFactory::Build2D("Normal", VFS::RetrieveFile<ImageFile>("/res/bamboo-wood-semigloss-normal.png"));
		//Texture2D* ao = TextureFactory::Build2D("AO", VFS::RetrieveFile<ImageFile>("/res/bamboo-wood-semigloss-ao.png"));

		//Texture2D* metallic = TextureFactory::Build2D("Metallic", VFS::RetrieveFile<ImageFile>("/res/cavefloor1_Metallic.png"));
		//Texture2D* albedo = TextureFactory::Build2D("Albedo", VFS::RetrieveFile<ImageFile>("/res/cavefloor1_Base_Color.png"));
		//Texture2D* roughness = TextureFactory::Build2D("Roughness", VFS::RetrieveFile<ImageFile>("/res/cavefloor1_Roughness.png"));
		//Texture2D* normal = TextureFactory::Build2D("Normal", VFS::RetrieveFile<ImageFile>("/res/cavefloor1_Normal.png"));
		//Texture2D* ao = TextureFactory::Build2D("AO", VFS::RetrieveFile<ImageFile>("/res/cavefloor1_Ambient_Occlusion.png"));

		//Texture2D* metallic = TextureFactory::Build2D("gold-scuffed_metallic.png");
		//Texture2D* albedo = TextureFactory::Build2D("gold-scuffed_basecolor-boosted.png");
		//Texture2D* roughness = TextureFactory::Build2D("gold-scuffed_roughness.png");
		Texture2D* normalGold = TextureFactory::Build2D("GoldNormal", VFS::RetrieveFile<ImageFile>("/res/gold-scuffed_normal.png"));

		Terrain* terrain = new Terrain("Terrain", maths::vec2(50, 50), 10);
		terrain->GetData()->SetVertexHeight(0, 0, 5);
		terrain->GetData()->SetVertexHeight(1, 1, 5);
		terrain->GetData()->SetVertexHeight(2, 2, 5);
		terrain->GetData()->SetVertexHeight(3, 3, 5);
		terrain->GetData()->SetVertexHeight(4, 4, 5);
		terrain->GetData()->SetVertexHeight(5, 5, 5);
		terrain->GetData()->SetVertexHeight(6, 6, 5);
		terrain->GetData()->SetVertexHeight(7, 7, 5);
		terrain->GetData()->SetVertexHeight(8, 8, 5);
		terrain->GetData()->SetVertexHeight(9, 9, 5);

		MaterialFactory::Order("Default", Color::White(), Shader::Default());
		MaterialFactory::OrderPBR("RustedMaterial", Color::White(), Shader::PBR(), albedo, roughness, metallic, ao, normal);
		MaterialFactory::OrderPBR("MetallicMaterial", Color::White(), Shader::PBR(), "GroundAlbedo", "GroundRoughness", "GroundMetallic", "AO", "GoldNormal");
		MaterialFactory::OrderPBR("BrickMaterial", Color::White(), Shader::PBR(), "OctoAlbedo", "OctoRoughness", "OctoMetallic", "OctoAO", "OctoNormal");
		ModelFactory::OrderCuboid("Wall", maths::vec3(25, 9.9f, 2), Color::White());
		ModelFactory::OrderTile("Floor", maths::vec2(50, 50), Color::White()); 
		ModelFactory::Order("Learjet", VFS::RetrieveFile<WavefrontFile>("/res/Plane.obj"));
		ModelFactory::Order("Cruiser", VFS::RetrieveFile<WavefrontFile>("/res/SunPrincess.obj"));
		FontFactory::Order("Roboto", "/res/Roboto-Regular.ttf", 32);
		MeshFactory::Order("Floor", "Floor", "BrickMaterial");
		MeshFactory::Order("Wall", "Wall", "MetallicMaterial");
		MeshFactory::Order("Learjet", "Learjet", "RustedMaterial", maths::mat4::Rotation(maths::PI, maths::vec3(0, 1, 0)));
		MeshFactory::Order("Cruiser", "Cruiser", "RustedMaterial", maths::mat4::Translation(maths::vec3(0, 0, -500)) * maths::mat4::Rotation(maths::PI, maths::vec3(0, 1, 0)));
		MeshFactory::Order("Terrain", terrain, "BrickMaterial");

		Camera* camera = new Camera(Viewport(-window->GetWidth() / 2, -window->GetHeight() / 2, window->GetWidth(), window->GetHeight()), maths::vec3(0, 50, 0), maths::mat4::Identity(), Projection::Perspective);
		camera->AddComponent(new Components::RigidBody(1, false, maths::vec3(0.0f, 0.0f, 0.0f), maths::vec3(0.0f)));
		camera->AddComponent(new Components::Collider(BoundingBox(maths::vec3(2.5f, 3.0f, 2.5f))));
		
		scene = new Scene("Default");
		PushScene(scene);
		Layer* layer = new Layer("Scene", new Renderer(), camera);
		scene->PushLayer(layer);

		GameObject* floor = new GameObject(0, 0, 0);
		floor->SetMesh("Terrain");
		floor->AddComponent(new Components::RigidBody(1, true, maths::vec3(0.0f), maths::vec3(0.0f), false));
		floor->AddComponent(new Components::Collider(BoundingBox(maths::vec3(50, 0, 50))));

		GameObject* prev = floor;
		for (int i = 0; i < 0; i++)
		{	
			GameObject* current = GameObject::Instantiate(floor, maths::vec3(0, -10, 0));
			current->MakeChildOf(prev, false);
			prev = current;
		}

		/*GameObject* plane = new GameObject(0, 20, 0);
		plane->SetMesh("Learjet");
		plane->AddComponent(new Components::RigidBody(1, true, 0.0f, 0.0f, false));
		Components::Collider* c = new Components::Collider(maths::vec3(4, 4, 40), maths::vec3(0, -2, 0));
		c->AddBoundingBox(BoundingBox(maths::vec3(30, 1, 5)), maths::vec3(0, -3, -1));
		plane->AddComponent(c);
		plane->Identifier()->SetName("Plane");

		GameObject* modelShip = new GameObject(0, 0, 0);
		modelShip->Transform()->SetScale(0.02f);
		modelShip->SetMesh("Cruiser");
		modelShip->AddComponent(new Components::RigidBody(1, true, 0.0f, 0.0f, false));
		modelShip->AddComponent(Components::Collider::FromMeshComponent(modelShip, false));*/

		Shader::PBR()->Enable();
		Shader::PBR()->SetUniformVec3("Lights[0].Position", maths::vec3(0, 100, 0));
		Shader::PBR()->SetUniformVec3("Lights[0].Color", maths::vec3(10000));
		//Shader::PBR()->SetUniformVec3("Lights[1].Position", maths::vec3(0, 100, 0));
		//Shader::PBR()->SetUniformVec3("Lights[1].Color", maths::vec3(10));
		Shader::PBR()->SetUniformInt("lightCount", 1);
	}

	void Tick() override
	{
		WindowHandle()->SetTitle("Ablaze: " + std::to_string(Time::AverageFPS()) + " FPS");

		AB_INFO(Camera::Main()->ScreenPointToWorldRay(Input::NormalizedMousePosition()));
	}

	void Update() override
	{		
		GameObject* cam = Camera::Main();
		Components::Transform* t = cam->Transform();
		Components::RigidBody* r = cam->GetComponent<Components::RigidBody>();
		if (Input::KeyDown(GLFW_KEY_W))
		{
			r->Acceleration() += CalculateVector(t->Forward()) * 50.0f;
		}
		if (Input::KeyDown(GLFW_KEY_S))
		{
			r->Acceleration() += CalculateVector(t->Forward()) * -50.0f;
		}
		if (Input::KeyDown(GLFW_KEY_D))
		{
			r->Acceleration() += CalculateVector(t->Right()) * 50.0f;
		}
		if (Input::KeyDown(GLFW_KEY_A))
		{
			r->Acceleration() += CalculateVector(t->Right()) * -50.0f;
		}
		if (Input::KeyDown(GLFW_KEY_LEFT))
		{
			t->Rotate(90 * Time::DeltaTime(), maths::vec3(0, 1, 0), Space::World, Angle::Degrees);
		}
		if (Input::KeyDown(GLFW_KEY_RIGHT))
		{
			t->Rotate(-90 * Time::DeltaTime(), maths::vec3(0, 1, 0), Space::World, Angle::Degrees);
		}
		if (Input::KeyDown(GLFW_KEY_UP))
		{
			t->Rotate(90 * Time::DeltaTime(), maths::vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}
		if (Input::KeyDown(GLFW_KEY_DOWN))
		{
			t->Rotate(-90 * Time::DeltaTime(), maths::vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}
		if (Input::KeyDown(GLFW_KEY_SPACE))
		{
			r->Velocity().y = 10.0f;
			r->Acceleration().y = 0.0f;
		}

		Application::Update();
	}

	maths::vec3 CalculateVector(const maths::vec3& vector)
	{
		maths::vec3 vec = vector;
		vec.y = 0;
		return vec.Normalize();
	}

};

int main()
{
	Game* game = new Game();
	game->Start();
	delete game;

	return 0;
}