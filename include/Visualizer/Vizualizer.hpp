#ifndef VIZUALIZER_HPP
	#define VIZUALIZER_HPP
	#include <memory>
	#include <SFML/Window.hpp>
	#include <SFML/Graphics.hpp>
	#include "Visualizer/FFT.hpp"
struct Star
{
	/**
	* x coordinate of the star
	*/
	float x = 0.f;
	/**
	* y coordinate of the star
	*/
	float y = 0.f;
	/**
	* z coordinate of the star
	*/
	float z = 0.f;
	/**
	* previous x coordinate of the star
	*/
	float old_x = 0.f;
	/**
	* previous y coordinate of the star
	*/
	float old_y = 0.f;
};


class Vizualizer
{
public:
    Vizualizer();
	~Vizualizer();
    void load(WithFFT& fft);
	void draw(sf::RenderWindow& window);
	bool update();
	//Projectile* checkCollision(const Vector2f & playerPosition, float playerRadius);
	sf::CircleShape boss;
    void setFFTResults(const std::vector<float>& results) {
        fftResults = results;
    }
private:
	//const int num_of_stars  = 300;
	const float base_boss_radius = 50;
	std::pair<float, float> base_boss_position = { WIDTH / 2,  1 };
	//float base_star_speed = static_cast<float>(1.01);
    std::vector<float> fftResults; // Store FFT results for visualization

	float update_by_sound(const int from, const int to, const int scale_factor);
	void update_radius(const float update_value, sf::CircleShape& circle) const;
	
	/**
	* Vector of stars that are used to compute positions.
	*/
	//std::vector<Star> stars;
	/**
	* Array of vertices representing stars. This is drawn.
	*/
	//sf::VertexArray star_vertices;
	/**
	* Vertices used to draw halo around the boss.
	*/
	std::vector<sf::VertexArray> halo;
	/**
	* Vector of halo colors. First color is in the background. Last is at the front.
	*/
	std::vector<sf::Color> halo_colors;
	/**
	* Vector of hegihts of each halo color layer.
	*/
	std::vector<float> halo_heights;
	
	/**
	* Planet shape.
	*/
	/**
	* Planet background shape.
	*/
	sf::CircleShape boss_background;
	/**
	* Planet texture.
	*/
	sf::Texture boss_texture;
	//add the projection
	//std::vector<Projectile> projectiles;
	//bool for direction
	float LeftRight = 1.0f;
	bool YingYang = false;
	int countYingYang = 0;
	sf::RectangleShape progressBar;
};
#endif // !VIZUALIZER_HPP