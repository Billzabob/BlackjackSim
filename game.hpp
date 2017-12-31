#pragma once

#include "hand.hpp"
#include "rules.hpp"
#include "shoe.hpp"
#include "strategy.hpp"

class Game {
 public:
  explicit Game(const Rules& rules, const Strategy& strat);

  void play();

 private:
  void playHand();

  Hand playerHand;
  Hand dealerHand;

  int playerMoney;
  const Strategy& strat;
  const Rules& rules;
  Shoe shoe;
};
