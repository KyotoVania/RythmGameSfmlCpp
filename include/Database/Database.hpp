/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Database.hpp
*/
#ifndef DATABASE_HPP_
	#define DATABASE_HPP_
#include "Beatmap/BeatmapConfig.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <map>
using namespace std;

class Database {
	public:
        Database();
        ~Database();
        void load(const std::string& file);
        void print();
        bool isBeatmapExist(int id);
        int getNbBeatmaps() const { return beatmaps.size(); }
        BeatmapConfig getBeatmap(int id) { return beatmaps[id]; }
	protected:
        map<int, BeatmapConfig> beatmaps;
	private:
};

#endif /*DATABASE_HPP_*/