#pragma once
#include "Factory.h"
//#include "Core/Json.h"
#include <string>

#define CLASS_DELCARATION(classname) \
	virtual const char* GetClassName() { return #classname; } \
	/*bool Read(const rapidjson::Value& value) \*/
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
		Object(const std::string& name) : m_name{ name } {}
		virtual ~Object() { OnDestroy(); }

		CLASS_DELCARATION(object);

		virtual bool Initialize() { return true; }
		virtual bool OnDestroy() {}

	protected:
		std::string m_name;

	};
}