#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Framework/Source/Resource/ResourceManager.h"
#include "Renderer/Text.h"
#include "Renderer/ParticleSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "Renderer/Texture.h"

#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <Framework/Components/SpriteRenderComponent.h>
#include <Framework/Components/CircleCollisionComponent.h>
#include <Physics/PhysicsSystem.h>

using namespace std;

class Star
{
public:
	Star(const kiko::vec2& pos, const kiko::vec2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::vec2 m_pos;
	kiko::vec2 m_vel;
};

int main(int argc, char* argv[])
{

	kiko::Factory::Instance().Register<kiko::SpriteRenderComponent>("SpriteRenderComponent");
	kiko::Factory::Instance().Register<kiko::CircleCollisionComponent>("CircleCollisionComponent");

	INFO_LOG("Initialize Engine...")

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	rapidjson::Document document;
	kiko::Json::Load("json.txt", document);


	int i1;
	kiko::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	kiko::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;

	std::string str;
	kiko::Json::Read(document, "string", str);
	std::cout << str << endl;

	bool b;
	kiko::Json::Read(document, "boolean", b);
	std::cout << b << endl;

	float f;
	kiko::Json::Read(document, "float", f);
	std::cout << f << endl;

	kiko::vec2 v2;
	kiko::Json::Read(document, "vector2", v2);
	std::cout << v2 << endl;

	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();

	// create game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	//create texture
	kiko::res_t<kiko::Texture> texture = GET_RESOURCE(kiko::Texture, "Ship_1_C_Small.png", kiko::g_renderer);

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// main game loop
	bool quit = false;

	while (!quit)
	{
		// update engine
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::PhysicsSystem::Instance().Update(kiko::g_time.GetDeltaTime());

		// update game
		game->Update(kiko::g_time.GetDeltaTime());

		// draw game
		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());
			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			star.Draw(kiko::g_renderer);
		}
		kiko::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		game->Draw(kiko::g_renderer);
		
		kiko::g_renderer.EndFrame();
	}

	stars.clear();

	return 0;
}
/*
		if (kiko::g_inputSystem.GetMouseButtonDown(0) &&
			!kiko::g_inputSystem.GetPreviousMouseButtonDown(0))
		{
			kiko::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = kiko::Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;

			data.color = kiko::Color{ 1, 1, 1, 1 };

			kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0, 1};
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			scene.Add(std::move(emitter));
		}
*/