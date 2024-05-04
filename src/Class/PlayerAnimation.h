#pragma once
#include <SFML/Graphics.hpp>

class PlayerAnimation
{
    static constexpr float holdTime = 0.15f;
    static constexpr int nFramesMovement = 7;

    sf::Texture playerTexture;

    sf::IntRect framesMovement[nFramesMovement];

    float time = 0.0f;
    int iFrameMovement = 0;

    void advance();

public:
    PlayerAnimation() = default;
    PlayerAnimation(int x, int y, int width, int height);

    void applyToSpritePlayer(sf::Sprite& s) const;
    void updateAnimation(float dt);
};

