#pragma once

#include <json/json.h>

struct Data
{
	virtual ~Data() = default;

	enum class Type
	{
		Boss
	};
};

struct BossData : public Data
{
	BossData(const Json::Value& value) 
	{
		hp = value["hp"].asInt();
	}

	int hp;
};