#include "catch.hpp"
#include "objects/Object.h"
#include "objects/playerprojectiles/Lazer.h"
#include "objects/playerprojectiles/Missile.h"
#include "objects/Explosion.h"
#include "objects/enemies/Seeker.h"
#include "objects/enemies/UFO.h"
#include "objects/enemies/Boss.h"
#include "objects/Bomb.h"
#include "objects/Player.h"
#include "engine/resource/AudioManager.h"
#include "engine/resource/TextureManager.h"
#include <cmath>

using namespace std;
// inspiration togs från time.pdf sida 10, flyttalsjämförelse
bool compare(float lhs, float rhs )
{
    return abs(lhs - rhs) <= 1e-4;
}

TEST_CASE ("Lazer")
{
    sf::Clock clock;
    std::vector<Object*> new_objects;
    sf::Vector2f position {100.0f, 100.0f};
    Lazer* lazer{ new Lazer(position)};
    Lazer* lazer2{ new Lazer(position)};
    Player* player{ new Player()};
    
    SECTION("Constructor")
    {
        
        CHECK( lazer -> getPosition().x == position.x );
        CHECK( lazer -> getPosition().y == position.y );
    }

   SECTION("Update")
   {
    sf::Time now = clock.getElapsedTime();
    lazer -> update(now, new_objects);
    CHECK( compare( lazer -> getPosition().x, 250.0f * now.asSeconds() + 100.0f));
    CHECK( compare( lazer -> getPosition().y, 100.0f));

    sf::Vector2f out_of_bounds {1000.0f, 1000.0f};
    lazer -> setPosition(out_of_bounds);
    lazer -> update(now, new_objects);
    CHECK(lazer -> isDead());

   }
   SECTION("Collision")
   {
    Seeker* seeker{ new Seeker(player)};
    seeker -> setPosition(position);
    lazer -> Collision(seeker, new_objects);
    seeker -> Collision(lazer, new_objects);
    CHECK( lazer -> isDead() );
    CHECK(seeker -> getHitpoints() == 1);
    seeker -> Collision(lazer, new_objects);
    CHECK(seeker -> getHitpoints() == 0);

    Bomb* bomb{ new Bomb()};
    bomb -> setPosition(position);
    bomb -> Collision(lazer, new_objects);
    CHECK( bomb -> isDead());
    CHECK( new_objects.size() == 1);

    Boss* boss{ new Boss()};
    int oldHP = boss -> getHitpoints();
    boss -> setPosition(position);
    boss -> Collision(lazer, new_objects);
    CHECK( boss -> getHitpoints() == oldHP - 1 );

    UFO* ufo{ new UFO()};
    oldHP = ufo -> getHitpoints();
    ufo -> setPosition(position);
    ufo -> Collision(lazer, new_objects);
    CHECK(ufo -> getHitpoints() == oldHP - 1 );

    Explosion* explosion{ new Explosion(position)};
    lazer2 -> Collision(explosion, new_objects);
    CHECK( lazer2 -> isDead() );
   }
}

TEST_CASE ("Missile")
{
    sf::Clock clock;
    std::vector<Object*> new_objects;
    sf::Vector2f position {100.0f, 100.0f};
    Missile* rocket{ new Missile(position)};
    Missile* rocket2{ new Missile(position)};
    Player* player{ new Player()};
    
    SECTION("Constructor")
    {
        
        CHECK( rocket -> getPosition().x == position.x );
        CHECK( rocket -> getPosition().y == position.y );
    }

   SECTION("Update")
   {
    sf::Time now = clock.getElapsedTime();
    rocket -> update(now, new_objects);
    CHECK( compare( rocket -> getPosition().x, 250.0f * now.asSeconds() + 100.0f));
    CHECK( compare( rocket -> getPosition().y, 100.0f));

    sf::Vector2f out_of_bounds {1000.0f, 1000.0f};
    rocket -> setPosition(out_of_bounds);
    rocket -> update(now, new_objects);
    CHECK(rocket -> isDead());

   }
   SECTION("Collision")
   {
    Seeker* seeker{ new Seeker(player)};
    seeker -> setPosition(position);
    rocket -> Collision(seeker, new_objects);
    seeker -> Collision(rocket, new_objects);
    CHECK( rocket -> isDead() );
    CHECK( new_objects.size() == 1);
    CHECK(seeker -> getHitpoints() == 1);
    seeker -> Collision(rocket, new_objects);
    CHECK(seeker -> getHitpoints() == 0);

    Bomb* bomb{ new Bomb()};
    bomb -> setPosition(position);
    bomb -> Collision(rocket, new_objects);
    CHECK( bomb -> isDead());
    CHECK( new_objects.size() == 2);

    Boss* boss{ new Boss()};
    int oldHP = boss -> getHitpoints();
    boss -> setPosition(position);
    boss -> Collision(rocket, new_objects);
    CHECK( boss -> getHitpoints() == oldHP - 1 );

    UFO* ufo{ new UFO()};
    oldHP = ufo -> getHitpoints();
    ufo -> setPosition(position);
    ufo -> Collision(rocket, new_objects);
    CHECK(ufo -> getHitpoints() == oldHP - 1 );

    Explosion* explosion{ new Explosion(position)};
    rocket2 -> Collision(explosion, new_objects);
    CHECK( rocket2 -> isDead() );
   }
}