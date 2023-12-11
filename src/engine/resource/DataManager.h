#pragma once

#include <map>
#include <memory>
#include <string>

#include "Data.h"

class DataManager
{
public:
	static DataManager& instance()
	{
		static DataManager instance;
		return instance;
	}

	Data* getData(const Data::Type& type);

private:
	DataManager();

	void readFile(const std::string& filePath);

	std::map<Data::Type, Data*> data;
};

