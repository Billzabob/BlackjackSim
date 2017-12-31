#include "shoe.hpp"

using namespace std;

struct EmptyDeck {};

Shoe::Shoe(unsigned int decks)
    : decks(decks), cardCount(decks * 52), gen(random_device()()) {
  reset();
}

unsigned int Shoe::drawCard() {
  if (cardCount == 0) {
    throw EmptyDeck();
  }
  size_t randomIndex = dis(gen) % cardCount;
  unsigned int total = 0;
  unsigned int card = 0;
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
  cardCount = 52 * decks;
}

unsigned int Shoe::getCardCount() const { return cardCount; }
