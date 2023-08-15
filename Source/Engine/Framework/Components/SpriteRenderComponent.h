#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace kiko
{
	class SpriteRenderComponent : public RenderComponent
	{
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() { return m_texture->GetSize().Length() * 0.5; }

		class Register
		{
		public:
			Register()
			{

			}
		};

	public:
		res_t<Texture> m_texture;
	};
}