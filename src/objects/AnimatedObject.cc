#include "AnimatedObject.h"

#include "engine/resource/TextureManager.h"

AnimatedObject::AnimatedObject()
    : MovingObject{}, m_loop{ false }, m_frameDuration{ 0.0f }, m_frames{}, m_animTimer{ 0.0f }, m_currentFrame{ 0 }, m_Path{ "" }
{
}

void AnimatedObject::animUpdate(const sf::Time& dt)
{
   m_animTimer += dt.asSeconds();

   if(m_animTimer>m_frameDuration)
   {
        m_currentFrame++;
        if( m_currentFrame + 1 > static_cast<int>(m_frames.size()))
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

void AnimatedObject::loadFrames(int amountOfFrames)
{
  TextureManager& texMgr{ TextureManager::instance() };
    
    for (int i { 0 }; i < amountOfFrames; ++i)
    {
	     m_frames.push_back(*texMgr.load(m_Path+ std::to_string(i) +".png"));
    }


    m_Texture = m_frames.at(m_currentFrame);

	m_Sprite.setTexture(m_Texture);
}