/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** FFT_Menu.hpp
*/
#ifndef FFT_MENU_HPP_
	#define FFT_MENU_HPP_
#include "Visualizer/FFT.hpp"

class FFT_Menu : public WithFFT {
	public:
		FFT_Menu();
		~FFT_Menu();
        int getCalculatedDifficulty();
        void setCalculatedDifficulty(int calculatedDifficulty);
        void setDifficulty(int difficulty);
        void analyzeEntireSong(const std::string& songPath);
        void loadMusicMenu(const std::string& beatmapPath);
        int calculate_song_difficulty();
        protected:
	private:
};

#endif /*FFT_MENU_HPP_*/