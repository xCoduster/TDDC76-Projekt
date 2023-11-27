#include "AnimatedObject.h"


void AnimatedObject::animUpdate(const sf::Time& dt)
{
   m_animTimer += dt.asSeconds();

   if(m_animTimer>m_frameDuration)
   {
        m_currentFrame++;
        if( m_currentFrame + 1 > m_frames.size())
        {
            m_Dead = true;
            return;
        }
        m_animTimer -= m_frameDuration;
        m_Sprite.setTexture(m_frames.at(m_currentFrame));
   }
}