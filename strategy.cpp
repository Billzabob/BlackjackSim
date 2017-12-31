#include "strategy.hpp"

#include <iostream>
#include <string>

using namespace std;

unsigned int Strategy::bet() const {
  cout << "Bet amount:" << endl;
  unsigned int bet;
  cin >> bet;
  return bet;
}

bool Strategy::takeInsurance() const {
  cout << "Bet insurance?" << endl;
  bool bet;
  cin >> bet;
  return bet;
}

Strategy::playChoice Strategy::choosePlay() const {
  cout << "Play choice:" << endl;
  string playString;
  cin >> playString;

  playChoice play;

  if (playString == "hit") {
    play = playChoice::Hit;
  } else if (playString == "stand") {
    play = playChoice::Stand;
  } else if (playString == "double") {
    play = playChoice::Double;
  } else if (playString == "split") {
    play = playChoice::Split;
  } else if (playString == "surrender") {
    play = playChoice::Surrender;
  }
  return play;
}
