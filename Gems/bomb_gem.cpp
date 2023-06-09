#include "bomb_gem.h"
#include <cstdlib>

BombGem::BombGem(float x, float y, ESprite sprite)
  : Gem(x, y, sprite)
{
  sf::Vector2f size(Gem::ONE_SPRITE_WIDTH, Gem::ONE_SPRITE_WIDTH);
  this->m_bomb.setSize(size);
  this->m_bomb.setOrigin(size / 2.f);

  this->m_bomb.setTexture(&Gem::SPRITE);
  this->m_bomb.setTextureRect(
    sf::IntRect(
      static_cast<int>(Gem::ONE_SPRITE_WIDTH * static_cast<int>(EBonusSprite::BS_BOMB)), 
      static_cast<int>(Gem::ONE_SPRITE_WIDTH),
      static_cast<int>(Gem::ONE_SPRITE_WIDTH), static_cast<int>(Gem::ONE_SPRITE_WIDTH)
    )
  );

  this->m_bomb.setPosition(x, y);
}

void BombGem::setPosition(sf::Vector2f pos) {
  Gem::setPosition(pos);
  this->m_bomb.setPosition(pos);
}

void BombGem::draw(sf::RenderWindow* window) const {
  Gem::draw(window);
  window->draw(this->m_bomb);
}

int BombGem::activate(std::vector<std::vector<Gem*>>& gems, size_t i, size_t j, size_t width, size_t height) {
  Gem* tmp = gems.at(i).at(j);
  int score = 0;
  sf::Vector2f pos = this->getPosition();
  gems.at(i).at(j) = new Gem(pos.x, pos.y, ESprite::S_NONE);

  int ni = rand() % height;
  int nj = rand() % width;

  score += gems.at(ni).at(nj)->activate(gems, ni, nj, width, height);

  if (ni + 1 < height)
    score += gems.at(ni).at(nj)->activate(gems, ni + 1, nj, width, height);

  if (nj + 1 < width)
    score += gems.at(ni).at(nj)->activate(gems, ni, nj + 1, width, height);

  if (ni - 1 >= 0)
    score += gems.at(ni).at(nj)->activate(gems, ni - 1, nj, width, height);

  if (nj - 1 >= 0)
    score += gems.at(ni).at(nj)->activate(gems, ni, nj - 1, width, height);

  delete tmp;
  return static_cast<int>(EGemScore::GS_BOMB) + score;
}