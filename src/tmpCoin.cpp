/** */
#include "block.cpp"

#ifndef __TRX_CLASS

#include "trx.cpp"

#endif

#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

class tmpCoin {
public:
  std::vector<Block *> chain;
  std::vector<Transaction *> current_trxs;

  /** */
  tmpCoin() {
    this->chain = std::vector<Block *>();
    this->current_trxs = std::vector<Transaction *>();
  }

  /** */
  void new_block() {
    auto blk = new Block(this->chain.size() + 1, std::time(0),
                         this->current_trxs, "proof");
  }

  /** */
  void new_trx(Transaction *trx) { this->current_trxs.push_back(trx); }

  /** */
  static void hash() {}

  /** */
  void last_block() {}
};