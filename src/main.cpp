#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Config/Config.hpp"
#include "Database/Database.hpp"
#include "GUI/GUI.hpp"
#include "Visualizer/Vizualizer.hpp"
#include <iostream>
#include <future>
#include <thread>
using namespace std;

void loadConfigAndDatabase(Config& config, Database& database) {
    cout << "loading config" << endl;
    config.load("config/game.cfg");
    cout << "loaded config" << endl;
    config.print();
    cout << "printed config" << endl;

    cout << "loading database" << endl;
    database.load("config/Database.cfg");
    cout << "loaded database" << endl;
    for (int i = 0; i < database.getNbBeatmaps(); ++i) {
        database.isBeatmapExist(i);
    }
    cout << "checked database" << endl;
    database.print();
    cout << "printed database" << endl;
}

void applyConfig(const Config& config, GUI& gui) {
    gui.load(config.getGUIConfig());
    cout << "loaded gui" << endl;
    gui.loadingScreenCreate();

    // Start loading assets in a separate thread
    auto future = std::async(std::launch::async, [&gui](){
        for (int i = 0; i <= 100; i++) {
            // Simulate loading assets
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            gui.updateLoadingScreen(i);
            if (i == 10) {
                gui.createMenu();
            }
        }
        // Create the menu after loading assets
    });

    // Wait for the loading to finish
    future.wait();
    cout << "loaded assets" << endl;
    // Start the main loop
    //for the moment, the menu is the main loop
    gui.loop();
}



int main (int argc, char** argv)
{
    Config config;
    GUI gui;
    Database database;
    loadConfigAndDatabase(config, database);
    applyConfig(config, gui);
    //Game game (argv, argc);
    //game.run();
    std::cout << "vizualizer ran" << std::endl;
    return 0;
}
