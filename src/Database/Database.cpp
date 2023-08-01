/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** Database.cpp
*/

#include "Database/Database.hpp"

Database::Database()
{
}

Database::~Database()
{
}

void Database::load(const std::string& file) {
    libconfig::Config cfg;

    // Read the file. If there is an error, report it and exit.
    try {
        cfg.readFile(file.c_str());
    }
    catch(const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return;
    }
    catch(const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return;
    }

    // Get the songs configuration
    const libconfig::Setting& songs = cfg.lookup("songs");
    for (int i = 0; i < songs.getLength(); ++i) {
        BeatmapConfig beatmapConfig;
        beatmapConfig.load(songs[i]);
        beatmaps[beatmapConfig.id] = beatmapConfig;
    }
}

void Database::print()
{
    for (auto it = beatmaps.begin(); it != beatmaps.end(); ++it) {
        it->second.print();
    }
}

bool Database::isBeatmapExist(int id) {
    auto it = beatmaps.find(id);
    if (it == beatmaps.end()) {
        cout << "Beatmap not found in the database" << endl;
        // Beatmap not found in the database
        return false;
    }

    std::filesystem::path path("Resources/Beatmaps/" + it->second.getFolderPath());
    if (!std::filesystem::exists(path)) {
        cout << "Beatmap folder does not exist" << endl;
        // Beatmap folder does not exist
        beatmaps.erase(it);
        return false;
    }

    // Beatmap exists in the database and its folder exists
    return true;
}
