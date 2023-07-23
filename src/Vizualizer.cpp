#include <iostream>
#include "Vizualizer.hpp"

using namespace std;
using namespace sf;


/**
 * Main function. Handles all user input.
 */

#define BUFFER_SIZE 16384

#define BIG_BUFFER
#pragma region Projectile
/**
 *  Initializes drawables.
 */

Projectile::Projectile(const float x, const float y, const float radius, const float speed,  float angle, bool yingOrYang)
{
	circle.setRadius(radius);
	if (yingOrYang)
	    circle.setFillColor(sf::Color::White);
	else 
		circle.setFillColor(sf::Color::Black);
	yingYang = yingOrYang;
    circle.setOrigin(radius, radius);
    circle.setPosition(x, y);
    this->speed = speed;
    this->angle = angle;
    this->radius = radius;
    this->position = { x, y };
}

Projectile::~Projectile()
{
}


#pragma region Vizualizer
/**
 *  Initializes drawables.
 */
Vizualizer::Vizualizer(const std::string& song_name) : WithFFT(song_name)
{
	stars.resize(num_of_stars);
	for(int i = 0; i < num_of_stars; i++)
	{
		stars[i] = (Star {1.f * (rand() % WIDTH),1.f* (rand() % HEIGHT), 0 });
	}
	//initialization of boss
	boss_texture.loadFromFile("Resources/hoppy_no_bg.png");
	boss_texture.setSmooth(true);
	boss.setRadius(base_boss_radius);
	boss.setPointCount(40);
	boss.setFillColor(Color(255, 255, 255, 128));
	boss.setTexture(&boss_texture);
	boss.setOrigin(base_boss_radius, base_boss_radius);
	//use pair position to set position of boss base_boss_position
	boss.setPosition(Vector2f((base_boss_position.first), (base_boss_position.second)));

	boss_background.setRadius(base_boss_radius);
	boss_background.setPointCount(40);
	boss_background.setFillColor(sf::Color(128, 128, 128));
	boss_background.setOrigin(base_boss_radius, base_boss_radius);
	boss_background.setPosition(Vector2f((base_boss_position.first), (base_boss_position.second)));
	//print value of the position
	//init the progress bar 
	progressBar.setFillColor(sf::Color::Green);
	progressBar.setSize(sf::Vector2f(0, 10));
	progressBar.setPosition(sf::Vector2f(0, HEIGHT - 100));
	
	//initialization of stars
	star_vertices.setPrimitiveType(Lines);
	star_vertices.resize(2*num_of_stars);

	//inicialization of halo effect
	for (int i = 0; i <4; i++)
	{
		halo.push_back(VertexArray(TriangleFan));
	}
	const float base_height = 300;
	halo_heights.push_back(base_height * 3);
	halo_heights.push_back(base_height * 2.6);
	halo_heights.push_back(base_height * 2);
	halo_heights.push_back(base_height);

	halo_colors.push_back(Color::Black);		
	halo_colors.push_back(Color::White);
	halo_colors.push_back(Color::Black);
	halo_colors.push_back(Color::White);
}

Vizualizer::~Vizualizer() {}

/**
 *  Draws Vizualizer to the given window.
 */
void Vizualizer::draw(sf::RenderWindow& window)
{
	window.draw(star_vertices);

	for (auto&& layer :halo)
	{
		window.draw(layer);
	}
	
	window.draw(boss_background);
	window.draw(boss);
	for (auto&& projectile : projectiles)
    {
        window.draw(projectile.circle);
    }
	window.draw(progressBar);
}
/**
 *  Helper funciton. Gets scaled approximate of given range of frequencies.
 */
float Vizualizer::update_by_sound(const int from, const int to, const int scale_factor)
{
	float sum = 0;
	for (int i = from; i < to; ++i)
	{
		//std::cout << "bin[" << i << "] = " << bin[i] << std::endl;
		sum += static_cast<float>(abs(bin[i]));
	}
	return (sum / (to - from)) / scale_factor;
}
/**
 * Helper function. Updates radius of given circle shape.
 */
void Vizualizer::update_radius(const float update_value,sf::CircleShape& circle) const
{
	circle.setRadius(base_boss_radius * update_value);
	circle.setOrigin(circle.getRadius(), circle.getRadius());
	circle.setPosition(boss.getPosition());
	//std::cout << "position: x = " << WIDTH / 2.f << " y = " << HEIGHT / 2.f << std::endl;
}

/**
 *  Updates Vizualizer state by current song buffer values.
 */
bool Vizualizer::update()
{
	WithFFT::update();
	//cout << "update" << endl;
	//update base_star_speed accoring to sub_bass frequencies

    float progress = offsetTime.asSeconds() / duration.asSeconds();

    progressBar.setSize(sf::Vector2f(progress * WIDTH, progressBar.getSize().y));
	//check win conditions if sound is over
	if (progress >=0.90)
		return true;
	base_star_speed = static_cast<float>(1.01) + update_by_sound(0, 60,100000000);
	
	//boss radius is mapped to human voice frequencies
	float radius_update = 1.f + update_by_sound(90, 280, 5000000);

	update_radius(radius_update, boss_background);
	update_radius(radius_update, boss);
	//we will had a notion of movement for the boss it will from side to side and move faster depending on the update_by_sound
	// Update boss's position based on the audio
    float movementFactor = 10.f; // Adjust this value as needed
    float boss_movement = update_by_sound(0, 60, 100000000); //
    //check if out of screen if so revert the bool and check it 
    if (boss.getPosition().x + 300 >= WIDTH || boss.getPosition().x - 300 <= 0)
        LeftRight = LeftRight * -1;
    float newPoseX = boss.getPosition().x + (boss_movement * movementFactor * LeftRight);
    boss.setPosition(newPoseX, boss.getPosition().y);
    boss_background.setPosition(boss.getPosition());

	//stars generation
	star_vertices.clear();
	for(auto& star: stars)
	{
		star.z += 1;
		
		star.old_x = star.x;
		star.old_y = star.y;
		star.x = (star.x - WIDTH / 2) * base_star_speed + WIDTH / 2;		
		star.y = (star.y + 75) * base_star_speed - 75;		
		//reset star - its out of borders
		if (star.x < 0 || star.x > WIDTH || star.y < 0 || star.y>HEIGHT)
		{
			star.x = 1.f * (rand() % WIDTH);
			star.y = 1.f * (rand() % HEIGHT);
			star.z = 100.f;

			star.old_x = star.x;
			star.old_y = star.y;
		}

		//adding head of the star
		star_vertices.append(Vertex(Vector2f(star.x, star.y),Color(static_cast<sf::Uint8>(star.z), static_cast<sf::Uint8>(star.z), static_cast<sf::Uint8>(star.z),255)));
		//adding tail of the star
		star_vertices.append(Vertex(Vector2f(star.old_x, star.old_y), Color(static_cast<sf::Uint8>(star.z), static_cast<sf::Uint8>(star.z), static_cast<sf::Uint8>(star.z), 255)));;
	}
	for (auto& shoot : projectiles ) {
		shoot.position.first += shoot.speed * cos(shoot.angle);
        shoot.position.second += shoot.speed * sin(shoot.angle);
        shoot.circle.setPosition(shoot.position.first, shoot.position.second);
		if (shoot.position.first < 0 || shoot.position.first > WIDTH || shoot.position.second < 0 || shoot.position.second > HEIGHT) {
    		projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), shoot), projectiles.end());
		}
	}
	//generating halo around boss
	for (size_t i = 0; i < halo.size(); i++)
	{
		halo[i].clear();
	}
	float checkYingYang =  1.f + update_by_sound(0, 60, 100000000);
	//cout << "checkYingYang : " << checkYingYang << std::endl;
	if (checkYingYang > 1.05)
    {
        countYingYang++;
        if (countYingYang == 5)
        {
            YingYang = !YingYang;
            countYingYang = 0;
        }
    }
	frequency_spectrum_round(halo, halo_colors, halo_heights, Vector2f(boss.getPosition()), boss.getRadius() - 2, 20, 80);
	//we will check there is some bass frequencies at this moment depending of a treshold if yes increment the countYingYang when it reach 5 it will invert the bool YingYang and go back to 0


	for (int i = 0; i < halo.size(); i++)
	{
    	if (i == 3)
    	{
        	for (int j = 0; j < halo[i].getVertexCount(); j++)
        	{   
            	float threshold= (boss.getRadius() / base_boss_radius);
            	float distanceToCenter = sqrt(pow(halo[i][j].position.x - boss.getPosition().x, 2) + pow(halo[i][j].position.y - boss.getPosition().y, 2));
            	float spawnRadius = (boss.getRadius() + threshold) +radius_update * 4;
	
	            if (distanceToCenter > spawnRadius)
    	        {
        	        float angle = atan2(halo[i][j].position.y - boss.getPosition().y, halo[i][j].position.x - boss.getPosition().x);
					float pose_x = halo[i][j].position.x + (boss.getRadius() + threshold) * cos(angle);
					float pose_y = halo[i][j].position.y + (boss.getRadius() + threshold) * sin(angle);
                	projectiles.push_back(Projectile(pose_x, pose_y, 5.0f, radius_update * 4, angle, YingYang));
            	}
        	}
    	}
	}
	return false;
	
}

Projectile* Vizualizer::checkCollision(const Vector2f & playerPosition, float playerRadius)
{
    for (auto& projectile : projectiles)
    {
        Vector2f diff = playerPosition - projectile.circle.getPosition();
        float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

        if (distance <= playerRadius + projectile.circle.getRadius())
        {
            return &projectile; // Return a pointer to the collided projectile
        }
    }

    return nullptr; // Return nullptr if no collision occurred
}


#pragma endregion 	