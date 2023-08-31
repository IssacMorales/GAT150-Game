#pragma once
#include "RenderComponent.h"
#include <Renderer/Model.h>
#include "Framework/Factory.h"
#include "Framework/Source/Resource/ResourceManager.h"

namespace kiko
{

	class ModelRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool Initialize();
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
		
		//errorHere
		virtual float GetRadius() override { return m_model->GetRadius(); }

	public:
		res_t<Model> m_model;
		std::string modelName;
	};
}