
/*
#include "Game.hpp"

void Game::handleCollision()
{
    if (player->gotHit == true )
    {
        player->player.setRadius(player->base_player_radius - 10);
        player->player_background.setRadius(player->player.getRadius() * 0.75f);

        // Update origins after changing sizes
        player->player.setOrigin(player->player.getRadius(), player->player.getRadius());
        player->player_background.setOrigin(player->player_background.getRadius(), player->player_background.getRadius() + 0.24f * player->player.getRadius());
    }
    else if (player->gotHit == false)
    {
        player->player.setRadius(player->base_player_radius);
        player->player_background.setRadius(player->player.getRadius() * 0.75f);
        // Update origins after changing sizes
        player->player.setOrigin(player->player.getRadius(), player->player.getRadius());
        player->player_background.setOrigin(player->base_player_radius * 0.75f, player->base_player_radius * 0.75f + 0.24f * player->base_player_radius);
    }

	
    Projectile* collidedProjectile = vizualizer->checkCollision(player->player.getPosition(), player->player.getRadius());

    if (collidedProjectile != nullptr && player->gotHit == false) {
		//print the color of the plauer and the color of the projectile
        if (player->_color != collidedProjectile->yingYang) {
		}else if (player->_color == collidedProjectile->yingYang) {
	        player->gotHit = true;
    	    player->invincibilityTimer = player->invincibilityTime;
        	health -= 100;	
			cout << "health changed from hp : " << health + 100 << "to " << health << std::endl;
		}    
	}

    if (player->gotHit && player->invincibilityTimer > 0.0f) {
        // Decrement invincibility timer
        //cout << "frameTime in seconds is: " << frameTime.asSeconds() << std::endl;
        player->invincibilityTimer -= frameTime.asSeconds(); // Assuming frameTime is the time elapsed since the last frame.
       // cout << "Invincibility timer after decrement: " << player->invincibilityTimer << endl;
        if (player->invincibilityTimer <= 0) {
            // Reset hit flag when invincibility period ends
            player->gotHit = false;
			//find a way to indicate that the player is not invisible anymore
        }
    }
	//check if the player is below the boss if so increase the score x check position of the boss
	// Assuming the laser beam is also centered on the x-coordinate of the player
	float laserCenterX = player->player.getPosition().x;

	// Calculate the distance between the boss and the laser
	float distance = abs(vizualizer->boss.getPosition().x - laserCenterX);

	// If the distance is less than or equal to the radius of the boss,
	// the laser is hitting the boss
	if (distance <= vizualizer->boss.getRadius()) {
    	score += 1;
	}
}

void Game::checkMenuButton(sf::Event& event)
{

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
        if (menu.play_button.isMouseOver(mousePosition)) {
            std::cout << "Le button play a été cliqué !" << std::endl;
			menu.state = GAME;
        }
        if (menu.left_button.isMouseOver(mousePosition)) {
            std::cout << "Le button previous song a été cliqué !" << std::endl;
            menu.idSong -= 1;
            if (menu.idSong < 0) {
                menu.idSong = menu.songs.size() - 1;
            }
			//menu set string corretcly
			menu.cover.loadFromFile("Resources" + get<2>(menu.songs[menu.idSong]));
        	std::string tmp =menu.setNameSong(get<1>(menu.songs[menu.idSong]));
            menu.text.setString(tmp);
        	menu.text.setPosition(WIDTH / 2 - tmp.length() * 15, HEIGHT / 4 - 20);
        }
        if (menu.right_button.isMouseOver(mousePosition)) {
            std::cout << "Le button next song a été cliqué !" << std::endl;
            menu.idSong += 1;
            if (menu.idSong >= menu.songs.size()) {
                menu.idSong = 0;
            }
			menu.cover.loadFromFile("Resources" + get<2>(menu.songs[menu.idSong]));
        	std::string tmp = menu.setNameSong(get<1>(menu.songs[menu.idSong]));
        	menu.text.setString(tmp);
        	menu.text.setPosition(WIDTH / 2 - tmp.length() * 15, HEIGHT / 4 - 20);
        }
	}
}

void Game::checkBackButton(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
		if (menu.back_button.isMouseOver(mousePosition)) {
            std::cout << "Le button back to menu a été cliqué !" << std::endl;
			menu.state = MENU;
			score = -1;
			menu.backgroundSprite.setTexture(menu.backgroundTexture);
        }
	}
}

void Game::run()
{
	sf::Event event{};
	while(window.isOpen())
	{
		frameTime = clock.restart();
		while(window.pollEvent(event))
		{
			// Add this check to your event handling loop
			if (event.type == sf::Event::Closed) {
				window.close();
				return; // This will exit the game loop and end the program
			}
            
			if (is_menu_active && menu.state == MENU)
				checkMenuButton(event);
			if (is_menu_active && (menu.state == SCORE || menu.state == LOSS))
				checkBackButton(event);
		}
        getMovements();
        window.clear(sf::Color(128, 128, 128));
        if (is_menu_active)
        {
            //hard set the mode to space
			window.clear(sf::Color(128,128,128));
            menu.draw(window);
            is_menu_active = menu.is_active;
			health = maxHealth;
			if (menu.state == MENU){
				score= 0;	
			}
            if (menu.state == GAME){
                //initialize_mode(menu.get_mode(), menu.get_song());
                //menu.quit();
		        std::string nameofsong(get<1>(menu.songs[menu.idSong]));
       			 size_t lastSlashPos = nameofsong.find_last_of("/");
				active_song =  nameofsong.substr(lastSlashPos + 1);
                initialize_mode("Space", active_song);
                initialize_player();
				is_menu_active = false;
                menu.is_active = false;
				WinOrLoss = INGAME;
            } else if (menu.state == SCORE || menu.state == WIN || menu.state == LOSS){
                std::string grade = getGradeFromScore(score);
                menu.setScore(score);
                menu.setNote(grade);
			}
	    }else if (WinOrLoss == INGAME && !is_menu_active && menu.state == GAME){
			if (vizualizer->update() == true){
				WinOrLoss = WIN;
				is_menu_active = true;
				menu.state = SCORE;
				menu.is_active = true;
				menu.backgroundSprite.setTexture(menu.backgroundTextureScore);
				vizualizer = nullptr;
				continue;
			}
            player->update();
            window.clear(sf::Color(128,128,128));
            vizualizer->draw(window);
            player->draw(window);
			handleCollision();
			float size =  health / maxHealth;
			healthBar.setSize(sf::Vector2f(size * WIDTH, healthBar.getSize().y));
			window.draw(healthBar);
    		scoreText.setString("Score: " + std::to_string(score));
		    window.draw(scoreText);
			//	handle loose and win conditions by changing  WinOrLoss
			if (health <= 0){
				WinOrLoss = LOSS;
				is_menu_active = true;
				menu.state = LOSS;
				menu.is_active = true;
				menu.backgroundSprite.setTexture(menu.backgroundTextureScore);
				vizualizer = nullptr;
			}
        	//draw back button
        }
        window.display();
    }
}


void Game::getMovements()
{

	if (is_menu_active){
	} else {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		is_menu_active = true;
		menu.state = MENU;
		menu.is_active = true;
		WinOrLoss = INMENU;
		//need to delete the Vizualizer
		vizualizer = nullptr;
		menu.backgroundSprite.setTexture(menu.backgroundTexture);
	}
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // Execute code for left arrow key press
        player->moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // Execute code for right arrow key press
        player->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        // Execute code for up arrow key press
        player->moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        // Execute code for down arrow key press
        player->moveDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        sf::Time elapsed = colorChangeClock.getElapsedTime();
        if (elapsed.asSeconds() < 0.15f)
        {
            return;
        }

        if (player->getColor() == false) {
            player->player_background.setFillColor(sf::Color::Black);
            player->setBackgroundColor(true);
        } else {
            player->player_background.setFillColor(sf::Color::White);
            player->setBackgroundColor(false);
        }
        colorChangeClock.restart();  // Reset the clock
    }
	}
}



Game::Game(char **argv, int argc)
{
    ContextSettings settings;
    settings.antialiasingLevel = 4;
	if (argc > 1){ 	//convert argv[1] to std::string
		cout << argv[1] << std::endl;
        std::string nameofsong(argv[1]);
        
        // Find the position of the last '/'
        size_t lastSlashPos = nameofsong.find_last_of("/");
        
        // Extract the substring after the last '/'
		active_song =  nameofsong.substr(lastSlashPos + 1);
	}
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setSize(sf::Vector2f(0, 10));
	healthBar.setPosition(sf::Vector2f(0, HEIGHT - 120));
	if (!font.loadFromFile("Resources/Fonts/Shikamaru.ttf")) { // Replace "Arial.ttf" with your font file
        std::cerr << "Error loading font\n";
    }
    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // Set character size in pixels, not points
    scoreText.setFillColor(sf::Color::White); // Set text color
    scoreText.setPosition(10, 10); // Set text position (optional)
	scoreText.setString("Score");
	menu.setFont(font); //
    const VideoMode desktop = VideoMode::getDesktopMode();
    window.create(VideoMode(WIDTH, HEIGHT, desktop.bitsPerPixel), "Hoppy Fighter",Style::Titlebar| Style::Close, settings);
    window.setFramerateLimit(FPS);
    grades[0] = "F";
    grades[1000] = "D";
    grades[2500] = "C";
    grades[4500] = "B";
    grades[7500] = "A";
}


void Game::initialize_mode(const std::string& mode_name, const std::string& song_name)
{

    if (mode_name == "Space")
    {
		cout << "name of the song to load is " << song_name << endl;
        vizualizer = std::make_unique<Vizualizer>(song_name);
    }
    else
    {
        throw std::invalid_argument("Received name of mode that has no initialization implemented.");
    }
}


void Game::initialize_player()
{
    player = std::make_unique<Player>();
}

std::string Game::getGradeFromScore(int score) 
{
    std::string grade = "F";  // default grade
    for (auto& g : grades) {
        if (score >= g.first) {
            grade = g.second;
        } else {
            break;
        }
    }
    return grade;
}

 */