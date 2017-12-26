#pragma once

#include <vector>

class Hand {
 public:
  int score() const;
  void clear();
  void operator<<(int card);
  int operator[](int i) const;
  bool operator==(int score) const;
  bool operator<(int score) const;
  bool operator>(int score) const;
  bool operator==(const Hand& hand) const;
  bool operator<(const Hand& hand) const;
  bool operator>(const Hand& hand) const;

 private:
  std::vector<int> hand;
};
