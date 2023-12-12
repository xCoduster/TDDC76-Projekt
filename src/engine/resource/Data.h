#pragma once

#include <json/json.h>

struct Data
{
	virtual ~Data() = default;

	enum class Type
	{
		Bomb,
		Boss,
		EnemyProjectile,
		Projectile,
		Player,
		PowerUp,
		Seeker,
		Star,
		UFO
	};
};

struct BossData : public Data
{
	BossData(const Json::Value& value) 
	{
		hp = value["hp"].asInt();
		speed1 = value["speed1"].asFloat();
		speed2 = value["speed2"].asFloat();
	}

	int hp;
	float speed1;
	float speed2;
};

struct EnemyData : public Data
{
	EnemyData(const Json::Value& value)
	{
		hp = value["hp"].asInt();
		speed = value["speed"].asFloat();
	}

	int hp;
	float speed;
};

struct ProjectileData : public Data
{
	ProjectileData(const Json::Value& value)
	{
		speed = value["speed"].asFloat();
	}

	float speed;
};

struct PlayerData : public Data
{
	PlayerData(const Json::Value& value)
	{
		fireRate = value["fireRate"].asFloat();
		hp = value["hp"].asInt();
		speed = value["speed"].asFloat();
	}

	float fireRate;
	int hp;
	float speed;
};

struct PowerUpData : public Data
{
	PowerUpData(const Json::Value& value)
	{
		lifeTime = value["lifeTime"].asFloat();
	}

	float lifeTime;
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
