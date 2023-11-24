#include "AnimationManager.h"

AnimationManager::AnimationManager()
{
}

bool AnimationManager::update(const sf::Time& dt, sf::Sprite& sprite,const std::vector<sf::Texture>& textures, const float frameDuration)
{
   animTimer += dt.asSeconds();

   if(animTimer>frameDuration)
   {
        currentFrame++;
        if( currentFrame + 1 > textures.size())
        {
            return true;
        }
        animTimer -= frameDuration;
        sprite.setTexture(textures.at(currentFrame));
   }
   return false;
}