#include "DataManager.h"

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
}