#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include <Framework/Source/Resource/ResourceManager.h>
#include <Framework/Components/PhysicsComponent.h>

bool Player::Initialize()
{
	Actor::Initialize();

	//cache off
	m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if(renderComponent)
		{
			float scale = transform.scale;
			//errorHere
			collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
		}
		
	}

	return false;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	// movement
	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	//transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();
	m_physicsComponent->ApplyTorque(rotate * turnRate);

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	//m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	transform.position.x = kiko::Wrap(transform.position.x, (float)kiko::g_renderer.GetWidth());
	transform.position.y = kiko::Wrap(transform.position.y, (float)kiko::g_renderer.GetHeight());

	// fire weapon
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket");
		weapon->transform = { transform.position, transform.rotation + kiko::DegreesToRadians(10.0f), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		weapon = INSTANTIATE(Weapon, "Rocket");
		weapon->transform = { transform.position, transform.rotation - kiko::DegreesToRadians(10.0f), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	}
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);

}

void Player::OnCollision(Actor* other)
{
	if (other->tag == "Enemy")
	{
		destroyed = true;
		kiko::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);

		//m_game->SetLives(m_game->GetLives() - 1);
		//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
	}
}

