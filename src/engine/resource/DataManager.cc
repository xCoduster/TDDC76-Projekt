#include "DataManager.h"

#include <fstream>

#include "util/Log.h"

#include <json/json.h>

DataManager::~DataManager()
{
    for (auto const& element : data)
    {
        delete element.second;
    }

    data.clear();
}

Data* DataManager::getData(const Data::Type& type)
{
    auto dataIterator = data.find(type);
    if (dataIterator != data.end())
    {
        return dataIterator->second;
    }

    return new Data{};
}

DataManager::DataManager()
    : data{}
{
    readFile("res/data.json");
}

void DataManager::readFile(const std::string& filePath)
{
    Json::Value root;
    std::ifstream dataFile(filePath, std::ifstream::binary);
    dataFile >> root;

    data[Data::Type::Bomb] = new EnemyData{ root["Bomb"] };
    data[Data::Type::Boss] = new BossData{ root["Boss"] };
    data[Data::Type::EnemyProjectile] = new ProjectileData{ root["Projectile"]["Enemy"] };
    data[Data::Type::Projectile] = new ProjectileData{ root["Projectile"]["Player"] };
    data[Data::Type::Player] = new PlayerData{ root["Player"] };
    data[Data::Type::PowerUp] = new PowerUpData{ root["PowerUp"] };
    data[Data::Type::Seeker] = new EnemyData{ root["Seeker"] };
    data[Data::Type::UFO] = new EnemyData{ root["UFO"] };

    data[Data::Type::Star] = new StarData{ root["Star"] };

}