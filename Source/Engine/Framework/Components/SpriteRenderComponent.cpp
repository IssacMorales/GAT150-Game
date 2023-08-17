#include "SpriteRenderComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Source/Resource/ResourceManager.h"

namespace kiko
{
	CLASS_DEFINITION(SpriteRenderComponent)

	bool SpriteRenderComponent::Initialize()
	{
		m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void kiko::SpriteRenderComponent::Update(float dt)
	{
	}

	void kiko::SpriteRenderComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform);
	}

	void SpriteRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, textureName);
	}
}

