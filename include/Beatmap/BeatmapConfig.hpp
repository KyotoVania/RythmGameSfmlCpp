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
using namespace std;
class BeatmapConfig {
	public:
        BeatmapConfig();
        ~BeatmapConfig();

	protected:
        string Name;
        string Artist;
        string FolderPath;
        int Difficulty;
        int BPM;
        int id;
        int offset;
	private:
};

#endif /*BEATMAPCONFIG_HPP_*/