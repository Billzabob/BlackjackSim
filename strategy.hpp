#pragma once

class Strategy {
 public:
  enum class playChoice { Hit, Stand, Double, Split, Surrender };

  unsigned int bet() const;
  bool takeInsurance() const;
  playChoice choosePlay() const;
};
