#pragma once

struct Rules {
  unsigned int numDecks;
  bool hitOnSoft17;
  bool surrenderAllowed;
  bool doubleAfterSplitAllowed;
  unsigned int blackjackNumerator;
  unsigned int blackjackDenominator;
  // Shuffle deck when less than this number of cards.
  unsigned int shuffleCardsLeft;
};
