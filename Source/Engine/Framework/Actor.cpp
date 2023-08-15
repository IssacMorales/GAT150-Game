#include "Actor.h"
#include "RenderComponent.h"

namespace kiko
{
	CLASS_DEFINITION(Actor);

	bool Actor::Initialize()
	{
		for (auto& component : m_components)
		{
			component->Initialize();
		}

		return true;
	}

	bool Actor::OnDestroy()
	{
		for (auto& component : m_components)
		{
			component->OnDestroy();
		}
	}


	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : m_components)
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(kiko::Renderer& renderer)
	{
		//if (m_model) m_model->Draw(renderer, m_transform);
		for (auto& component : m_components)
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

	bool Actor::Read(const rapidjson::Value& value)
	{
		return true;
	}
}
