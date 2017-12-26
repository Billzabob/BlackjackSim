#include "shoe.hpp"

using namespace std;

Shoe::Shoe(int decks)
    : decks(decks), cardCount(decks * 52), gen(random_device()()) {
  reset();
}

int Shoe::drawCard() {
  size_t randomIndex = dis(gen) % cardCount;
  int total = 0;
  for (size_t i = 1; i <= 10; ++i) {
    total += cards[i];
    if (total > randomIndex) return i;
  }
}

void Shoe::reset() {
  for (size_t i = 1; i <= 9; ++i) {
    cards[i] = 4 * decks;
  }
  cards[10] = 16 * decks;
}
