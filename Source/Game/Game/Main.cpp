#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
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
#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <Framework/Source/Resource/ResourceManager.cpp>

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

template<typename T>
void print(const std::string& s, const T& container) {
	std::cout << s << std::endl; for(auto element : container)
	{
		std::cout << element << "";
	}
	std::cout << std::endl;
}

void print_arg(int count, ...)
{
	va_list args;

	va_start(args, count);
	for (int i = 0; i < count; ++i)
	{
		std::cout << va_arg(args, const char*) << std::endl;
	}
	va_end(args);
}



int main(int argc, char* argv[])
{
	/*int n[4] = { 1, 2, 3, 4 };
	print("array class: ", n);
	cout << n << endl;
	cout << *(n + 3) << endl;

	std::array<int, 4> na = { 1, 2, 3, 4 };
	print("array class: ", na);
	cout << na.front() << endl;
	cout << na.back() << endl;
	cout << na.max_size() << endl;

	std::vector<int> nv = { 1, 2, 3, 4 };
	print("vector class: ", nv);
	nv.insert(nv.begin(), 0);
	nv.push_back(5);
	nv.pop_back();
	auto iter = nv.erase(nv.begin(), nv.end());
	print("vector: ", nv);
	

	std::list<int> nl = { 1, 2, 3, 4 };
	print("list class: ", nl);
	nl.push_front(0);
	print("list class: ", nl);

	std::map<std::string, int> ages;
	ages["Charles"] = 17;
	ages["Xane"] = 18;
	ages["Jacob"] = 19;

	cout << ages["Charles"] << endl;
	cout << ages["Xane"] << endl;*/


	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();

	// create game
	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	//create texture
	kiko::res_t<kiko::Texture> texture = kiko::g_resourceM.Get<kiko::Texture>("Ship_1_C_Medium.png", kiko::g_renderer);

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::Vector2(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight())));
		kiko::Vector2 vel(kiko::randomf(100, 200), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// main game loop
	bool quit = false;
	
	//texture->Load("Ship_1_C_Medium.png", kiko::g_renderer);

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
		game->Draw(kiko::g_renderer);
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		
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