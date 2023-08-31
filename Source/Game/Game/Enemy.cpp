#include "Enemy.h"
#include "Player.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	bool Enemy::Initialize()
	{
		CLASS_DEFINITION(Enemy)
			Actor::Initialize();

		m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
		//cache off
		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<kiko::RenderComponent>()->GetRadius() * scale;
			}

		}

		return true;
	}
	void Enemy::OnDestroy()
	{
		Actor::OnDestroy();
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		vec2 forward = vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			vec2 direction = player->transform.position - transform.position;
			// turn towards player		
			float turnAngle = vec2::SignedAngle(forward, direction.Normalized());
			m_physicsComponent->ApplyTorque(turnAngle);

			// check if player is in front
			if (std::fabs(turnAngle) < DegreesToRadians(30.0f))
			{
				// I see you!
			}
		}
		m_physicsComponent->ApplyForce(forward * m_speed);

		//transform.position += forward * m_speed * g_time.GetDeltaTime();
		transform.position.x = Wrap(transform.position.x, (float)g_renderer.GetWidth());
		transform.position.y = Wrap(transform.position.y, (float)g_renderer.GetHeight());


	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Player")
		{
			EventManager::Instance().DispatchEvent("AddPoints", 100);
			//m_game->AddPoints(100);
			destroyed = true;

			// create explosion
			EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 0;
			data.angle = 0;
			data.angleRange = Pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;

			data.color = Color{ 1, 1, 1, 1 };

			Transform transform{ this->transform.position, 0, 1};
			auto emitter = std::make_unique<Emitter>(transform, data);
			emitter->lifespan = 0.1f;
			m_scene->Add(std::move(emitter));

		}
	}
}
