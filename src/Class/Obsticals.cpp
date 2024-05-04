#include "Obsticals.h"
#include <cstdlib>

Obsticals::Obsticals(std::string location)
{
	// Set up your enemy's appearance and properties

	if (!texture.loadFromFile(location))
	{
		std::cout << "The background_1 can't load" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setScale(200.f / texture.getSize().y, 200.f / texture.getSize().y);

	//For Debugging
	//outline.setTextureRect({ 0, 0, 120, 120 });
	//sf::Vector2f getSizeOutline(outline.getTextureRect().getSize());
	//outline.setSize(getSizeOutline);
	//outline.setOutlineColor(sf::Color::Blue);
	//outline.setOutlineThickness(2.f);
}

sf::Vector2i Obsticals::getSize() const {
	return sprite.getTextureRect().getSize();
}

sf::Vector2f Obsticals::getPosition() const {
	return sprite.getPosition();
}

sf::FloatRect Obsticals::getGlobalBounds() const {
	return sprite.getGlobalBounds();
}

void Obsticals::setScale(float x, float y) {
	sprite.setScale(x, y);
}

void Obsticals::spawnRandom_500_800(sf::RenderWindow& window) {
	// Spawn the enemy at a random location on the right side of the screen
	float yPos = static_cast<float>(std::rand() % (800 - 500 + 1) + 500); // range [500, 800]
	sprite.setPosition(window.getSize().x, yPos);

	//outline.setPosition(window.getSize().x + 100, yPos);
}

void Obsticals::spawnRandom_100_400(sf::RenderWindow& window)
{
	// Spawn the enemy at a random location on the right side of the screen
	float yPos = static_cast<float>(std::rand() % (400 - 100 + 1) + 100); // range [500, 800]
	sprite.setPosition(window.getSize().x, yPos);

	//outline.setPosition(window.getSize().x + 100, yPos);
}

void Obsticals::spawnStatic(sf::RenderWindow& window) {
	sprite.setPosition(window.getSize().x, window.getSize().y - 370);

	//outline.setPosition(window.getSize().x + 100, window.getSize().y - 370);
}

void Obsticals::update(float dt) {
	// Update any movement or animation logic here
	// For example, move the enemy towards the left
	sprite.move(-movementSpeed * dt, 0);

	//outline.move(-movementSpeed * dt, 0);
}

void Obsticals::draw(sf::RenderWindow& window) const {
	// Draw the enemy to the window
	window.draw(sprite);

	//window.draw(outline);
}

void Obsticals::checkAndRespawnDynamic_500_800(sf::RenderWindow& window)
{
	if (sprite.getPosition().x < 0 - sprite.getTextureRect().getSize().x) {
		spawnRandom_500_800(window);
	}
}

void Obsticals::checkAndRespawnDynamic_100_400(sf::RenderWindow& window)
{
	if (sprite.getPosition().x < 0 - sprite.getTextureRect().getSize().x) {
		spawnRandom_100_400(window);
	}
}

void Obsticals::checkAndRespawnStatic(sf::RenderWindow& window)
{
	if (sprite.getPosition().x < 0 - sprite.getTextureRect().getSize().x) {
		spawnStatic(window);
	}
}