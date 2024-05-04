#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Class/Parallax.h"
#include "Class/Obsticals.h"
#include "Class/Player.h"

using namespace sf;
using namespace std;

//int Run(sf::RenderWindow& window);
//class MainMenu {
//public:
//	MainMenu(sf::RenderWindow& window) : window(window) {
//		if (!font.loadFromFile("Asset/Font/dDamel.ttf")) {
//			std::cerr << "Failed to load font" << std::endl;
//			std::exit(-1);
//		}
//
//		if (!back.loadFromFile("Asset/Background/home.png")) {}
//		background.setTexture(back);
//
//		if (!titleTexture.loadFromFile("Asset/Logo/Pyramids.png")) {}
//		titles.setTexture(titleTexture);
//		titles.setScale(0.3, 0.3);
//		titles.setPosition(800, -70);
//
//		if (!start.loadFromFile("Asset/Background/start.png")) {}
//		s.setTexture(start);
//		s.setScale(0.5, 0.5);
//		s.setPosition(600, 100);
//
//		if (!exit.loadFromFile("Asset/Background/exit.png")) {}
//		e.setTexture(exit);
//		e.setScale(0.5, 0.5);
//		e.setPosition(600, 100);
//	}
//
//	void handleInput() {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::MouseButtonPressed) {
//				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//
//				if (s.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
//				{
//					std::cout << "Starting the game!" << std::endl;
//					// Add code to start the game
//					Run(window);
//				}
//
//				else if (e.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
//				{
//					return;
//				}
//			}
//		}
//	}
//
//	void draw() {
//		window.clear();
//		window.draw(background);
//		window.draw(titles);
//		window.draw(s);
//		window.draw(e);
//		//window.draw(startOption);
//		//window.draw(exitOption);
//		window.display();
//	}
//
//private:
//	sf::RenderWindow& window;
//	sf::Font font;
//	sf::Text title;
//	//sf::Text startOption;
//	//sf::Text exitOption;
//	sf::Texture back;
//	sf::Sprite background;
//	Texture start;
//	Sprite s;
//	Texture exit;
//	Sprite e;
//	sf::Texture titleTexture;
//	sf::Sprite titles;
//};

//int main() {
//	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Main Menu", sf::Style::Fullscreen);
//
//	MainMenu mainMenu(window);
//
//	while (window.isOpen()) {
//		mainMenu.handleInput();
//		mainMenu.draw();
//	}
//
//	return 0;
//}
//int Run(sf::RenderWindow& window)
//{
int main() {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Parallax", sf::Style::Fullscreen);
	window.setFramerateLimit(100); // call it once, after creating the window

	sf::Music backgroundMusic;
	backgroundMusic.setVolume(50.f);
	if (!backgroundMusic.openFromFile("./Asset/Music/music.mp3"))
	{
		std::cout << "Error " << std::endl;
	}
	backgroundMusic.play();

	sf::Music deathMusic;
	if (!deathMusic.openFromFile("./Asset/Music/death.mp3"))
	{
		std::cout << "Error " << std::endl;
	}

	std::srand(std::time(nullptr));

	sf::Clock gameClock;
	float elapsedGame = 0.0;

	sf::Clock ExtraTime;
	float elapsedExtraTime = 0.f;

	//Player
	Player player(100, window.getSize().y - 480);
	sf::Vector2f playerPos(100, window.getSize().y - 480);
	sf::Clock playerClock;
	sf::Color color = player.GetPlayerColor();
	bool isPlayerAlive = true;
	bool isDead = false;

	sf::Clock stopClock;
	float elapsedStopClock = 0.0;
	float stopTimer = 1.f;
 
	bool intersectionOccurred = false;
	bool isTimerStarted = false;

	int health = 10;
	sf::Font font;
	font.loadFromFile("Asset/Font/dDamel.ttf");

	sf::Text heal;
	heal.setString(std::to_string(health));
	heal.setPosition(100, 100);
	heal.setCharacterSize(50);
	heal.setFont(font);

	sf::Texture key;
	key.loadFromFile("Asset/Health/Key.png");

	sf::Sprite keyLife;
	keyLife.setTexture(key);
	keyLife.setPosition(100, 100);
	keyLife.setScale(0.2, 0.2);

	//parallax
	sf::Clock parallaxClock;
	float parallaxDeltaTime = 0;
	Parallax parrallax(window);

	//Enemy
	sf::Clock clockObsticals;
	std::vector<Obsticals> obstacles;

	Obsticals obstacle1("Asset/Obsticals/obstacle_1.png");
	Obsticals obstacle2("Asset/Obsticals/obstacle_2.png");
	Obsticals obstacle3("Asset/Obsticals/alian space ship.png");

	obstacle1.setScale(0.28, 0.4);

	obstacles.push_back(obstacle1);
	obstacles.push_back(obstacle2);
	obstacles.push_back(obstacle3);

	float deltaTimeObsticals = 0.0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}

		if (isPlayerAlive)
		{
			// Player Update
			sf::Time currentTime = playerClock.restart();
			float dt = currentTime.asSeconds();
			player.Update(dt);

			elapsedExtraTime = ExtraTime.getElapsedTime().asSeconds();

			if (elapsedExtraTime >= 100) {
				parallaxDeltaTime = parallaxClock.restart().asSeconds() * 1.5;
			}
			else
			{
				parallaxDeltaTime = parallaxClock.restart().asSeconds();
			}

			// Player Movement and Animation
			player.UpdateCurrentAnimation(event, playerPos, player.GetPlayerPosition().y, health);

			deltaTimeObsticals = clockObsticals.restart().asSeconds();

			obstacles[0].update(deltaTimeObsticals);
			obstacles[1].update(deltaTimeObsticals + 0.001);
			obstacles[2].update(deltaTimeObsticals + 0.005);

			// Check and respawn enemies
			obstacles[0].checkAndRespawnDynamic_500_800(window);
			obstacles[1].checkAndRespawnStatic(window);
			obstacles[2].checkAndRespawnDynamic_100_400(window);

			// Collision detection
			for (const auto& obstacle : obstacles)
			{
				sf::FloatRect obstacleBounds = obstacle.outline.getGlobalBounds();

				if (intersectionOccurred)
				{
					if (!isTimerStarted)
					{
						stopClock.restart();
						isTimerStarted = true;
					}

					elapsedStopClock = stopClock.getElapsedTime().asSeconds();

					if (elapsedStopClock >= 1.5f)
					{
						isTimerStarted = false;
						intersectionOccurred = false;
						player.SetPlayerColor(color);
					}
				}

				else if (obstacleBounds.intersects(player.outline.getGlobalBounds()))
				{
					health--;
					heal.setString(std::to_string(health));
					player.SetPlayerColor({ 220,220,220, 70 });
					intersectionOccurred = true;

					if (health <= 0) {
						gameClock.restart();
						parallaxDeltaTime = 0;
						isPlayerAlive = false;
					}
					break;
				}
			}
		}

		else
		{
			backgroundMusic.stop();
			deathMusic.setVolume(100.f);
			deathMusic.play();

			elapsedGame = gameClock.getElapsedTime().asSeconds();

			if (elapsedGame <= 1.f)
			{
				sf::Time currentTime = playerClock.restart();
				float dt = currentTime.asSeconds();
				player.Update(dt);
				player.UpdateCurrentAnimation(event, playerPos, player.GetPlayerPosition().y, 0);
			}
		}

		window.clear();

		parrallax.parlx(parallaxDeltaTime);
		parrallax.draw(window, obstacles, player);

		window.draw(keyLife);
		window.draw(heal);

		if (health <= 0) {
			player.ShowMessage(window, player);
		}

		window.display();
	}

	return 0;
}