/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Core.cpp
*/

#include "Core/Core.hpp"

Core::Core() {
    //we will set the tuple of gamestates
    //the first bool will be used to know if the transition is done
    //the first gamestate is the previous gamestate
    //the second is the current gamestate

    gameStates = std::make_tuple(false, GameState::EXIT, GameState::MENU);

    loadConfigAndDatabase();
    applyConfig();
}

Core::~Core() {

}


void Core::loadConfigAndDatabase() {
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

void Core::applyConfig() {
    gui.load(config.getGUIConfig());
    cout << "loaded gui" << endl;
    gui.loadingScreenCreate();

    // Start loading assets in a separate thread
    auto future = std::async(std::launch::async, [this](){
        for (int i = 0; i <= 100; i++) {
            // Simulate loading assets
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            gui.updateLoadingScreen(i);
            if (i == 10) {
                gui.createMenu();
            }
            if (i == 20) {
                gui.loadBeatmapPanel(database);
            }
        }
    });

    // Wait for the loading to finish
    future.wait();
    cout << "loaded assets" << endl;
    // Start the main loop
    // for the moment, the menu is the main loop
}

void Core::run() {
    gui.loop(std::get<2>(gameStates));
}

