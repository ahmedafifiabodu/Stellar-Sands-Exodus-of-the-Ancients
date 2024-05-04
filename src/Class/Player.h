#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerAnimation.h"

enum class AnimationMovementIndex
{
	runningR,	//0
	jumping,	//1
	crouch,		//2
	die,		//3
	Count		//4
};

class Player {
	float x, y;

	sf::Texture texture;
	sf::Sprite sprite;

	PlayerAnimation animationsMovement[int(AnimationMovementIndex::Count)];
	AnimationMovementIndex currentAnimationMovement = AnimationMovementIndex::runningR;

	sf::Vector2f position;
	sf::Vector2f velocity = { 0.f, 0.f };

	// Jumping Parameters
	sf::Clock jumpClock;
	float jumpTime = 0.0;
	float jumping = 0.0;
	bool isJumping = false;

	// Crouching Parameters
	bool isCrouching = false;

	void setPosition(float x, float y);

	//Player Movement
	static float doJumping(float time, float duration);
	void Jump(sf::Vector2f playerPosition, float playerDynamicPosotionY);
	void couch(bool isCrouching);

public:
	sf::RectangleShape outline;

	Player(float x, float y);

	// Getters
	sf::Color GetPlayerColor();
	sf::Vector2f GetPlayerPosition();

	// Setters
	void SetPlayerColor(sf::Color color);

	// Update and Draw
	void UpdateCurrentAnimation(const sf::Event& event, sf::Vector2f playerPosition, float playerDynamicPosotionY, int health);
	void Drawing(sf::RenderTarget& rt) const;
	void Update(float dt);
	void ShowMessage(sf::RenderWindow& window, Player player);
};
