#pragma once

class Strategy {
 public:
  enum class playChoice { Hit, Stand, Double, Split, Surrender };

  int bet();
  bool takeInsurance();
  playChoice choosePlay();

 private:
};
