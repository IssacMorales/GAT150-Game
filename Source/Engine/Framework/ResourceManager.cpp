#include "ResourceManager.h"

namespace kiko
{
    void ResourceManager::Add(const std::string& id, const std::string& filename)
    {
        if (m_resources.find(id) == m_resources.end())
        {
            m_resources[id] = std::make_shared<Resource>();

        }
    }

    std::shared_ptr<Resource> ResourceManager::Get(const std::string& id)
    {
        return std::shared_ptr<Resource>();
    }

}
