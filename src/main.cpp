#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Core/Core.hpp"


int main(int argc, char** argv) {
    Core core;
    core.run();
    std::cout << "vizualizer ran" << std::endl;
    return 0;
}
