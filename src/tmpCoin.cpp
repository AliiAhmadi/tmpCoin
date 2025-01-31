/** */
#include "block.cpp"
#include "trx.cpp"
#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

class tmpCoin {
public:
  std::vector<Block> chain;
  Transaction *current_trx;

  /** */
  tmpCoin() {
    this->chain = std::vector<Block>();
    this->current_trx = new Transaction();
  }

  /** */
  void new_block() {}

  /** */
  void new_trx() {}

  /** */
  void hash() {}

  /** */
  void last_block() {}
};