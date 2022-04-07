#pragma once

#include <string>

/**
 * @brief Struktura reprezentująca liczbę
 */
struct Number
{
	Number(double v) : value(v) {}
	double value;
};

/**
 * @brief Struktura reprezentująca pare liczb
 */
struct Pair
{
	Pair(double v1, double v2) : value1(v1), value2(v2) {}
	double value1, value2;
};

/**
 * @brief Struktura reporezentująca trzy liczby
 */
struct Triplet
{
	Triplet(double v1, double v2, double v3) : value1(v1), value2(v2), value3(v3) {}
	double value1, value2, value3;
};

/**
 * @brief Struktura reprezentująca nazwę
 */
struct Name 
{
	Name(std::string v) : value(v) {}
	std::string value;
};