#pragma once
#include "Singleton.h"
#include <memory>
#include <map>
#include <string>
namespace kiko
{
    class CreatorBase
    {
    public:
        virtual ~CreatorBase() = default;

        virtual std::unique_ptr<class Object>Create() = 0;

        static T& Instance() 
        {

        }
    }

    template <typename T>
    class Creator : public CreatorBase
    {
    public:
        std::unique_ptr<class Object> Create() override
        {
            return std::make_unique<T>();
        }
    };
}