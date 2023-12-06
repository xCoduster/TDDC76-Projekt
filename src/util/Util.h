#pragma once

#include <vector>
#include <string>
#include <utility>

int random(int min, int max);

std::vector<std::pair<std::string, int>> readScore(const std::string& filePath);

bool compareScore(std::pair<std::string, int> left, std::pair<std::string, int> right);

template <typename T>
void clearVector(std::vector<T*>& pointers)
{
	for (std::size_t i{ 0 }; i < pointers.size(); ++i)
	{
		std::swap(pointers.at(i), pointers.back());
		delete pointers.back();
		pointers.pop_back();
		--i;
	}
}