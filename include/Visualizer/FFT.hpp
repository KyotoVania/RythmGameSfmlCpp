/*
** EPITECH PROJECT, 2023
** newtry
** File description:
** FFT.hpp
*/
#ifndef FFT_HPP_
	#define FFT_HPP_
	#include <fstream>
	#include <iostream>
	#include <SFML/Graphics.hpp>
	#include <SFML/Audio.hpp>
	#include <complex>
	#include <valarray>
	#include <cmath>
	#include <vector>
	#include <string>
	#include <memory>
	#include <algorithm>
	#include <numeric>
	#include <functional>
	#include <utility>
	#include <array>
	#include <map>
	#include <set>
	using Complex = std::complex<double>;
	using ComplAr = std::valarray<Complex>;
	const float PI = static_cast<float>(3.14159265358979323846);


#define WIDTH 1280
#define HEIGHT 1060
#define FPS 100
using namespace std;
using namespace sf;

class WithFFT
{
public:
	WithFFT();
	~WithFFT();
    void create();
    void loadMusic(const std::string& path);
    void performFFT();
	void fft(ComplAr& data);
	void create_hamming_window();
    int getDifficulties();
    sf::Time duration = sf::seconds(0);
	sf::Time offsetTime = sf::seconds(0);
	void draw(sf::RenderWindow& window);
	bool update();
    const std::vector<float>& getFFTResults() const {
        return fftResults;
    }
protected:
	sf::SoundBuffer buffer;
	sf::Sound song;

    unsigned int sample_rate = 0;
	sf::Uint64 sample_count = 0;
	sf::Uint64 buffer_size = 0;
    std::vector<float> fftResults; // Store FFT results

	const std::string path = "Resources/Songs/";
	std::vector<Complex> samples;
	ComplAr bin;
	std::vector<float> window;
	void frequency_spectrum_round(std::vector<sf::VertexArray>& VAs, std::vector<sf::Color>& colors,const std::vector<float>& heights, const sf::Vector2f& center, const float& radius, const int& from, const int& to);
};

#endif /*FFT_HPP_*/