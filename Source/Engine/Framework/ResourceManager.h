#pragma once
#include "Resource.h"
#include <string>
#include <map>
#include <memory>

namespace kiko
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;

		void Add(const std::string& id, const std::string& filename);
		std::shared_ptr<Resource> Get(const std::string& id);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;
	};
}