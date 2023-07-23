#include <SFML/Graphics.hpp>
#include <string>
//create a global map to associate a int with a note with is a string
#include <vector>
#include <tuple>
#include <vector>
#include <tuple>
#include <string>
#include <fstream>
#include <sstream>

enum state { MENU, GAME, SCORE, LOSS, EXIT };
// A tuple representing a song: <ID, filename, cover>
using Song = std::tuple<int, std::string, std::string>;

class Database {
public:

    // Add a song to the database
    void addSong(int id, const std::string& filename, const std::string& cover) {
        songs.push_back(std::make_tuple(id, filename, cover));
    }

    // Get all songs in the database
    const std::vector<Song>& getSongs() const {
        return songs;
    }

    // Parse song database from file
    void parseDatabase(const std::string& filepath) {
        std::ifstream file(filepath);
		if (!file.in)
			cout << "Error opening " << filepath << endl;
        std::string line;
        while (std::getline(file, line)) {
			cout << line << endl;
            std::stringstream ss(line);
            std::string id_str, filename, cover;
            std::getline(ss, id_str, ',');
            std::getline(ss, filename, ',');
            std::getline(ss, cover, ',');

            int id = std::stoi(id_str);
            filename = "resources/songs/" + filename;
            cover = "/" + cover;

            addSong(id, filename, cover);
			cout << "new song " << id << " created successfully name: " << filename << endl;
        }
    }
	
private:
    std::vector<Song> songs;
};

class Button {
protected:
    sf::Vector2f position;
    sf::Shape* shape;
    sf::Text text;
	sf::Font font;	

public:
    Button(sf::Vector2f position, sf::Shape* shape, const std::string& buttonText, sf::Color color) {
		if (!font.loadFromFile("Resources/Fonts/Shikamaru.ttf"))
			std::cout << "Loading failed" << endl;
        this->position = position;
        this->shape = shape;
        this->shape->setFillColor(color);
        this->text.setString(buttonText);
        this->text.setFont(font);
        this->text.setPosition(position.x + shape->getGlobalBounds().width / 2 - this->text.getGlobalBounds().width / 2, position.y + shape->getGlobalBounds().height / 2 - this->text.getGlobalBounds().height / 2);
    }

    virtual ~Button() {
        delete shape;
    }

    bool isMouseOver(sf::Vector2f mousePosition) const {
        return shape->getGlobalBounds().contains(mousePosition);
    }

    virtual void draw(sf::RenderWindow& window) {
        shape->setPosition(position);
        window.draw(*shape);
        window.draw(text);
    }
};

class RectangleButton : public Button {
public:
    //RectangleButton(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText, sf::Font font) : Button(position, new sf::RectangleShape(size), buttonText, font) {}
    RectangleButton(sf::Vector2f position, sf::Vector2f size, const std::string& buttonText, sf::Color color)
            : Button(position, new sf::RectangleShape(size), buttonText, color) {}

    void setSize(sf::Vector2f size) {
        static_cast<sf::RectangleShape*>(shape)->setSize(size);
    }
};

class TriangleButton : public Button {
public:
    TriangleButton(sf::Vector2f sommet_one, sf::Vector2f sommet_two, sf::Vector2f sommet_three, const std::string& buttonText, sf::Color color) : Button(sf::Vector2f(0, 0), new sf::ConvexShape(), buttonText, color) {
        sf::ConvexShape *triangleShape = static_cast<sf::ConvexShape *>(shape);
        triangleShape->setPointCount(3);
        triangleShape->setPoint(0, sommet_one);
        triangleShape->setPoint(1, sommet_two);
        triangleShape->setPoint(2, sommet_three);

        float centerX = (sommet_one.x + sommet_two.x + sommet_three.x) / 3.0f - 75;
        float centerY = (sommet_one.y + sommet_two.y + sommet_three.y) / 3.0f - 35;
        text.setPosition(centerX, centerY);
    }
};

class Menu {
public:
    RectangleButton play_button;
    RectangleButton back_button;
    TriangleButton left_button;
    TriangleButton right_button;
    sf::Text text;
    bool is_active;
	int state = MENU;
	sf::Texture backgroundTexture;
	sf::Texture backgroundTextureScore;
	sf::Texture cover;
	sf::RectangleShape coverShape;
	sf::Sprite backgroundSprite;
	std::vector<Song> songs;
	int score;
	sf::Text scoreText;
	sf::Text note;
	sf::Text ending;
	void setScore(int newScore)
	{
		scoreText.setString("Score: " + std::to_string(newScore));
	}
	void setNote(std::string newNote)
	{
		note.setString("Note: " + newNote);
	}
	sf::Font _font;
	int idSong = 0;
    Menu()
        : play_button(sf::Vector2f(100, HEIGHT / 5 * 4), sf::Vector2f(WIDTH / 6 * 5, HEIGHT / 8), "play", sf::Color::Green)
		, back_button(sf::Vector2f(10, 100), sf::Vector2f( HEIGHT / 4, HEIGHT / 8), "back to menu", sf::Color::Red)
        , left_button(sf::Vector2f(50.0f, HEIGHT / 4), sf::Vector2f(300, HEIGHT / 4 - 100), sf::Vector2f(300, HEIGHT / 4 + 100), "Previous\n    Song", sf::Color::Blue)
        , right_button(sf::Vector2f(WIDTH - 50, HEIGHT / 4), sf::Vector2f(WIDTH - 300, HEIGHT / 4 - 100), sf::Vector2f(WIDTH - 300, HEIGHT / 4 + 100), "Next\nSong", sf::Color::Blue)
        , _font() // Moved the initialization of _font here
    {
		Database datasongs;
		datasongs.parseDatabase("Resources/Songs/Song_Database.txt");
		songs = datasongs.getSongs();
		
		//take the first song take the second element of the tupple Song 1 
        const Song& firstSong = songs[0];
		string nameOfSong = setNameSong(get<1>(firstSong));
        std::cout << "name of song: " << nameOfSong << std::endl;
        text.setString(nameOfSong);
        text.setFont(_font);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(64);
        text.setPosition(WIDTH / 2 - nameOfSong.size() * 20, HEIGHT / 4 - 20);
        is_active = true;
		coverShape.setSize(sf::Vector2f(240, 240));
		coverShape.setPosition(sf::Vector2f(WIDTH / 2 - 120, HEIGHT / 2 - 120));
		cover.loadFromFile("Resources/Sommus.png");
		coverShape.setTexture(&cover);
		state = MENU;
		backgroundTexture.loadFromFile("Resources/backgroundmenu.png");
		backgroundTextureScore.loadFromFile("Resources/backgroundscore.png");
		backgroundSprite.setTexture(backgroundTexture);
    	score = 0;
    	scoreText.setFont(_font);
    	note.setFont(_font);
    	ending.setFont(_font);
    }

	std::string setNameSong(const std::string& nameOfSong)
    {
    	size_t pos = nameOfSong.rfind("/");
    	std::string new_name = nameOfSong.substr(pos + 1);
    	size_t pos_bis = new_name.rfind(".");
    	new_name = new_name.substr(0, pos_bis);
		return new_name;
    }
	
    void setText(const std::string& newText) {
        text.setString(newText);
    }
	void setFont(const sf::Font& font) {
		_font = font;	
	}
    void draw(sf::RenderWindow& window) {
		if (state == MENU){
			window.draw(backgroundSprite);
        	play_button.draw(window);
        	left_button.draw(window);
        	right_button.draw(window);
			window.draw(coverShape);
        	window.draw(text);
		} else if (state == SCORE || state == LOSS) {
			ending.setCharacterSize(80);
			
			if (state == SCORE)
			{
				ending.setString("Victory");
				ending.setPosition(500,150);
			} else
			{
				ending.setString("Defeat");
				ending.setPosition(500, 150);
			}
			scoreText.setPosition(475, 550);
			note.setPosition(525, 300);
			scoreText.setCharacterSize(70);
			note.setCharacterSize(70);
			window.draw(backgroundSprite);
			window.draw(scoreText);
			window.draw(ending);
			window.draw(note);
			back_button.draw(window);
		}
    }
};
