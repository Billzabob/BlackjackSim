#pragma once

#include <array>
#include <random>

class Shoe {
 public:
  explicit Shoe(unsigned int decks);

  unsigned int drawCard();

  void reset();

  unsigned int getCardCount() const;

 private:
  const unsigned int decks;
  std::array<int, 11> cards;
  unsigned int cardCount;
  // RNG
  std::mt19937 gen;
  std::uniform_int_distribution<unsigned int> dis;
};
