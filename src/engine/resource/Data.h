#pragma once

#include <json/json.h>

struct Data
{
	virtual ~Data() = default;

	enum class Type
	{
		Boss,
		Star
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

struct StarData : public Data
{
	StarData(const Json::Value& value) 
	{
		greenSpeed = value["greenSpeed"].asFloat();
		blueSpeed = value["blueSpeed"].asFloat();
		redSpeed = value["redSpeed"].asFloat();
		scale = value["scale"].asFloat();
	}

	float greenSpeed;
	float blueSpeed;
	float redSpeed;

	float scale;
};