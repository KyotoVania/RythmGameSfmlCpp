/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** GUIConfig.cpp
*/

#include "GUI/GUIConfig.hpp"

GUIConfig::GUIConfig() {
}

GUIConfig::~GUIConfig() {
}

void GUIConfig::load(const libconfig::Setting& guiSetting) {
    guiSetting.lookupValue("title", title);
    guiSetting.lookupValue("fps", fps);
    const libconfig::Setting& res = guiSetting["res"];
    res.lookupValue("width", this->res.first);
    res.lookupValue("height", this->res.second);
    const libconfig::Setting& theme = guiSetting["theme"];
    theme.lookupValue("id", this->theme.id);
    theme.lookupValue("name", this->theme.name);
}

void GUIConfig::print() {
    cout << "GUIConfig:" << endl;
    cout << "title: " << title << endl;
    cout << "fps: " << fps << endl;
    cout << "res: " << res.first << "x" << res.second << endl;
    cout << "theme: " << theme.id << " " << theme.name << endl;
}