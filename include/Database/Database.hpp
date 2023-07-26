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
#include <map>
using namespace std;

class Database {
	public:
        Database();
        ~Database();

	protected:
        map<int, BeatmapConfig> beatmaps;
	private:
};

#endif /*DATABASE_HPP_*/