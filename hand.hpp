#pragma once

#include <cstddef>  // size_t
#include <vector>

class Hand {
 public:
  unsigned int score() const;
  void clear();
  bool soft() const;
  unsigned int numCards() const;
  void operator<<(unsigned int card);
  unsigned int operator[](size_t i) const;
  bool operator==(unsigned int score) const;
  bool operator<(unsigned int score) const;
  bool operator>(unsigned int score) const;
  bool operator==(const Hand& hand) const;
  bool operator<(const Hand& hand) const;
  bool operator>(const Hand& hand) const;

 private:
  std::vector<unsigned int> hand;
};
