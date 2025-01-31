#include "trx.cpp"
#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

class tmpCoin {
public:
  std::vector<int> chain;
  Transaction *current_trx;
  tmpCoin() {
    this->chain = std::vector<int>();
    this->current_trx = new Transaction();
  }
  void new_block() {
    // this->chain
  }
};