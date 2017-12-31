#include "game.hpp"

#include <iostream>
#include <vector>

using namespace std;

Game::Game(const Rules& rules, const Strategy& strat)
    : playerMoney(0), strat(strat), rules(rules), shoe(rules.numDecks) {}

void Game::play() {
  while (true) {
    playHand();
    if (shoe.getCardCount() < rules.shuffleCardsLeft) {
      cout << "Shuffling deck" << endl << endl;
      shoe.reset();
    }
  }
}

void Game::playHand() {
  auto bet = strat.bet();

  if (bet % 2 != 0) {
    cout << "Bet must be divisible by 2" << endl;
    return;
  }
  if (bet % rules.blackjackDenominator != 0) {
    cout << "Bet must be divisible by blackjack payout denominator ("
         << rules.blackjackDenominator << ")" << endl;
    return;
  }
  playerMoney -= bet;
  cout << "Player bet: " << bet << endl;

  // Dealer hand index 0 is the hole card (unknown to player).
  dealerHand << shoe.drawCard();
  dealerHand << shoe.drawCard();
  playerHand << shoe.drawCard();
  playerHand << shoe.drawCard();

  cout << "Dealer delt: " << dealerHand[1] << endl;
  cout << "Player delt: " << playerHand[0] << endl;
  cout << "Player delt: " << playerHand[1] << endl;
  cout << "Player score: " << playerHand.score() << endl;

  bool dealerBlackjack = false;

  // Check for dealer blackjack.
  if (dealerHand[1] == 10 && dealerHand[0] == 1) {
    cout << "Dealer had blackjack" << endl;
    dealerBlackjack = true;
  }

  // Check for dealer blackjack with insurance.
  if (dealerHand[1] == 1) {
    auto insuranceBet = 0;
    if (strat.takeInsurance()) {
      insuranceBet = bet / 2;
    }
    playerMoney -= insuranceBet;

    if (dealerHand[0] == 10) {
      cout << "Dealer had blackjack" << endl;
      dealerBlackjack = true;
      playerMoney += insuranceBet * 2;
    } else {
      cout << "Dealer did not have blackjack" << endl;
    }
  }

  bool playerBlackjack = false;

  // Check for player blackjack.
  if (playerHand == 21) {
    cout << "Player had blackjack" << endl;
    playerBlackjack = true;
    if (dealerBlackjack) {
      cout << "But so did the dealer, push" << endl;
    }
  }

  // Player does his plays.
  Strategy::playChoice choice;
  bool done = dealerBlackjack;
  while (playerHand < 21 && !done) {
    choice = strat.choosePlay();
    unsigned int card;
    switch (choice) {
      case Strategy::playChoice::Stand:
        cout << "Player stands" << endl;
        done = true;
        break;
      case Strategy::playChoice::Hit:
        cout << "Player hits" << endl;
        card = shoe.drawCard();
        cout << "Got a " << card << endl;
        playerHand << card;
        cout << "Player score: " << playerHand.score() << endl;
        break;
      case Strategy::playChoice::Double:
        if (playerHand.numCards() == 2) {
          cout << "Player doubles" << endl;
          card = shoe.drawCard();
          cout << "Got a " << card << endl;
          playerHand << card;
          cout << "Player score: " << playerHand.score() << endl;
          playerMoney -= bet;
          bet *= 2;
          done = true;
        } else {
          cout << "Can only double on first card" << endl;
        }
        break;
      case Strategy::playChoice::Split:
        if (playerHand.numCards() == 2 && playerHand[0] == playerHand[1]) {
          cout << "Player splits" << endl;
          // TODO
        } else {
          cout << "Can't split this hand" << endl;
        }
        break;
      case Strategy::playChoice::Surrender:
        if (rules.surrenderAllowed && playerHand.numCards() == 2) {
          cout << "Player surrenders" << endl;
          playerMoney += bet / 2;
          done = true;
        } else if (!rules.surrenderAllowed) {
          cout << "Surrender not allowed" << endl;
        } else {
          cout << "Can only surrender before hitting" << endl;
        }
        break;
    }
  }

  // Play out dealer hand.
  while (dealerHand < 17 ||
         (dealerHand == 17 && dealerHand.soft() && rules.hitOnSoft17)) {
    cout << "Dealer hits" << endl;
    auto card = shoe.drawCard();
    cout << "Got a " << card << endl;
    dealerHand << card;
    cout << "Dealer score: " << dealerHand.score() << endl;
  }

  cout << "Dealer final score: " << dealerHand.score() << endl;
  cout << "Player final score: " << playerHand.score() << endl;

  // Check who won.
  if (choice != Strategy::playChoice::Surrender) {
    if (!playerBlackjack) {
      if (playerHand > 21) {
        cout << "Player busted" << endl;
      } else if (dealerHand > 21) {
        cout << "Dealer busted" << endl;
        playerMoney += bet * 2;
      } else if (dealerHand > playerHand) {
        cout << "Dealer won" << endl;
      } else if (dealerHand == playerHand) {
        cout << "Push" << endl;
        playerMoney += bet;
      } else if (dealerHand < playerHand) {
        cout << "Player won" << endl;
        playerMoney += bet * 2;
      }
    } else {
      if (!dealerBlackjack) {
        playerMoney += bet;
        playerMoney +=
            bet * rules.blackjackNumerator / rules.blackjackDenominator;
      } else {
        playerMoney += bet;
      }
    }
  }

  cout << "Player money: " << playerMoney << endl << endl;

  playerHand.clear();
  dealerHand.clear();
}
