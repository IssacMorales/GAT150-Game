#include "PlatformGame.h"

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"

#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <Framework/Components/SpriteRenderComponent.h>
#include <Framework/Components/CircleCollisionComponent.h>
#include <Framework/Source/Resource/ResourceManager.h>



using namespace std;

int main(int argc, char* argv[])
{

	kiko::Factory::Instance().Register<kiko::SpriteRenderComponent>("SpriteRenderComponent");
	//kiko::Factory::Instance().Register<kiko::CircleCollisionComponent>("CircleCollisionComponent");

	INFO_LOG("Initialize Engine...")

	kiko::MemoryTracker::Initialize();
	kiko::seedRandom((unsigned int)time(nullptr));
	//kiko::setFilePath("assets/platformer");


	// initialize engine
	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();
	kiko::PhysicsSystem::Instance().Initialize();

	// create game
	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	//create texture
	//kiko::res_t<kiko::Texture> texture = GET_RESOURCE(kiko::Texture, "Character.png", kiko::g_renderer);

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

		//kiko::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);
		kiko::g_particleSystem.Draw(kiko::g_renderer);
		game->Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();
	}

	return 0;
}
