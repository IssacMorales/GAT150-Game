#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponent : public PhysicsComponent
	{
	public: 
		virtual void Update(float dt);
		virtual void ApplyForce(const vec2& force);
	};
}