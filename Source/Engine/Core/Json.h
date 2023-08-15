#pragma once
#include "Math/Vector2.h"
//#include <rapidjson/include/rapidjson/document.h>
#include <string>

#define READ_DATA(value, data) kiko::Json::Read(value, #data, data);