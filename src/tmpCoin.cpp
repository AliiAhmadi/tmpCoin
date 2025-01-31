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

    // Create the first block of chain.
    this->new_block("0");
  }

  /** */
  void new_block(const std::string prev_hash = "", double proof = 0.) {
    Block *blk = new Block(
        this->chain.size() + 1, std::time(0), this->current_trxs, proof,
        (prev_hash == "" ? tmpCoin::hash(this->chain[this->chain.size() - 1])
                         : prev_hash));

    // Clear all mempool.
    this->current_trxs.clear();
    this->chain.push_back(blk);
  }

  /** */
  void new_trx(Transaction *trx) { this->current_trxs.push_back(trx); }

  /** */
  static std::string hash(Block *blk) {}

  /** */
  void last_block() {}
};