/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** GUIConfig.hpp
*/
#ifndef GUICONFIG_HPP_
	#define GUICONFIG_HPP_

#include <string>
#include <libconfig.h++>
#include <iostream>
using namespace std;

struct themeData {
    int id;
    string name;
};

class GUIConfig {
	public:
		GUIConfig();
		~GUIConfig();
        void setResolution(pair<int, int> res);
        void setTitle(string title);
        void setFPS(int fps);
        void setTheme(themeData theme);
        pair<int, int> getResolution() const;
        string getTitle() const;
        int getFPS() const;
        themeData getTheme() const;
        void load(const libconfig::Setting& guiSetting);
        void print();


	protected:
    pair<int, int> res;
    string title;
    int fps;
    themeData theme;
	private:
};

#endif /*GUICONFIG_HPP_*/