#include "AnimatedObject.h"


void AnimatedObject::animUpdate(const sf::Time& dt)
{
   m_animTimer += dt.asSeconds();

   if(m_animTimer>m_frameDuration)
   {
        m_currentFrame++;
        if( m_currentFrame + 1 > m_frames.size())
        {
            if (!m_loop)
            {
                m_Dead = true;
                return;
            }
            else
                m_currentFrame = 0;
        }
        m_animTimer -= m_frameDuration;
        m_Sprite.setTexture(m_frames.at(m_currentFrame));
   }
}