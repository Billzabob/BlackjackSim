#include "game.hpp"

#include <iostream>

using namespace std;

Game::Game(Strategy& strat) : playerMoney(0), strat(strat), shoe(1) {}

void Game::play() {
  while (true) {
    playHand();
  }
}

void Game::playHand() {
  int bet = strat.bet();

  if (bet % 2 != 0) {
    cout << "Bet must be divisible by 2" << endl;
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

  bool dealerBlackjack = false;

  // Check for dealer blackjack.
  if (dealerHand[1] == 10 && dealerHand[0] == 1) {
    cout << "Dealer had blackjack" << endl;
    dealerBlackjack = true;
  }

  // Check for dealer blackjack with insurance.
  if (dealerHand[1] == 1) {
    int insuranceBet = 0;
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

  // Check for player blackjack.
  if (playerHand == 21) {
    cout << "Player had blackjack" << endl;
    if (dealerBlackjack) {
      cout << "But so did the dealer, push" << endl;
    } else {
      playerMoney += bet / 2;
    }
  }

  // Player does his plays.
  Strategy::playChoice choice;
  bool done = dealerBlackjack;
  while (playerHand < 21 && !done) {
    choice = strat.choosePlay();
    int card;
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
        cout << "Player doubles" << endl;
        card = shoe.drawCard();
        cout << "Got a " << card << endl;
        playerHand << card;
        cout << "Player score: " << playerHand.score() << endl;
        playerMoney -= bet;
        bet *= 2;
        done = true;
        break;
      case Strategy::playChoice::Split:
        cout << "Player splits" << endl;
        // TODO
        break;
      case Strategy::playChoice::Surrender:
        cout << "Player surrenders" << endl;
        playerMoney += bet / 2;
        done = true;
        break;
    }
  }

  // Check who won.
  while (dealerHand < 17) {
    cout << "Dealer hits" << endl;
    int card = shoe.drawCard();
    cout << "Got a " << card << endl;
    dealerHand << card;
    cout << "Dealer score: " << dealerHand.score() << endl;
  }

  cout << "Dealer final score: " << dealerHand.score() << endl;
  cout << "Player final score: " << playerHand.score() << endl;

  if (choice != Strategy::playChoice::Surrender) {
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
  }

  cout << "Player money: " << playerMoney << endl << endl;

  playerHand.clear();
  dealerHand.clear();
}
