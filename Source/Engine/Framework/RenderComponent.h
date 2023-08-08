#pragma once
#include "Components/Component.h"

namespace kiko 
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}
