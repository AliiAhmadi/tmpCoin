/** */
#include "block.cpp"
#include "trx.cpp"
#include <sstream>

#include <iomanip>
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
  Block *new_block(const std::string prev_hash = "", double proof = 0.) {
    Block *blk = new Block(
        this->chain.size() + 1, std::time(0), this->current_trxs, proof,
        (prev_hash == "" ? tmpCoin::hash(this->chain[this->chain.size() - 1])
                         : prev_hash));

    // Clear all mempool.
    this->current_trxs.clear();
    this->chain.push_back(blk);

    return blk;
  }

  /** */
  void new_trx(Transaction *trx) { this->current_trxs.push_back(trx); }

  /** */
  static std::string hash(Block *blk) {
    const std::string serializedBlock = blk->serialize();
    std::hash<std::string> hasher;

    size_t hash = hasher(serializedBlock);
    std::string hash_string = tmpCoin::to_hex(hash);

    return hash_string;
  }

  /** */
  Block *last_block() {
    if (this->chain.size() == 0)
      return NULL;

    return this->chain[this->chain.size() - 1];
  }

  void proof_of_work() {}

private:
  static std::string to_hex(size_t hash_value) {
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash_value;
    return ss.str();
  }
};