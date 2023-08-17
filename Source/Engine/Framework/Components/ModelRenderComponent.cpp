#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(ModelRenderComponent)
	void kiko::ModelRenderComponent::Update(float dt)
	{
	}

	bool ModelRenderComponent::Initialize()
	{
		if (!modelName.empty()) m_model = GET_RESOURCE(Model, modelName, g_renderer);

		return true;
	}

	void kiko::ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transform);
	}

	void ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}

}