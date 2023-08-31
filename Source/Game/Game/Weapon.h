#pragma once
#include "Framework/Actor.h"

namespace kiko
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0;
		class PhysicsComponent* m_physicsComponent = nullptr;
	};
}
