/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Core.hpp
*/
#ifndef CORE_HPP_
	#define CORE_HPP_

#include <SFML/Graphics.hpp>
#include "Menu/Menu.hpp"
#include "GUI/GUI.hpp"
#include "Config/Config.hpp"
#include "Database/Database.hpp"

class Core {
	public:
		Core();
		~Core();
	protected:
	private:
        Menu menu;
        GUI gui;
        //Config config;
        Database database;

};

#endif /*CORE_HPP_*/