#include "Enemy.h"
#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include <Framework/Source/Resource/ResourceManager.h>
#include <Framework/Components/PhysicsComponent.h>
#include "Player.h"

namespace kiko
{
	CLASS_DEFINITION(Enemy)
	bool Enemy::Initialize()
	{
		Actor::Initialize();

		//cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		auto collisionComponent = GetComponent<CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				//errorHere
				collisionComponent->m_radius = GetComponent<RenderComponent>()->GetRadius() * scale;
			}

		}

		return false;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		// movement
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			kiko::vec2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			//EVENT_DISPATCH("OnEnemyDead", 0);
		}
		if (other->tag == "Ground") groundCount++;
	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}


}