#pragma once
#include "Component.h"

namespace kiko
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollision(CollisionComponent* collision);
	public:
		float m_radius = 0;
	};
}