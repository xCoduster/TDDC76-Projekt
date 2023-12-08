#include "catch.hpp"
#include "objects/Object.h"
#include "objects/Projectile.h"
#include "engine/resource/AudioManager.h"
#include "engine/resource/TextureManager.h"

using namespace std;

TEST_CASE ("Projectile")
{
    sf::Clock clock;
    std::vector<Object*> new_objects;
    sf::Vector2f lazer_position {100.0f, 100.0f};
    Projectile* lazer{ new Projectile(lazer_position)};
    
    SECTION("constructor")
    {
        
        CHECK( lazer -> getPosition().x == lazer_position.x );
        CHECK( lazer -> getPosition().y == lazer_position.y );
    }

   SECTION("Update")
   {
    sf::Vector2f out_of_bounds {1000.0f, 1000.0f};
    lazer -> setPosition(out_of_bounds);
    sf::Time now = clock.getElapsedTime();
    lazer -> update(now, new_objects);
    CHECK(lazer -> isDead());
    //CHECK( lazer -> getPosition().x)
    /*
      Time t0{0,0,0};
      Time t1{12,30,30};
      Time t2{23,59,59};

      CHECK_THROWS( Time{13,35,60} );
      CHECK_THROWS( Time{13,60,35} );
      CHECK_THROWS( Time{24,35,35} );
             
      CHECK( t0.get_hour()   == 0 );
      CHECK( t0.get_minute() == 0 );
      CHECK( t0.get_second() == 0 );
      CHECK( t1.get_hour()   == 12 );
      CHECK( t1.get_minute() == 30 );
      CHECK( t1.get_second() == 30 );
      CHECK( t2.get_hour()   == 23 );
      CHECK( t2.get_minute() == 59 );
      CHECK( t2.get_second() == 59 );
      */
   }
   SECTION("Collision")
   {
    
   }
}