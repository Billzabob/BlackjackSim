#include "hand.hpp"

using namespace std;

unsigned int Hand::score() const {
  unsigned int score = 0;
  unsigned int aces = 0;
  for (const auto& card : hand) {
    score += card;
    if (card == 1) aces++;
  }
  while (score <= 11 && aces > 0) {
    score += 10;
    aces--;
  }
  return score;
}

void Hand::clear() { hand.clear(); }

bool Hand::soft() const { return score() == (score() + 10); }

unsigned int Hand::numCards() const { return hand.size(); }

void Hand::operator<<(unsigned int card) { hand.push_back(card); }

unsigned int Hand::operator[](size_t i) const { return hand.at(i); }

bool Hand::operator==(unsigned int score) const {
  return this->score() == score;
}

bool Hand::operator<(unsigned int score) const { return this->score() < score; }

bool Hand::operator>(unsigned int score) const { return this->score() > score; }

bool Hand::operator==(const Hand& hand) const {
  return score() == hand.score();
}

bool Hand::operator<(const Hand& hand) const { return score() < hand.score(); }

bool Hand::operator>(const Hand& hand) const { return score() > hand.score(); }
