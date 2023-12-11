#include "DataManager.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "util/Log.h"

#include <json/json.h>

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
    std::ifstream config_doc(filePath, std::ifstream::binary);
    config_doc >> root;

    data[Data::Type::Boss] = new BossData{ root["Boss"] };

    data[Data::Type::Star] = new StarData{ root["Star"] };

}