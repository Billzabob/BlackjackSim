#include "game.hpp"
#include "strategy.hpp"

int main() {
  Strategy strat;
  Game game(strat);
  game.play();
}
