#pragma once

#include <vector>
#include <string>
#include <utility>

int random(int min, int max);

std::vector<std::pair<std::string, int>> readScore(const std::string& filePath);
bool compareScore(std::pair<std::string, int> left, std::pair<std::string, int> right);
