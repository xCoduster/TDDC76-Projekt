#include "Util.h"

#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>

int random(int min, int max)
{
	int range = max - min + 1;

	if (range == 0)
		return 0;

	return min + std::rand() % range;
}

std::vector<std::pair<std::string, int>> readScore(const std::string& filePath)
{
	std::ifstream file{ filePath };
	std::string line{};
	std::vector<std::pair<std::string, int>> scores{};

	std::string name{};
	int score{ 0 };

	while (std::getline(file, line))
	{
		name = line.substr(0, line.find(','));
		score = stoi(line.substr(line.find(',') + 1, line.size()));
		scores.push_back(std::make_pair(name, score));
	}

	return scores;
}

bool compareScore(std::pair<std::string, int> left, std::pair<std::string, int> right)
{
	return (left.second < right.second);
}