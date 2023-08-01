/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** BeatmapConfig.hpp
*/
#ifndef BEATMAPCONFIG_HPP_
	#define BEATMAPCONFIG_HPP_

#include <string>
#include <map>
#include <iostream>
#include <libconfig.h++>
using namespace std;
class BeatmapConfig {
	public:
        BeatmapConfig();
        ~BeatmapConfig();
        void load(const libconfig::Setting& beatmapSetting);
        void print();
        int id;
        string getFolderPath() const { return FolderPath; }
        string getName() const { return Name; }
        string getArtist() const { return Artist; }
        int getDifficulty() const { return Difficulty; }
protected:
        string Name;
        string Artist;
        string FolderPath;
        int Difficulty;
        int BPM;
        int offset;
	private:

};

#endif /*BEATMAPCONFIG_HPP_*/