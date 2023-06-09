#pragma once

#include "gem.h"
#include "board.h"
#include "game_configuration.h"

#include <SFML\Graphics.hpp>

class Game
{
public:
  Game();
  ~Game();
  bool init(GameŅonfiguration const& cfg);
  void loop();
private:
  bool setConfiguration(GameŅonfiguration const& cfg);

  sf::RenderWindow* m_window;
  sf::Text m_message;
  Board* m_board;
  int m_score;
};