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

    gameStates = std::make_tuple(true, GameState::ENDT, GameState::MENU, GameState::ENDT);

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
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    gui.setActive(false);

    // Start loading assets in a separate thread
    auto future = std::async(std::launch::async, [this](){
        gui.setActive(true);
        for (int i = 0; i <= 100; i++) {
            // Simulate loading assets
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            gui.updateLoadingScreen(i);
            if (i == 10) {
                //gui.createMenu(database);
                menu.load(make_pair(gui.getWindow().getSize().x, gui.getWindow().getSize().y), database);
            }
            if (i == 20) {
                game.loadTextures();
            }
            if (i == 30) {
                game.loadEntities();
            }
            if (i == 40) {
                game.loadTexts();
            }
        }
        gui.setActive(false);

    });

    // Wait for the loading to finish
    future.wait();
    gui.setActive(true);
    cout << "loaded assets" << endl;
    // Start the main loop
    // for the moment, the menu is the main loop
}

void Core::run() {
    while (gui.getWindow().isOpen()){
        sf::Event event = gui.getEvent();
        while (gui.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gui.getWindow().close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    gui.getWindow().close();
                }
            }
            if (event.type == sf::Event::Resized) {
                gui.getWindow().setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
            }
            updateState(event);

        }
        gui.getWindow().clear();
        drawState();
        //gui.drawState(std::get<2>(gameStates));
        gui.getWindow().display();
    }
}

void Core::updateState(sf::Event event) {
    //this function will update the state
    transition();
    //we will update the current gamestate
    switch (std::get<2>(gameStates)) {
        case GameState::MENU:
            if (menu.update(event, gui.getWindow()) == 1) {
                std::get<3>(gameStates) = GameState::GAME;
                std::get<0>(gameStates) = false;
            }
            //gui.updateMenu();
            break;
        case GameState::GAME:
            game.update();
            break;
        case GameState::EXIT:
            gui.getWindow().close();
            break;
        default:
            break;
    }
}

void Core::drawState() {
    //this function will draw the state
    switch (std::get<2>(gameStates)) {
        case GameState::MENU:
            menu.draw(gui.getWindow());
            break;
        case GameState::GAME:
            game.draw(gui.getWindow());
            break;
        case GameState::EXIT:
            gui.getWindow().close();
            break;
        default:
            break;
    }
}

void Core::transition() {
    //this function will do the transition
    //we will check if the transition is done
    if (std::get<0>(gameStates) == false) {
        //the transition is not done
        //we will update the transition
        std::get<0>(gameStates) = true;
        if (std::get<3>(gameStates) == GameState::GAME) {
            //we will update the gamestate
           // game.reset();
            game.setDifficulty(menu.getDifficulty());
            //game.loadBeatmap(menu.getActualSongName());
        } else {
            //we will update the gamestate
        }
        std::get<2>(gameStates) = std::get<3>(gameStates);
        std::get<1>(gameStates) = std::get<3>(gameStates);
        std::get<3>(gameStates) = GameState::ENDT;
    }
}