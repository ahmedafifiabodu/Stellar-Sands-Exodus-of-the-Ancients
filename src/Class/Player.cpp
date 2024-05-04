#include "Player.h"
#include <iostream>

Player::Player(float x, float y) : x(x), y(y), position(x, y)
{
	constexpr int tileSizesx = 300;
	constexpr int tileSizesy = 300;
	constexpr int animationDelay = 40;

	constexpr int WalkingRightIndex = int(AnimationMovementIndex::runningR);
	constexpr int WalkingJumpIndex = int(AnimationMovementIndex::jumping);
	constexpr int WalkingCrouchIndex = int(AnimationMovementIndex::crouch);
	constexpr int WalkingDieIndex = int(AnimationMovementIndex::die);

	animationsMovement[WalkingRightIndex] = PlayerAnimation(animationDelay, 0, tileSizesx, tileSizesy);
	animationsMovement[WalkingJumpIndex] = PlayerAnimation(animationDelay, 300, tileSizesx, tileSizesy);
	animationsMovement[WalkingCrouchIndex] = PlayerAnimation(0, 900, tileSizesx, tileSizesy);
	animationsMovement[WalkingDieIndex] = PlayerAnimation(0, 1200, tileSizesx, tileSizesy);

	sprite.setTextureRect({ 0, 0, tileSizesx , tileSizesy });
	sprite.setPosition(x, y);
	//sprite.setColor(sf::Color::Red);

	//For Debugging
	//sf::Vector2f getSizeOutline(static_cast<float>(sprite.getTextureRect().getSize().x - 150), static_cast<float>(sprite.getTextureRect().getSize().y - 50));
	//outline.setSize(getSizeOutline);
	//outline.setPosition(100, 1080 - 480);
	//outline.setOutlineColor(sf::Color::Green);
	//outline.setOutlineThickness(2.f);
}

void Player::Drawing(sf::RenderTarget& rt) const
{
	rt.draw(outline);
	rt.draw(sprite);
}

float Player::doJumping(float time, float duration)
{
	return (-4 / (duration * duration)) * time * time + (4 / duration) * time;
}

void Player::Jump(sf::Vector2f playerPosition, float playerDynamicPosotionY)
{
	jumpTime = jumpClock.getElapsedTime().asSeconds();

	if (isJumping == true)
	{
		jumping = static_cast<float>(playerPosition.y + (-(playerPosition.y / 1.5)) * doJumping(jumpTime, 1));
		outline.setPosition(playerPosition.x, jumping);
		sprite.setPosition(playerPosition.x, jumping);
	}

	if (playerDynamicPosotionY >= playerPosition.y)
	{
		isJumping = false;
		currentAnimationMovement = AnimationMovementIndex::runningR;
	}
}

void Player::couch(bool isCrouching)
{
	if (isCrouching == true)
	{
		sf::Vector2f getSizeOutline(static_cast<float>(sprite.getTextureRect().getSize().x - 250), static_cast<float>(sprite.getTextureRect().getSize().y - 150));
		outline.setSize(getSizeOutline);

		outline.setPosition(260, 1080 - 360);

		currentAnimationMovement = AnimationMovementIndex::crouch;
	}
	else
	{
		isCrouching = false;
		currentAnimationMovement = AnimationMovementIndex::runningR;
	}
}

void Player::UpdateCurrentAnimation(const sf::Event& event, sf::Vector2f playerPosition, float playerDynamicPosotionY, int health)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
	{
		currentAnimationMovement = AnimationMovementIndex::jumping;
		isJumping = true;
		jumpClock.restart();
	}

	Jump(playerPosition, playerDynamicPosotionY);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !isCrouching)
	{
		couch(true);
	}

	if (health == 0)
	{
		currentAnimationMovement = AnimationMovementIndex::die;
	}
}

void Player::Update(float dt)
{
	// For Debugging
	//sf::Vector2f getSizeOutline(static_cast<float>(sprite.getTextureRect().getSize().x - 150), static_cast<float>(sprite.getTextureRect().getSize().y - 50));
	//outline.setSize(getSizeOutline);
	//outline.setPosition(100, 1080 - 480);

	animationsMovement[static_cast<int>(currentAnimationMovement)].updateAnimation(dt);
	animationsMovement[static_cast<int>(currentAnimationMovement)].applyToSpritePlayer(sprite);
}

sf::Vector2f Player::GetPlayerPosition()
{
	return sprite.getPosition();
}

void Player::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

sf::Color Player::GetPlayerColor()
{
	return sprite.getColor();
}

void Player::SetPlayerColor(sf::Color color)
{
	sprite.setColor(color);
}

void Player::ShowMessage(sf::RenderWindow& window, Player player)
{
	sf::Font font;
	if (!font.loadFromFile("./Asset/Font/dDamel.ttf")) {
		std::cerr << "Error loading font" << std::endl;
		return;
	}

	sf::Texture texture;
	sf::Sprite sprite;

	if (!texture.loadFromFile("Asset/Background/Death.png"))
	{
		std::cout << "The Death can't load" << std::endl;
	}

	sprite.setTexture(texture);
	sprite.setPosition(-200.f, -200.f);
	sprite.setScale(1.2f, 1.5f);

	window.clear({ 20,20,20,150 });

	sf::Text text("Game Over!!", font);
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::Red);
	text.setOrigin(text.getPosition().x / 2.f, text.getPosition().y / 2.f);
	text.setPosition(window.getSize().x / 3.f, (window.getSize().y / 2.f) - 50);

	window.draw(sprite);
	window.draw(text);

	player.Drawing(window);
}