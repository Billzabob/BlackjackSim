#pragma once

#include "hand.hpp"
#include "shoe.hpp"
#include "strategy.hpp"

class Game {
 public:
  explicit Game(Strategy& strat);

  void play();

 private:
  void playHand();

  int playerScore();
  int dealerScore();

  static int calculateScore(std::vector<int> hand);

  Hand playerHand;
  Hand dealerHand;

  int playerMoney;
  Strategy& strat;
  Shoe shoe;
};
