#pragma once
#include "Singleton.h"
#include <memory>
#include <map>
#include <string>

namespace kiko
{
    template <typename T>
    class Singleton
    {
    public:
        Singleton(const Singleton& other) {}
        Singleton& operator = (const Singleton& other) {}

        static T& Instance()
        {
            static T instance;
            return instance;
        }

    protected:
        Singleton() = default;
    };
}