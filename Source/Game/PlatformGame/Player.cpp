#include "Player.h"
#include "PlatformGame.h"
#include "Framework/Framework.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"

namespace kiko
{
	CLASS_DEFINITION(Player)

	bool Player::Initialize()
	{
		Actor::Initialize();

		//cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();

		/*auto collisionComponent = GetComponent<CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = GetComponent<RenderComponent>()->GetRadius() * scale;
			}

		}*/

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);
		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;

		// movement
		float dir = 0;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		if (dir)
		{
			velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}
		// jump

		if (onGround && 
			 g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			vec2 up = vec2{0, -1};
			m_physicsComponent->SetVelocity(velocity + (up * jump));
		}

		m_physicsComponent->SetGravityScale((velocity.y > 0) ? 5.0f : 4.0f);


		//animation
		//check if moving
		if (std::fabs(velocity.x) > 0.2f && onGround)
		{
			m_spriteAnimComponent->flipH = (dir < -0.1f);
			m_spriteAnimComponent->SetSequence("run");
		}
		else if (std::fabs(velocity.y) > 0.2f) {
			m_spriteAnimComponent->SetSequence("jump");
		}
		else
		{
			m_spriteAnimComponent->SetSequence("idle");
		}

		

	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy")
		{
			destroyed = true;
			//EVENT_DISPATCH("OnPlayerDead", 0);
		}
		if (other->tag == "Ground") groundCount++;
		if (other->tag == "Coin")
		{
			destroyed = true;
		}
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag != "Ground") groundCount--;
	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);
		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
	}


}