/*
** EPITECH PROJECT, 2023
** newtry
** File description:
** FFT.cpp
*/
#include "Visualizer/FFT.hpp"

#define BUFFER_SIZE 16384

#define BIG_BUFFER
#pragma region WithFFT
/**
 * Initializes drawables.
 */
WithFFT::WithFFT()
{

}
/**
 * Computes FFT on current song buffer values.
 */
WithFFT::~WithFFT()
{
    // Stop the song playback if it is currently playing
    song.stop();

    // Optionally, release any resources held by the buffer

    // If there are any dynamically allocated objects or arrays, delete them here
    // (Ensure you have the necessary definitions and declarations for these objects)
    // Example:
    // delete[] samples;

    // No need to perform explicit cleanup for other member variables, as they will be automatically cleaned up by their destructors.
}

void WithFFT::create()
{

}

void WithFFT::loadMusic(const std::string &path)
{
    ifstream ifs(path);
    if (!ifs.good())
    {
        cout << "Song \"" << path << "\" is not in the database." << endl;
        return;
    }

    buffer.loadFromFile(path);
    song.setBuffer(buffer);

    sample_count = buffer.getSampleCount();
    sample_rate = buffer.getSampleRate() * buffer.getChannelCount();
#ifdef BIG_BUFFER
    if (BUFFER_SIZE < sample_count)
    {
        buffer_size = BUFFER_SIZE;
    }
    else
    {
        buffer_size = sample_count;
    }
#endif

#ifndef BIG_BUFFER
    buffer_size = WIDTH;
#endif

    song.setLoop(true);
    song.play();

    samples.resize(buffer_size);
    create_hamming_window();
    duration = sf::seconds(static_cast<float>(sample_count) / sample_rate);
}

bool WithFFT::update()
{
	int offset = static_cast<int>(song.getPlayingOffset().asSeconds() * sample_rate);
	if(offset + buffer_size < sample_count)
	{
		for (int i = 0; i < buffer_size; i++)
		{
			samples[i] = Complex(static_cast<int>(buffer.getSamples()[i + offset] * window[i]), 0);
		}
	}

	bin = ComplAr(samples.data(), buffer_size);
	fft(bin);
	offsetTime = song.getPlayingOffset();
	return true;
}
/**
 *  Implements Fast Fourier Transform algorithm.
 */
void WithFFT::fft(ComplAr& data)
{
	const size_t n = data.size();
	if (n <= 1) return;

	ComplAr odd = data[slice(1, n / 2, 2)];
	ComplAr even = data[slice(0, n / 2, 2)];

	fft(odd);
	fft(even);

	for (int i = 0; i < n / 2; i++) {

		Complex omega = polar<double>(1.0, -2 * PI * i / n);
		//multiplication could be optimized by counting the mult only once;
		data[i] = even[i] + omega * odd[i];
		data[i+n/2] = even[i] - omega * odd[i];
	}
}
/**
 * Generates hamming window.
 */
void WithFFT::create_hamming_window()
{
	for (int i = 0; i < buffer_size; i++) {
		window.push_back(static_cast<float>(0.54) - static_cast<float>(0.46) * cos((2 * PI * i) / static_cast<float>(buffer_size)));
	}
}

/**
 * Generates logarithmically scaled frequency halo forming a circle. 
 * Each layer is stored at one VertexArray in the vector VAs.
 * Parameters:
 * Color of each layer is in vector colors.
 * Height of each layer is in vector heights.
 * Center is the center of the halo.
 * Radius is the base radius the halo will reach when no music is playing.
 * From is a frequency from which the halo should start generating.
 * To is a frequency to which the halo should be generated.
 */

void WithFFT::frequency_spectrum_round(std::vector<sf::VertexArray>& VAs,std::vector<sf::Color>& colors,const std::vector<float>& heights, const sf::Vector2f& center, const float& radius, const int& from, const int& to)
{
	if (VAs.size() != colors.size() || VAs.size() != heights.size())
	{
		throw new invalid_argument("number of VertexArrays is not the same as number of colors");
	}
	if(from == 0)
	{
		throw new invalid_argument("spectrum cant start at 0, set different 'from' value");
	}
	
	const float scale = float(to-from) / 180.f;		//divided by angle (in degrees) that the scale should cover (360 - circle; 180 - half a circle)
	
	for (int i = 0; i < VAs.size(); i++)
	{
		VAs[i].append(Vertex(center, colors[i]));
	}

	for(int j = static_cast<int>(VAs.size()-1); j >= 0; j--)
	{
		//generating left side of the halo

		float new_radius;
		float angle;
		Vector2f cartez;
		Vector2f base_position;

		for (float i = static_cast<float>(from); i< static_cast<float>(to); i *= static_cast<float>(1.01))
		{
			//generating left-side
			new_radius = radius * static_cast<float>(1 + (abs(bin[static_cast<int>(i)]) / 30000000000 * heights[j]));
			angle= ((i-from)/ scale + 90 ) * PI / 180;
			cartez = Vector2f(new_radius * cos(angle), new_radius * sin(angle)); //polar coordinates to cartez
			base_position = center + cartez;
			VAs[j].append(Vertex(base_position, colors[j]));
		}		
		//last vertex for completing full semicircle
		angle = (270 * PI / 180);
		cartez = Vector2f(new_radius * cos(angle), new_radius * sin(angle));
		VAs[j].append(Vertex(center + cartez));
		
		//generating right side of the halo
		for (float i = static_cast<float>(from); i< static_cast<float>(to); i *= static_cast<float>(1.01))
		{
			new_radius = radius * static_cast<float>(1 + (abs(bin[static_cast<int>(i)]) / 30000000000 * heights[j]));
			angle = (-(i - from) / scale + 90) * PI / 180;
			cartez = Vector2f(new_radius * cos(angle), new_radius * sin(angle));
			base_position = center + cartez;
			VAs[j].append(Vertex(base_position, colors[j]));
		}
		//last vertex for completing full semicircle
		angle = -(90 * PI / 180);
		cartez = Vector2f(new_radius * cos(angle), new_radius * sin(angle));
		VAs[j].append(Vertex(center + cartez));
	}
	//print the number of bar arround the circle 


	//print the value for the each bar
	//cout << VAs[0][0].position.x << endl;
}


int WithFFT::getDifficulties()
{
    // Placeholder logic to compute difficulty based on the music's FFT data.
    // This is a simplistic approach and might need a more sophisticated algorithm.
    float average_magnitude = 0;
    for (const auto& val : fftResults)
    {
        average_magnitude += abs(val);
    }
    average_magnitude /= fftResults.size();

    int difficulty = static_cast<int>(average_magnitude / 10000); // Arbitrary scaling factor
    if (difficulty > 10) difficulty = 10;
    if (difficulty < 1) difficulty = 1;

    return difficulty;
}
#pragma endregion