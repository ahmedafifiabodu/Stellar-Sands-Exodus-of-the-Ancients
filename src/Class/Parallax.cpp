#include <SFML/Graphics.hpp>
#include "Parallax.h"

Parallax::Parallax(sf::RenderWindow& window) : textures(numTextures), sprites(numTextures * 2), distances(numTextures)
{
	windowsResizeX = static_cast<float>(window.getSize().x);
	windowsResizeY = static_cast<float>(window.getSize().y);

	const float initialDistance = 20.0f;

	speeds = { defaultSpeed, 2 * defaultSpeed, 3 * defaultSpeed, 4 * defaultSpeed, 5 * defaultSpeed, 6 * defaultSpeed,
							  7 * defaultSpeed, 8 * defaultSpeed, 9 * defaultSpeed, 10 * defaultSpeed, 11 * defaultSpeed, 12 * defaultSpeed };

	for (int i = 0; i < numTextures; ++i) {
		std::string filename = texturePath + std::to_string(i + 1) + fileExtension;

		if (!textures[i].loadFromFile(filename)) {
			std::cout << "The background_" << i + 1 << " can't load" << std::endl;
		}

		scaleY = windowsResizeY / (textures[0].getSize().y);
		windowsSizeX = textures[0].getSize().x * scaleY;

		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) * 2].setTexture(textures[i]);
		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) * 2 + 1].setTexture(textures[i]);
		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) * 2].setPosition(0, 0);
		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) * 2 + 1].setPosition(windowsSizeX, 0);
		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) * 2].setScale(scaleY, scaleY);
		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) * 2 + 1].setScale(scaleY, scaleY);
	}

	if (!texturet1.loadFromFile("Asset/Background/Temple.jpg"))
	{
		std::cout << "The temple_1 can't load" << std::endl;
	}
	if (!texturet2.loadFromFile("Asset/Background/temple_1.png"))
	{
		std::cout << "The temple_2 can't load" << std::endl;
	}

	spritet1.setTexture(texturet1);
	spritet1.setPosition(windowsSizeX * 3, 0);

	spritet2.setTexture(texturet2);
	spritet2.setPosition(windowsSizeX * 3, 0);

	spritet1.setScale(scaleY, scaleY);
	spritet2.setScale(scaleY, scaleY);
}

void Parallax::parlx(float deltaTime)
{
	for (int i = 0; i < numTextures; ++i)
	{
		distances[i] = speeds[i] * deltaTime;
	}

	for (int i = 0; i < sprites.size(); i += 2) {
		sprites[i].setPosition(sprites[i].getPosition().x + distances[i / 2], 0);
		sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) + 1].setPosition(sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) + 1].getPosition().x + distances[i / 2], 0);

		if (sprites[i].getPosition().x <= -windowsSizeX)
			sprites[i].setPosition(windowsSizeX + sprites[i + 1].getPosition().x, 0);

		if (sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) + 1].getPosition().x <= -windowsSizeX)
			sprites[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) + 1].setPosition(windowsSizeX + sprites[i].getPosition().x, 0);
	}

	spritet1.setPosition(spritet1.getPosition().x + distances[11], 0);
	spritet2.setPosition(spritet1.getPosition().x + distances[11], 0);

	if (spritet1.getPosition().x <= -(windowsSizeX * 2))
	{
		spritet1.setPosition(windowsSizeX, 0);
		spritet2.setPosition(windowsSizeX, 0);
	}
}

void Parallax::draw(sf::RenderWindow& window, std::vector<Obsticals> obstacles, Player player) const
{
	for (auto it = sprites.begin(); it != sprites.begin() + 18; ++it) {
		window.draw(*it);
	}

	window.draw(spritet1);

	for (const auto& obstacle : obstacles)
	{
		obstacle.draw(window);
	}

	player.Drawing(window);

	for (auto it = sprites.begin() + 18; it != sprites.begin() + 24; ++it) {
		window.draw(*it);
	}

	window.draw(spritet2);
}