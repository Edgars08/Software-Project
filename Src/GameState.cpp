#include "GameState.h"
#include "StateManager.h"
#include "Definations.h"
#include "GameOverState.h"

namespace EdgarSam
{
    GameState::GameState(GameDataPtr data) : _data(data)
    {
    }
    GameState::~GameState()
    {
        delete this->space;
        delete this->spaceShip;
        delete this->score;
        for (auto *ship_laser : ship_lasers)
        {
            delete ship_laser;
        }
        for (auto *asteroid : asteroids)
        {
            delete asteroid;
        }
        for (auto *lander : landers)
        {
            delete lander;
        }
        for (auto *lander_laser : lander_lasers)
        {
            delete lander_laser;
        }
    }
    void GameState::InitState()
    {
        // OBJECT
        this->spaceShip = new SpaceShip(_data);
        this->space = new Space(_data);
        this->score = new Score(_data);

        // start the cloks
        this->clock_1.restart();
        this->clock_2.restart();
        this->clock_3.restart();

        this->gamescore = 0;
        this->score->UpdateScore(this->gamescore);
        this->checkSize = false;
    }
    void GameState::HandleInput()
    {
        sf::Event event;
        while (_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                _data->window.close();
            }
        }
    }

    void GameState::shootShipLasers()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            ship_lasers.push_back(new Lasers(_data, sf::Vector2f(spaceShip->getPosition().x, spaceShip->getPosition().y + spaceShip->getBounds().height * 0.45f), spaceShip->getDirection()));
        }
    }
    void GameState::shootLanderLasers()
    {
        if (this->clock_3.getElapsedTime().asSeconds() > LANDERLASER_SPAWNTIME)
        {
            this->randomIndex = rand() % landers.size();
            lander_lasers.push_back(new Lasers(_data, sf::Vector2f(landers[randomIndex]->getPosition().x, landers[randomIndex]->getPosition().y + landers[randomIndex]->getBounds().height * 0.45f), landers[randomIndex]->getDirection(), false));
            this->clock_3.restart();
        }
    }

    void GameState::InitLander()
    {
        if (this->clock_2.getElapsedTime().asSeconds() > LANDER_SPAWNTIME && landers.size() < LANDER_COUNT)
        {
            landers.push_back(new Lander(_data));
            this->checkSize = true;
            this->clock_2.restart();
        }
    }

    void GameState::InitAsteroid()
    {
        if (this->clock_1.getElapsedTime().asSeconds() > ASTERIOD_SPAWNTIME)
        {
            asteroids.push_back(new Asteroid(_data));
            this->clock_1.restart();
        }
    }

    void GameState::UpdateShipLaser(float dt)
    {
        for (unsigned int counter = 0; counter < ship_lasers.size(); counter++)
        {
            ship_lasers[counter]->Update(dt);
            if (ship_lasers[counter]->getBounds().left + ship_lasers[counter]->getBounds().width < 0 || ship_lasers[counter]->getBounds().left > _data->window.getSize().x)
            {
                delete ship_lasers[counter];
                ship_lasers.erase(ship_lasers.begin() + counter);
            }
        }
    }

    void GameState::UpdateAsteroid(float dt)
    {
        for (unsigned int counter = 0; counter < asteroids.size(); counter++)
        {
            this->asteroids[counter]->Update(dt);
            if (asteroids[counter]->getBounds().top > _data->window.getSize().y)
            {
                delete asteroids[counter];
                asteroids.erase(asteroids.begin() + counter);
            }
        }
    }
    void GameState::UpdateLander(float dt)
    {
        for (unsigned int counter = 0; counter < landers.size(); counter++)
        {
            landers[counter]->update(dt);
        }
    }
    void GameState::UpdateLanderLaser(float dt)
    {
        for (auto &laser : lander_lasers)
        {
            laser->Update(dt);
            if (laser->getBounds().left + laser->getBounds().width < 0 || laser->getBounds().left > _data->window.getSize().x)
            {
                delete laser;
                lander_lasers.erase(std::remove(lander_lasers.begin(), lander_lasers.end(), laser), lander_lasers.end());
            }
        }
    }
    template <typename T>
    void GameState::shipCollision(T &enemy)
    {
        bool collided = false;
        auto shipBounds = sf::FloatRect(spaceShip->getPosition().x + spaceShip->getBounds().width / 3.0f, spaceShip->getPosition().y + spaceShip->getBounds().height / 3.0f, spaceShip->getBounds().width * 2 / 3, spaceShip->getBounds().height * 2 / 3);
        for (auto &element : enemy)
        {
            if (element->getBounds().intersects(shipBounds))
            {
                collided = true;
                break;
            }
        }
        if (collided)
        {
            _data->states.PushState(std::unique_ptr<State>(new GameOverState(_data)), true);
        }
    }
    template <typename G>
    void GameState::laserCollision(G &enemy_1)
    {
        for (unsigned int i = 0; i < enemy_1.size(); ++i)
        {
            bool isremoved = false;

            for (unsigned int k = 0; k < ship_lasers.size() && isremoved == false; ++k)
            {
                if (ship_lasers[k]->getBounds().intersects(enemy_1[i]->getBounds()))
                {
                    // freeing up the memory allocated for the asteroid and laser object.
                    delete enemy_1[i];
                    delete ship_lasers[k];
                    // removes the asteroid and laser objects from the vectors.
                    ship_lasers.erase(ship_lasers.begin() + k);
                    enemy_1.erase(enemy_1.begin() + i);
                    isremoved = true;

                    this->gamescore++;
                    this->score->UpdateScore(this->gamescore);
                }
            }
        }
    }

    template <typename U>
    void GameState::draw(U &enemy)
    {
        for (auto *element : enemy)
        {
            element->draw();
        }
    }

    void GameState::checkCollision()
    {
        this->laserCollision(asteroids);
        this->shipCollision(landers);
        this->shipCollision(asteroids);
        this->laserCollision(landers);
        this->shipCollision(lander_lasers);
    }

    void GameState::Update(float dt)
    {
        this->space->update(dt);
        this->spaceShip->update(dt);
        this->shootShipLasers();
        this->InitAsteroid();
        this->InitLander();
        this->shootLanderLasers(); //
        this->UpdateShipLaser(dt);
        this->UpdateAsteroid(dt);
        this->UpdateLander(dt);
        this->UpdateLanderLaser(dt);
        this->checkCollision();
        if (landers.size() == 0 && this->checkSize)
        {
            _data->states.PushState(std::unique_ptr<State>(new GameOverState(_data)), true);
        }
    }

    void GameState::Draw(float dt)
    {
        _data->window.clear();
        this->space->draw();
        this->spaceShip->draw();
        this->draw(asteroids);
        this->draw(landers);
        this->draw(ship_lasers);
        this->draw(lander_lasers);
        this->score->draw();
        _data->window.display();
    }
}