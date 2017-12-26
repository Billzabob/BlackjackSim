#include "hand.hpp"

using namespace std;

int Hand::score() const {
  int score = 0;
  int aces = 0;
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

void Hand::operator<<(int card) { hand.push_back(card); }

int Hand::operator[](int i) const { return hand[i]; }

bool Hand::operator==(int score) const { return this->score() == score; }

bool Hand::operator<(int score) const { return this->score() < score; }

bool Hand::operator>(int score) const { return this->score() > score; }

bool Hand::operator==(const Hand& hand) const {
  return score() == hand.score();
}

bool Hand::operator<(const Hand& hand) const { return score() < hand.score(); }

bool Hand::operator>(const Hand& hand) const { return score() > hand.score(); }
