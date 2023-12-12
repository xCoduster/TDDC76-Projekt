#pragma once



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
	BossData(float fireRate) : fireRate{fireRate} {}

	float fireRate;
};