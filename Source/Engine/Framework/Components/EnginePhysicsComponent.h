#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public: 
		CLASS_DECLARATION(EnginePhysicsComponent)

		virtual void Update(float dt);
		virtual void ApplyForce(const vec2& force);
		void ApplyTorque(float torque) override;
	};
}