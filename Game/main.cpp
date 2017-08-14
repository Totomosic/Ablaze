#include "Ablaze.h"

using namespace Ablaze;

class Game : public Application
{
private:
	Scene* scene;
	bool firstPersonMode;
	float camSpeed = 500;

public:

	void Init() override
	{
		Window::SetHint(GLFW_SAMPLES, 4);
		BuildWindow(1280, 720, "Ablaze: ", Color(100, 200, 255));
		VFS::Mount("shader", "");
		VFS::Mount("textures", "res/Textures/");
		VFS::Mount("res", "res/");
		
		firstPersonMode = false;

		scene = new Scene("Default");
		Layer* layer = new Layer("Scene", new ForwardRenderer());

		Texture2D* metallic = TextureFactory::Build2D("Metallic", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_metallic.png"));
		Texture2D* albedo = TextureFactory::Build2D("Albedo", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_basecolor.png"));
		Texture2D* roughness = TextureFactory::Build2D("Roughness", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_roughness.png"));
		Texture2D* normal = TextureFactory::Build2D("Normal", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_normal.png"));
		Texture2D* ao = TextureFactory::Build2D("AO", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_ao.png"));

		TextureFactory::Order2D("GroundAlbedo", VFS::RetrieveFile<ImageFile>("/textures/streakedmetal-albedo.png"));
		TextureFactory::Order2D("GroundRoughness", VFS::RetrieveFile<ImageFile>("/textures/streakedmetal-roughness.png"));
		TextureFactory::Order2D("GroundMetallic", VFS::RetrieveFile<ImageFile>("/textures/streakedmetal-metalness.png"));

		TextureFactory::Order2D("OctoAlbedo", VFS::RetrieveFile<ImageFile>("/textures/octostoneAlbedo.png"));
		TextureFactory::Order2D("OctoRoughness", VFS::RetrieveFile<ImageFile>("/textures/octostoneRoughness2.png"));
		TextureFactory::Order2D("OctoMetallic", VFS::RetrieveFile<ImageFile>("/textures/octostoneMetallic.png"));
		TextureFactory::Order2D("OctoAO", VFS::RetrieveFile<ImageFile>("/textures/octostoneAmbient_Occlusionc.png"));
		TextureFactory::Order2D("OctoNormal", VFS::RetrieveFile<ImageFile>("/textures/octostoneNormalc.png"));

		TextureFactory::Order2D("GrassAlbedo", VFS::RetrieveFile<ImageFile>("/textures/grass1-albedo3.png"));
		TextureFactory::Order2D("GrassRoughness", VFS::RetrieveFile<ImageFile>("/textures/grass1-rough.png"));
		TextureFactory::Order2D("GrassMetallic", VFS::RetrieveFile<ImageFile>("/textures/octostoneMetallic.png"));
		TextureFactory::Order2D("GrassAO", VFS::RetrieveFile<ImageFile>("/textures/grass1-ao.png"));
		TextureFactory::Order2D("GrassNormal", VFS::RetrieveFile<ImageFile>("/textures/grass1-normal2.png"));

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
		Texture2D* normalGold = TextureFactory::Build2D("GoldNormal", VFS::RetrieveFile<ImageFile>("/textures/gold-scuffed_normal.png"));

		Terrain* terrain = ModelFactory::BuildTerrain("Terrain", maths::vec2(5000), 200);
		TerrainData* data = terrain->GetData();
		data->EnableEditing();
		data->SetData(PerlinNoise(688246124, 100, 16, 8));
		data->DisableEditing();

		MaterialFactory::Order("Default", Color::White(), Shader::Default(), "");
		MaterialFactory::OrderPBR("RustedMaterial", Color::White(), Shader::PBR(), albedo, roughness, metallic, ao, normal);
		MaterialFactory::OrderPBR("MetallicMaterial", Color::White(), Shader::PBR(), "GroundAlbedo", "GroundRoughness", "GroundMetallic", "AO", "GoldNormal");
		MaterialFactory::OrderPBR("BrickMaterial", Color::White(), Shader::PBR(), "OctoAlbedo", "OctoRoughness", "OctoMetallic", "OctoAO", "OctoNormal");
		MaterialFactory::OrderPBR("GrassMaterial", Color::White(), Shader::PBR(), "GrassAlbedo", "GrassRoughness", "GrassMetallic", "GrassAO", "GrassNormal");
		ModelFactory::OrderCuboid("Wall", maths::vec3(25, 9.9f, 2), Color::White());
		ModelFactory::OrderTile("Floor", maths::vec2(50, 50), Color::White()); 
		ModelFactory::Order("Learjet", VFS::RetrieveFile<WavefrontFile>("/res/Plane.obj"));
		ModelFactory::Order("Cruiser", VFS::RetrieveFile<WavefrontFile>("/res/SunPrincess.obj"));
		ModelFactory::Order("Bridge", VFS::RetrieveFile<WavefrontFile>("/res/Bridge1.obj"));
		MeshFactory::Order("Floor", "Floor", "BrickMaterial");
		MeshFactory::Order("Wall", "Wall", "MetallicMaterial");
		MeshFactory::Order("Learjet", "Learjet", "RustedMaterial", maths::mat4::Rotation(maths::PI, maths::vec3(0, 1, 0)));
		MeshFactory::Order("Cruiser", "Cruiser", "RustedMaterial", maths::mat4::Translation(maths::vec3(0, 0, -500)) * maths::mat4::Rotation(maths::PI, maths::vec3(0, 1, 0)));
		MeshFactory::Order("Terrain", "Terrain", "GrassMaterial");
		MeshFactory::Order("Bridge", "Bridge", "Default", maths::mat4::Translation(16.7f, 0, 0) * maths::mat4::Rotation(maths::PI / 2, maths::vec3(0, 1, 0)));
		MaterialFactory::RequestPBR("GrassMaterial")->AddUniformFloat("tiling", 100);

		Camera* camera = new Camera(window->GetViewport(), maths::vec3(0, 100, 0), maths::mat4::Identity(), Projection::Perspective, maths::PI / 6.0, Angle::Radians, 1.0f, 3000.0f);
		camera->AddComponent(new Components::RigidBody(1, false, maths::vec3(0.0f, 0.0f, 0.0f), maths::vec3(0.0f)));
		camera->AddComponent(new Components::Collider(OBB(maths::vec3(2.5f, 3.0f, 2.5f))));

		GameObject* floor = new GameObject(0, 0, 0);
		floor->SetMesh("Terrain");
		floor->Identifier()->SetName("Terrain");

		GameObject* bridge = new GameObject(0, -120, -700);
		bridge->Transform()->SetScale(80);
		bridge->Transform()->Rotate(-65, maths::vec3(0, 1, 0), Space::World, Angle::Degrees);
		bridge->AddComponent(new Components::RigidBody(1, true, 0, 0, false));
		Components::Collider* collider = new Components::Collider(OBB(maths::vec3(2.7f, 0.3f, 34)), maths::mat4::Translation(0, 2.5f, 0));
		collider->AddOBB(OBB(maths::vec3(0.7f, 3, 1.2f)), maths::mat4::Translation(1.2f, 2.5f, 11.7f));
		collider->AddOBB(OBB(maths::vec3(0.7f, 3, 1.2f)), maths::mat4::Translation(-1.3f, 2.5f, 11.7f));
		collider->AddOBB(OBB(maths::vec3(0.7f, 3, 1.2f)), maths::mat4::Translation(1.2f, 2.5f, -11.0f));
		collider->AddOBB(OBB(maths::vec3(0.7f, 3, 1.2f)), maths::mat4::Translation(-1.2f, 2.5f, -11.0f));
		bridge->AddComponent(collider);
		bridge->SetMesh("Bridge");

		Layer* waterLayer = new Layer("Water", new ForwardRenderer());

		GameObject* water = new GameObject(0, 0, 0);
		water->SetMesh(MeshFactory::Build("Water", ModelFactory::BuildTile("Water", maths::vec2(10000), Color(50, 100, 150, 180)), "Default"));
		water->AddComponent(new Components::RigidBody(1, true, maths::vec3(0.0f), maths::vec3(0.0f), false));
		water->AddComponent(new Components::Collider(OBB(maths::vec3(10000, 0, 10000))));

		Layer* uiLayer = new Layer("UI", new ForwardRenderer());

		Camera* uiCamera = new Camera(Viewport(-WindowWidth() / 2, -WindowHeight() / 2, WindowWidth(), WindowHeight()), maths::vec3(0, 0, 100), maths::mat4::Identity(), Projection::Orthographic);
		uiLayer->SetCamera(uiCamera);

		GameObject* crossHair = new GameObject(0, 0, 0);
		crossHair->SetMesh(MeshFactory::BuildRectangleUnnamed(maths::vec2(5), Color::Black(), "Default"));

		Shader::PBR()->Enable();
		Shader::PBR()->SetUniformVec3("Lights[0].Position", maths::vec3(0, 10000, 0));
		Shader::PBR()->SetUniformVec3("Lights[0].Color", maths::vec3(1e9));
		Shader::PBR()->SetUniformInt("lightCount", 1);

		Shader::Default()->Enable();
		Shader::Default()->SetUniformVec3("Lights[0].Position", maths::vec3(0, 10000, 0));
	}

	void Tick() override
	{
		WindowHandle()->SetTitle("Ablaze: " + std::to_string(Time::AverageFPS()) + " FPS");
	}

	void Update() override
	{		
		GameObject* cam = Camera::Main();
		Components::Transform* t = cam->Transform();
		Components::RigidBody* r = cam->GetComponent<Components::RigidBody>();
		if (Input::KeyDown(GLFW_KEY_W))
		{
			r->Acceleration() += CalculateVector(t->Forward()) * camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_S))
		{
			r->Acceleration() += CalculateVector(t->Forward()) * -camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_D))
		{
			r->Acceleration() += CalculateVector(t->Right()) * camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_A))
		{
			r->Acceleration() += CalculateVector(t->Right()) * -camSpeed;
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
		if (Input::KeyPressedDown(GLFW_KEY_C))
		{
			firstPersonMode = !firstPersonMode;
			if (firstPersonMode)
			{
				Mouse::Capture();
			}
			else
			{
				Mouse::Release();
			}
		}

		if (firstPersonMode)
		{
			t->Rotate(-Mouse::GetRelPosition().x * 0.3f, maths::vec3(0, 1, 0), Space::World, Angle::Degrees);
			t->Rotate(-Mouse::GetRelPosition().y * 0.3f, maths::vec3(1, 0, 0), Space::Local, Angle::Degrees);
		}

		Terrain* terrain = (Terrain*)GameObjects::GetWithName("Terrain")->Mesh()->GetMesh()->GetModel(0);
		TerrainData& data = *terrain->GetData();
		maths::vec3 pos = t->GetPosition();
		if (pos.y - 1.5f <= data.GetHeightAtLocation(pos.x, pos.z))
		{
			t->SetPosition(maths::vec3(pos.x, data.GetHeightAtLocation(pos.x, pos.z) + 1.5f, pos.z));
			r->Velocity().y = 0;
			r->Acceleration().y = 0;
		}

		if (Input::KeyPressedDown(GLFW_KEY_SPACE))
		{
			r->Velocity().y = 8.0f * maths::Map(camSpeed, 10, 1000, 1, 10);
			r->Acceleration().y = 0.0f;
		}
		Application::Update();
	}

	void Render() override
	{
		Application::Render();
		UpdateDisplay();
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