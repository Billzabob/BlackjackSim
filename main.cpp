#include "game.hpp"
#include "rules.hpp"
#include "strategy.hpp"

using namespace std;

int main() {
  Rules rules;
  rules.numDecks = 1;
  rules.hitOnSoft17 = true;
  rules.surrenderAllowed = true;
  rules.doubleAfterSplitAllowed = true;
  rules.blackjackNumerator = 3;
  rules.blackjackDenominator = 2;
  rules.shuffleCardsLeft = 20;

  Strategy strat;
  Game game(rules, strat);
  game.play();
}
