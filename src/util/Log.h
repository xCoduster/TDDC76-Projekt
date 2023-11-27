#pragma once

#include <iostream>

#include <SFML/System/Vector2.hpp>

#define NO_LOG			0
#define ERROR_LEVEL		1
#define INFO_LEVEL		2
#define DEBUG_LEVEL		3

#ifndef LOG_LEVEL
	#define LOG_LEVEL	DEBUG_LEVEL
#endif

#if LOG_LEVEL >= DEBUG_LEVEL
	#define LOG_DEBUG(...)     std::cout << "[DEBUG]: " << __VA_ARGS__ << std::endl
#else
	#define LOG_DEBUG(...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
	#define LOG_INFO(...)      std::cout << "[INFO]: " << __VA_ARGS__ << std::endl
#else
	#define LOG_INFO(...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
	#define LOG_ERROR(...)     std::cout << "[ERROR]: " << __VA_ARGS__ << std::endl
#else
	#define LOG_ERROR(...)
#endif

// T: int, unsigned int, float
template <typename T>
std::ostream& operator<<(std::ostream& os, sf::Vector2<T> rhs)
{
	os << "(" << rhs.x << ", " << rhs.y << ")";
	return os;
}