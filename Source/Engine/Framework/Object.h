#pragma once
#include "Factory.h"
#include "Core/Json.h"
#include <string>

#define CLASS_DELCARATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
	virtual void Read(const json_t& value); \
	class Register \
	{ \
		public: \
		Register()\
		{ \
			Factory::Instance().Register<classname>(#classname); \
		}\
	};

#define CLASS_DEFINITION(classname) \
	classname::Register register_class;

namespace kiko
{
	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name) : name{ name } {}
		virtual ~Object() { OnDestroy(); }

		CLASS_DELCARATION(Object)

		virtual bool Initialize() { return true; }
		virtual void OnDestroy() {}

	protected:
		std::string name;

	};
}