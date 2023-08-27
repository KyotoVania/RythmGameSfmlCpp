/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** FFT_Game.cpp
*/

#include "Visualizer/FFT_Game.hpp"

#define BUFFER_SIZE 16384

#define BIG_BUFFER

FFT_Game::FFT_Game()
{
}

FFT_Game::~FFT_Game()
{
    song.stop();
    // Stop the song playback if it is currently playing

    // Optionally, release any resources held by the buffer

    // If there are any dynamically allocated objects or arrays, delete them here
    // (Ensure you have the necessary definitions and declarations for these objects)
    // Example:
    // delete[] samples;

    // No need to perform explicit cleanup for other member variables, as they will be automatically cleaned up by their destructors.
}

/*
void FFT_Game::loadMusic(const std::string &path)
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
 */