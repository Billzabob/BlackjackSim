#include "strategy.hpp"

#include <iostream>
#include <string>

using namespace std;

int Strategy::bet() {
  cout << "Bet amount:" << endl;
  int bet;
  cin >> bet;
  return bet;
}

bool Strategy::takeInsurance() {
  cout << "Bet insurance?" << endl;
  bool bet;
  cin >> bet;
  return bet;
}

Strategy::playChoice Strategy::choosePlay() {
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
