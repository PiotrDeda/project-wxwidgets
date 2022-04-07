#pragma once

#include <functional>

/**
 * @brief Struktura reprezentująca komendę
 */
struct Command
{
	/**
	 * @brief Konstruktor komendy
	 *
	 * @param n { parameter_description }
	 * @param c { parameter_description }
	 */
	Command(std::string n, std::function<void(std::vector<std::string>)> c) : name(n), command(c) {}
	std::string name;
	std::function<void(std::vector<std::string>)> command;
};