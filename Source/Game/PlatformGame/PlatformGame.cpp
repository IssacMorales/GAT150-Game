#include "PlatformGame.h"
#include "Player.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

using namespace kiko;

bool PlatformGame::Initialize()
{

	// load audio
	//kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scenes/PlatformScene.json");
	m_scene->Load("scenes/tilemap.json");
	m_scene->Initialize();

	m_scene->GetActorByName("Title")->active = false;

	//add events
	EVENT_SUBSCRIBE("AddPoints", PlatformGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::AddPoints);

	return true;
}

void PlatformGame::Shutdown()
{
}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	//case PlatformGame::eState::Title:
		//auto actor = INSTANTIATE(kiko::Actor, "Crate");
		//actor->transform.position = { kiko::random(kiko::g_renderer.GetWidth()), 100 };
		//actor->Initialize();
		//m_scene->Add(std::move(actor));
		//break;

	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		
		break;

	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
		// Tried to spawn coins everywhere but it didn't work, I am sad...
		/*m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTime >= m_spawnTime)
		{
			
			m_spawnTimer = 0;
			std::unique_ptr<Actor> enemy = std::make_unique<Actor>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 0.5f});
			enemy->tag = "Coin";
		}*/
		break;

	case eState::PlayerDeadStart:
		
		break;

	case PlatformGame::eState::PlayerDead:
		break;
	case PlatformGame::eState::GameOver:
		
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void PlatformGame::Draw(kiko::Renderer& renderer)
{
	
	m_scene->Draw(renderer);
}

void PlatformGame::AddPoints(const kiko::Event& event)
{
	m_score += std::get<int>(event.data);

}

void PlatformGame::OnPlayerDead(const kiko::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
