#include "shoe.hpp"

using namespace std;

struct EmptyDeck {};

Shoe::Shoe(int decks)
    : decks(decks), cardCount(decks * 52), gen(random_device()()) {
  reset();
}

int Shoe::drawCard() {
  if (cardCount <= 0) {
    throw EmptyDeck();
  }
  size_t randomIndex = dis(gen) % cardCount;
  int total = 0;
  int card = 0;
  for (size_t i = 1; i <= 10; ++i) {
    total += cards[i];
    if (total > randomIndex) {
      cards[i] = cards[i] - 1;
      cardCount--;
      card = i;
      break;
    }
  }
  return card;
}

void Shoe::reset() {
  for (size_t i = 1; i <= 9; ++i) {
    cards[i] = 4 * decks;
  }
  cards[10] = 16 * decks;
}
