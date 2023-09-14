#include "Score.h"

namespace EdgarSam
{

   Score::Score(GameDataPtr data) : _data{data}
   {
      // Load Font
      this->_data->assets.AddFont("ScoreFont", SCORE_FONT);
      // Setting the font
      this->_scoreValue.setFont(_data->assets.getFont("ScoreFont"));
      this->_scoreValue.setString("0");
      this->_scoreValue.setCharacterSize(20);
      this->_scoreValue.setFillColor(sf::Color::Green);
      this->_scoreValue.setPosition(_data->window.getSize().x / 20, _data->window.getSize().y / 50);

   }

   void Score::UpdateScore(int score)
   {
      _scoreValue.setString("Score: " + std::to_string(score));
   }
  
   void Score::draw()
   {
      _data->window.draw(_scoreValue);
   }

}