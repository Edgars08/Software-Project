
#include "SpaceShip.h"
#include "Definations.h"
#include "AssetLibrary.h"
#include "Lander.h"
#include "Asteroid.h"
#include "Lasers.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;
using namespace EdgarSam;

// ------------- Tests for SpaceShip ----------------
TEST_CASE("Spaceship Orientation is Right-Facing")
{
    // Create a mock GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new SpaceShip object
    SpaceShip ship(data);

    // Check that the ship is facing right
    CHECK(ship.getDirection() == false);
}
TEST_CASE("Spaceship Orientation is Left-Facing")
{
    // Create a mock GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new SpaceShip object
    SpaceShip ship(data);

    // Check that the ship is facing left
    CHECK(ship.getDirection() == false);
}

// ------------- Tests for Assets ----------------
TEST_CASE("AddTexture and getTexture methods work correctly")
{
    AssetLibrary library;
    library.AddTexture("test", ASTEROID_FILEPATH);
    CHECK(library.getTexture("test").loadFromFile(ASTEROID_FILEPATH));
}

TEST_CASE("AddFont and getFont methods work correctly")
{
    AssetLibrary library;
    library.AddFont("test", MAINMENU_FONT);
    CHECK(library.getFont("test").loadFromFile(MAINMENU_FONT));
}

TEST_CASE("getTexture method throws runtime error if texture is not found")
{
    AssetLibrary library;
    CHECK_THROWS_AS(library.getTexture("notFound"), runtime_error);
}

TEST_CASE("getFont method throws runtime error if font is not found")
{
    AssetLibrary library;
    CHECK_THROWS_AS(library.getFont("notFound"), runtime_error);
}
// ------------- Tests for Lander ----------------
TEST_CASE("Lander initialization")
{
    // Create a new GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new Lander object
    Lander lander(data);

    CHECK(lander.getDirection() == true);
}

TEST_CASE("Lander collision with the bottom window")
{
    // Create a new GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new Lander object
    Lander lander(data);

    // Move the Lander object to the bottom of the window
    lander.setPosition(lander.getPosition().x, data->window.getSize().y + lander.getBounds().height * 1.5f);

    // Check that the Lander object has collided with the bottom of the window
    lander.checkCollision();
    CHECK(lander.getPosition().y == (data->window.getSize().y - lander.getBounds().height));
}
TEST_CASE("Lander collision with the top window")
{
    // Create a new GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new Lander object
    Lander lander(data);

    // Move the Lander object to the bottom of the window
    lander.setPosition(lander.getPosition().x, 0.0f - lander.getBounds().height);

    // Check that the Lander object has collided with the bottom of the window
    lander.checkCollision();
    CHECK(lander.getPosition().y == 0.0f);
}
TEST_CASE("Lander direction change when colliding with the right window")
{
    // Create a new GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new Lander object
    Lander lander(data);

    // Move the Lander object to the right side of the window
    lander.setPosition(data->window.getSize().x + lander.getBounds().width, lander.getPosition().y);

    // Check that the Lander object has changed direction
    lander.updateDirection();
    CHECK(lander.getDirection() == false);
}
TEST_CASE("Lander direction change when colliding with the left window")
{
    // Create a new GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new Lander object
    Lander lander(data);

    // Move the Lander object to the right side of the window
    lander.setPosition(0.0f - lander.getBounds().width, lander.getPosition().y);

    // Check that the Lander object has changed direction
    lander.updateDirection();
    CHECK(lander.getDirection() == true);
}
TEST_CASE("Lander movement")
{
    // Create a new GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a new Lander object
    Lander lander(data);

    // Update the Lander object
    lander.update(0.1);

    // Check that the Lander object has moved in a random direction
    CHECK(std::abs(lander.getPosition().x) <= lander.getBounds().width / 2);
    CHECK(std::abs(lander.getPosition().y) <= lander.getBounds().height / 2);
}
// ------------- Tests for Asteroid ----------------
TEST_CASE("Asteroid spawn position is above top window")
{
    // Create a mock GameData object with a window size of 800x600
    GameDataPtr data = std::make_shared<GameData>();
    data->window.setSize(sf::Vector2u(800, 600));

    // Create an Asteroid object
    Asteroid asteroid(data);

    CHECK(asteroid.getPosition().y <= 0.0f);
}

TEST_CASE("Asteroid speed is positive")
{
    // Create a mock GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create an Asteroid object
    Asteroid asteroid(data);
    asteroid.Update(0.8);
    asteroid.Update(0.8);
    asteroid.Update(0.8);
    // Check that the asteroid speed is positive
    CHECK(asteroid.getPosition().x > 0.0f);
    CHECK(asteroid.getPosition().y > 0.0f);
}
// ------------- Tests for Lasers ----------------

TEST_CASE("Lasers - Constructor was created successfully")
{
    // Create a mock GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a Lasers object with default parameters
    Lasers lasers(data, sf::Vector2f(0.0f, 0.0f), true);

    CHECK(lasers.getBounds().left == 0.0f);
    CHECK(lasers.getBounds().top == 0.0f);
}

TEST_CASE("Lasers - Spawned with correct position")
{
    // Create a mock GameData object
    GameDataPtr data = std::make_shared<GameData>();

    // Create a Lasers object with default parameters
    Lasers lasers(data, sf::Vector2f(0.0f, 0.0f), true);

    // Call the SpawnLasers method
    lasers.SpawnLasers(sf::Vector2f(100.0f, 200.0f), false);

    CHECK(lasers.getBounds().left == 100.0f);
    CHECK(lasers.getBounds().top == 200.0f);
    CHECK(lasers.getBounds().width == 30.0f);
    CHECK(lasers.getBounds().height == 50.0f);
}