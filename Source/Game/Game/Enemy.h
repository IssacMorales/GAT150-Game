#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace kiko
{
	class Enemy : public Actor
	{
	public:

		CLASS_DECLARATION(Enemy)

		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;

		float m_fireRate = 0;
		float m_fireTimer = 0;

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}