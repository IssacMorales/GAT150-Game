#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24);  //std::make_shared<kiko::Font>("arcadeclassic.ttf", 24);
	m_scoreText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24));
	m_scoreText->Create(kiko::g_renderer, "SCORE 0000", kiko::Color{ 1, 0, 1, 1 });

	m_titleText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24));
	m_titleText->Create(kiko::g_renderer, "AZTEROIDS", kiko::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24));
	m_gameoverText->Create(kiko::g_renderer, "GAME OVER", kiko::Color{ 1, 1, 1, 1 });

	m_timerText = std::make_unique<kiko::Text>(GET_RESOURCE(kiko::Font, "arcadeclassic.ttf", 24));
	m_timerText->Create(kiko::g_renderer, "TIMER", kiko::Color{ 1, 1, 1, 1 });

	// load audio
	kiko::g_audioSystem.AddAudio("hit", "hit.wav");

	// create scene
	m_scene = std::make_unique<kiko::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;

	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;

	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
		{
			//create player
			std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kiko::Pi, kiko::Transform{ { 400, 300 }, 0, 6 });
			player->tag = "Player";
			player->m_game = this;

			//create components
			auto renderComponent = CREATE_CLASS(SpriteRenderComponent);
			renderComponent->m_texture = GET_RESOURCE(kiko::Texture, "Ship_1_C_Small.png", kiko::g_renderer);
			player->AddComponent(std::move(renderComponent));

			auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
			physicsComponent->m_damping = 0.9f;
			player->AddComponent(std::move(physicsComponent));

			auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
			collisionComponent->m_radius = 30.0f;
			player->AddComponent(std::move(collisionComponent));

			player->Initialize();
			m_scene->Add(std::move(player));
		}
	m_state = eState::Game;
	break;
	case SpaceGame::eState::Game:
		m_gameTimer += dt;
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(75.0f, 150.0f), kiko::Pi, kiko::Transform{ { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::TwoPi), 3});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			std::unique_ptr<kiko::SpriteRenderComponent> component = std::make_unique<kiko::SpriteRenderComponent>();
			component->m_texture = GET_RESOURCE(kiko::Texture, "Enemy_2_B_Small.png", kiko::g_renderer);
			enemy->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;

	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), {1, 1, 1, 1});
	m_timerText->Create(kiko::g_renderer, std::to_string((int)m_gameTimer), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer & renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}
	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 400, 300);
	}

	m_timerText->Draw(renderer, 400, 40);
	m_scoreText->Draw(renderer, 40, 20);
	m_scene->Draw(renderer);
}
