#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Obsticals {
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2i getSize() const;
	sf::Vector2f getPosition() const;
	sf::FloatRect getGlobalBounds() const;

	float movementSpeed = 500.0f; // Adjust as needed

	void spawnRandom_500_800(sf::RenderWindow& window);
	void spawnRandom_100_400(sf::RenderWindow& window);
	void spawnStatic(sf::RenderWindow& window);

public:

	Obsticals(std::string);

	sf::RectangleShape outline;

	void setScale(float x, float y);
	void update(float dt);
	void checkAndRespawnDynamic_500_800(sf::RenderWindow& window);
	void checkAndRespawnDynamic_100_400(sf::RenderWindow& window);
	void checkAndRespawnStatic(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) const;
};