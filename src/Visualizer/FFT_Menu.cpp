/*
** EPITECH PROJECT, 2023
** RythmGameSfmlCpp
** File description:
** FFT_Menu.cpp
*/

#include "Visualizer/FFT_Menu.hpp"

#define BUFFER_SIZE 16384
#define SOME_THRESHOLD 0.5

#define BIG_BUFFER

FFT_Menu::FFT_Menu()
{
}

FFT_Menu::~FFT_Menu()
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

void FFT_Menu::loadMusicMenu(const std::string &path)
{
    ifstream ifs(path);
    if (!ifs.good())
    {
        cout << "Song \"" << path << "\" is not in the database." << endl;
        return;
    } else {
        std::cout << "Song \"" << path << "\" is in the database." << endl;
    }
    std::cout << "Loading music FFT_menu: " << path << std::endl;
    std::string path2 = path + "/Song.wav";
    std::cout << "Loading music FFT_menu: " << path2 << std::endl;
    if (!buffer.loadFromFile(path2))
    {
        std::cout << "Error loading music" << std::endl;
    } else {
        std::cout << "Music loaded" << std::endl;
    }
    std::cout << "Buffer loaded" << std::endl;
    song.setBuffer(buffer);
    std::cout << "Buffer set" << std::endl;
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
    std::cout << "WIDTH: " << WIDTH << std::endl;
    buffer_size = WIDTH;
#endif
    std::cout << "buffer_size: " << buffer_size << std::endl;
   // song.setLoop(true);
    //song.play();

    samples.resize(buffer_size);
    create_hamming_window();
    duration = sf::seconds(static_cast<float>(sample_count) / sample_rate);
}



int FFT_Menu::getCalculatedDifficulty()
{
    int difficulty = 0;


    return difficulty;
}

void FFT_Menu::analyzeEntireSong(const std::string &path)
{
    // Set the difficulty level
    //setDifficulty(difficulty);
}

int FFT_Menu::calculate_song_difficulty() {
    // Initialize counters for the entire song
    int totalSignificantPeaks = 0;

    // Loop through the entire song, chunk by chunk
    for (int offset = 0; offset < sample_count; offset += buffer_size) {
        // Fetch samples from the audio buffer
        for (int i = 0; i < buffer_size; i++) {
            if (i + offset < sample_count) {
                samples[i] = Complex(static_cast<int>(buffer.getSamples()[i + offset] * window[i]), 0);
            } else {
                samples[i] = Complex(0, 0);  // Zero-padding for the last chunk
            }
        }

        // Perform FFT on these samples
        bin = ComplAr(samples.data(), buffer_size);
        fft(bin);  // Assuming fft() modifies 'bin' in-place

        // Count significant peaks in this chunk
        int numSignificantPeaks = 0;
        for (const auto& freq : bin) {
            if (std::abs(freq) > SOME_THRESHOLD) {
                numSignificantPeaks++;
            }
        }

        // Aggregate results
        totalSignificantPeaks += numSignificantPeaks;
    }

    // Calculate and normalize the difficulty score based on aggregated results
    int rawScore = totalSignificantPeaks;
    std::cout << "rawScore: " << rawScore << std::endl;
    int normalizedScore = (rawScore / (sample_count / buffer_size)) % 11;

    return normalizedScore;
}
