#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Vizualizer.hpp"

int main (int argc, char** argv)
{
	//create a unique pointer to the game
	Game game (argv, argc);
	//run the game
	game.run();
	std::cout << "vizualizer ran" << std::endl;
	
	return 0;
}
