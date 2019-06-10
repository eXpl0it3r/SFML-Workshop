#include "Sokoban.hpp"
#include <iostream>

int main()
{
	try
	{
		auto game = Sokoban{};
		game.run();
	}
	catch (std::exception& exception)
	{
		std::cerr << "Sokoban encountered an unrecoverable error and will be terminated:\n";
		std::cerr << exception.what() << "\n";
	}
}
