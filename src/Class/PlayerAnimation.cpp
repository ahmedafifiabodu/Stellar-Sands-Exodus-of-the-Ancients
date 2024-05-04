#include "PlayerAnimation.h"

void PlayerAnimation::advance()
{
	if (++iFrameMovement >= nFramesMovement)
		iFrameMovement = 0;             //for looping the 8 frames
}

PlayerAnimation::PlayerAnimation(int x, int y, int width, int height) : time(0.0f), iFrameMovement(0)
{
	if (!playerTexture.loadFromFile("./Asset/Player/player.png")) {
		// handle error
	}

	for (int i = 0; i < nFramesMovement; ++i)
		framesMovement[i] = { x + i * width, y, width, height };
}

void PlayerAnimation::applyToSpritePlayer(sf::Sprite& s) const
{
	s.setTexture(playerTexture);

	s.setTextureRect(framesMovement[iFrameMovement]);  // Use framesMovement for movement animation
}

void PlayerAnimation::updateAnimation(float dt)
{
	time += dt;

	while (time >= holdTime)
	{
		time -= holdTime;
		advance();
	}
}