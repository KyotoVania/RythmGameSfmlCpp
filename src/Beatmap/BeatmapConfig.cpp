/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** BeatmapConfig.cpp
*/

#include "Beatmap/BeatmapConfig.hpp"

BeatmapConfig::BeatmapConfig()
{
}

BeatmapConfig::~BeatmapConfig()
{
}

void BeatmapConfig::load(const libconfig::Setting& beatmapSetting) {
    beatmapSetting.lookupValue("Name", Name);
    beatmapSetting.lookupValue("Artist", Artist);
    beatmapSetting.lookupValue("FolderPath", FolderPath);
    beatmapSetting.lookupValue("Difficulty", Difficulty);
    beatmapSetting.lookupValue("BPM", BPM);
    beatmapSetting.lookupValue("id", id);
    beatmapSetting.lookupValue("offset", offset);
}

void BeatmapConfig::print()
{
    std::cout << "Name: " << Name << std::endl;
    std::cout << "Artist: " << Artist << std::endl;
    std::cout << "FolderPath: " << FolderPath << std::endl;
    std::cout << "Difficulty: " << Difficulty << std::endl;
    std::cout << "BPM: " << BPM << std::endl;
    std::cout << "id: " << id << std::endl;
    std::cout << "offset: " << offset << std::endl;
}