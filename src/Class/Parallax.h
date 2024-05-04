#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Obsticals.h"

class Parallax
{
	float windowsSizeX;
	float windowsResizeX;
	float windowsResizeY;
	float deltaTime = 0;

	bool isDrawing = false;

	float scaleX = 0.0;
	float scaleY = 0.0;
	const float defaultSpeed = -50.0f;

	const int numTextures = 12;
	const std::string texturePath = "Asset/Background/background_";
	const std::string fileExtension = ".png";

	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;
	std::vector<float> distances;
	std::vector<float> speeds;

	sf::Texture texturet1;
	sf::Texture texturet2;

	sf::Sprite spritet1;
	sf::Sprite spritet2;

public:

	Parallax(sf::RenderWindow& window);

	void parlx(float deltaTime);
	void draw(sf::RenderWindow& window, std::vector<Obsticals> obstacles, Player player) const;
};
