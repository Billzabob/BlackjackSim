#pragma once

#include <array>
#include <random>
#include <vector>

class Shoe {
 public:
  explicit Shoe(int decks);

  int drawCard();

  void reset();

 private:
  const int decks;
  std::array<int, 11> cards;
  int cardCount;
  // RNG
  std::mt19937 gen;
  std::uniform_int_distribution<int> dis;
};
