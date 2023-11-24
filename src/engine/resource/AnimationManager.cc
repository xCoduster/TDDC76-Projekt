#include "AnimationManager.h"

AnimationManager::AnimationManager(std::vector<sf::Texture> textures, float frameDuration)
{
    animTimer = 0;
    currentFrame = 0;

    frames = textures;
    animSpeed = frameDuration;
}

void AnimationManager::update(const sf::Time& dt, sf::Sprite& sprite)
{
   animTimer += dt.asSeconds();
   if(animTimer>animSpeed)
   {
        animTimer -= animSpeed;
        currentFrame++;
        sprite.setTexture(frames.at(currentFrame));
   }
}