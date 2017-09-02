#include "Ablaze.h"
#include <functional>

using namespace Ablaze;

class Game : public Application
{
private:
	Scene* scene;
	DynamicTexture* reflectionTexture;
	DynamicTexture* refractionTexture;
	UniformManager tempUniforms;
	bool firstPersonMode;
	float camSpeed = 500;

	float* movefactor = nullptr;

public:

	void Init() override
	{
		Window::SetHint(GLFW_SAMPLES, 4);
		BuildWindow(1280, 720, "Ablaze: ", Color(100, 200, 255));
		VFS::Mount("shader", "res/Shaders/");
		VFS::Mount("textures", "res/Textures/");
		VFS::Mount("water", "res/Textures/Water/");
		VFS::Mount("res", "res/");
		
		firstPersonMode = false;

		scene = new Scene("Default");
		Layer* layer = new Layer("Scene", new ForwardRenderer());

		Shader* waterShader = Shader::FromFile("Water", VFS::RetrieveFile<GLSLFile>("/shader/water_v.glsl"), VFS::RetrieveFile<GLSLFile>("/shader/water_f.glsl"));
		Shader* terrainShader = Shader::FromFile("Terrain", VFS::RetrieveFile<GLSLFile>("/shader/terrain_v.glsl"), VFS::RetrieveFile<GLSLFile>("/shader/terrain_f.glsl"));

		Texture2D* metallic = TextureFactory::Build2D("Metallic", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_metallic.png"));
		Texture2D* albedo = TextureFactory::Build2D("Albedo", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_basecolor.png"));
		Texture2D* roughness = TextureFactory::Build2D("Roughness", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_roughness.png"));
		Texture2D* normal = TextureFactory::Build2D("Normal", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_normal.png"));
		Texture2D* ao = TextureFactory::Build2D("AO", VFS::RetrieveFile<ImageFile>("/textures/rustediron2_ao.png"));

		TextureFactory::Order2D("WaterNormalMap", VFS::RetrieveFile<ImageFile>("/water/normal.png"));
		TextureFactory::Order2D("WaterDUDV", VFS::RetrieveFile<ImageFile>("/water/waterDUDV.png"));

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

		Texture2D* normalGold = TextureFactory::Build2D("GoldNormal", VFS::RetrieveFile<ImageFile>("/textures/gold-scuffed_normal.png"));

		tempUniforms.AddUniform("ClippingPlane.clipNormal", maths::vec3(0, -1, 0));
		tempUniforms.AddUniform<float>("ClippingPlane.clipHeight", 1000000);

		reflectionTexture = new DynamicTexture("Reflection", 512, 512, UpdateMode::CreateEachFrame, 1);
		reflectionTexture->GetUniforms().AddUniform("ClippingPlane.clipNormal", maths::vec3(0, 1, 0));
		reflectionTexture->GetUniforms().AddUniform<float>("ClippingPlane.clipHeight", 0);
		refractionTexture = new DynamicTexture("Refraction", 512, 512, UpdateMode::CreateEachFrame, 1);
		refractionTexture->GetUniforms().AddUniform("ClippingPlane.clipNormal", maths::vec3(0, -1, 0));
		refractionTexture->GetUniforms().AddUniform<float>("ClippingPlane.clipHeight", 0);

		reflectionTexture->SetClearColor(window->GetClearColor());
		refractionTexture->SetClearColor(window->GetClearColor());

		Terrain* terrain = ModelFactory::BuildTerrain("Terrain", maths::vec2(5000), 200);
		TerrainData* data = terrain->GetData();
		data->EnableEditing();
		data->SetData(PerlinNoise(983562, 100, 16, 8));
		data->DisableEditing();

		MaterialFactory::Order("Default", Color::White(), Shader::Default());
		MaterialFactory::Order("Water", Color::White(), waterShader);

		Material* waterMaterial = MaterialFactory::Request("Water");
		waterMaterial->AddTexture("Tex0", reflectionTexture);
		waterMaterial->AddTexture("Tex1", refractionTexture);
		waterMaterial->AddTexture("Tex2", TextureFactory::Request2D("WaterDUDV"));
		waterMaterial->AddTexture("Tex3", TextureFactory::Request2D("WaterNormalMap"));
		waterMaterial->AddUniform<float>("moveFactor", 0);
		movefactor = &waterMaterial->GetUniforms().GetUniform<float>("moveFactor");

		MaterialFactory::OrderPBR("RustedMaterial", Color::White(), Shader::PBR(), albedo, roughness, metallic, ao, normal);
		MaterialFactory::OrderPBR("MetallicMaterial", Color::White(), Shader::PBR(), "GroundAlbedo", "GroundRoughness", "GroundMetallic", "AO", "GoldNormal");
		MaterialFactory::OrderPBR("BrickMaterial", Color::White(), Shader::PBR(), "OctoAlbedo", "OctoRoughness", "OctoMetallic", "OctoAO", "OctoNormal");
		MaterialFactory::OrderPBR("GrassMaterial", Color::White(), Shader::PBR(), "GrassAlbedo", "GrassRoughness", "GrassMetallic", "GrassAO", "GrassNormal");
		MaterialFactory::Order("TerrainMaterial", Color::White(), terrainShader, "Tex0", "GrassAlbedo");
		ModelFactory::Order("Learjet", VFS::RetrieveFile<WavefrontFile>("/res/Plane.obj"));
		ModelFactory::Order("Cruiser", VFS::RetrieveFile<WavefrontFile>("/res/SunPrincess.obj"));
		ModelFactory::Order("Bridge", VFS::RetrieveFile<WavefrontFile>("/res/Bridge1.obj"));
		FontFactory::Order("Arial", "/res/arial.ttf", 32);
		MeshFactory::Order("Learjet", "Learjet", "RustedMaterial", maths::mat4::Rotation(maths::PI, maths::vec3(0, 1, 0)));
		MeshFactory::Order("Cruiser", "Cruiser", "RustedMaterial", maths::mat4::Translation(maths::vec3(0, 0, -500)) * maths::mat4::Rotation(maths::PI, maths::vec3(0, 1, 0)));
		MeshFactory::Order("Terrain", "Terrain", "TerrainMaterial");
		MeshFactory::Order("Bridge", "Bridge", "Default", maths::mat4::Translation(16.7f, 0, 0) * maths::mat4::Rotation(maths::PI / 2, maths::vec3(0, 1, 0)));
		MaterialFactory::RequestPBR("GrassMaterial")->AddUniform<float>("tiling", 100);

		Camera* camera = new Camera(window->GetViewport(), maths::vec3(0, 100, 0), maths::mat4::Identity(), Projection::Perspective, maths::PI / 6.0, Angle::Radians, 1.0f, 3000.0f);
		camera->AddComponent(new Components::RigidBody(1, false, maths::vec3(0.0f, 0.0f, 0.0f), maths::vec3(0.0f)));
		camera->AddComponent(new Components::Collider(OBB(maths::vec3(2.5f, 3.0f, 2.5f))));

		GameObject* floor = new GameObject(0, 0, 0);
		floor->SetMesh("Terrain");
		floor->Identifier()->SetName("Terrain");

		GameObject* bridge = new GameObject(850, -55, 650);
		bridge->Transform()->SetScale(40);
		bridge->Transform()->Rotate(-50, maths::vec3(0, 1, 0), Space::World, Angle::Degrees);
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
		water->SetMesh(MeshFactory::Build("Water", ModelFactory::BuildTile("Water", maths::vec2(10000), Color(200, 200, 255, 255)), "Water"));
		water->AddComponent(new Components::RigidBody(1, true, maths::vec3(0.0f), maths::vec3(0.0f), false));
		water->AddComponent(new Components::Collider(OBB(maths::vec3(10000, 0, 10000))));

		Layer* uiLayer = new Layer("UI", new ForwardRenderer());
		Canvas* canvas = new Canvas(window, Origin::TopLeft);
		uiLayer->SetCamera(canvas);

		Panel* crosshair = new Panel(WindowWidth() / 2, -WindowHeight() / 2, maths::vec2(4), Color::Black());
		crosshair->SetColor(Color::Red());

		Text* text = new Text(65, -25, "Test Text", FontFactory::Request("Arial", 24));
		text->Identifier()->SetName("Text");

		GameObject* sun = new GameObject(0, 1000, 0);
		sun->AddComponent(new Components::Light(LightType::Point, Color::White()));

		GLStates::EnableClipDistance(0);
	}

	void Tick() override
	{
		WindowHandle()->SetTitle("Ablaze: " + std::to_string(Time::AverageFPS()) + " FPS");
		((Text*)GameObjects::GetWithName("Text"))->SetText(std::to_string(Time::AverageFPS()) + " FPS");
	}

	void Update() override
	{		
		Camera* cam = Camera::Main();
		Components::Transform* t = cam->Transform();
		Components::RigidBody* r = cam->GetComponent<Components::RigidBody>();

		*movefactor += 0.001f;

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
		Camera* cam = Camera::Main();
		maths::vec3 position = cam->Transform()->GetPosition();
		position.y *= -1;
		Camera* reflectionCamera = cam->Clone(position, maths::mat4::InvertY(cam->Transform()->GetRotation()));
		reflectionTexture->SetCamera(reflectionCamera);
		refractionTexture->Create();
		reflectionTexture->Create();
		reflectionCamera->Destroy();

		tempUniforms.UploadAll(ShaderManager::GetAllShaders());

		Application::Render();
		UpdateDisplay();
	}

	static maths::vec3 CalculateVector(const maths::vec3& vector)
	{
		maths::vec3 vec = vector;
		vec.y = 0;
		return vec.Normalize();
	}

	void Test(const Event& e)
	{
		AB_INFO(e.ToString());
	}

};

int main()
{
	Game* game = new Game();
	game->Start();
	delete game;

	return 0;
}