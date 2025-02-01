/** */
#include "block.cpp"
#include "trx.cpp"
#include <sstream>

#include <iomanip>
#include <iostream>
#include <vector>

// #include <bits/stdc++.h>

#ifndef __CLASS_TMPCOIN
#define __CLASS_TMPCOIN

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
  Block *new_block(const std::string prev_hash = "", long long proof = 0) {
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
  Transaction *new_trx(Transaction *trx) {
    this->current_trxs.push_back(trx);
    return trx;
  }

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

  bool valid_proof(long long last_proof, long long proof) {
    std::string now_proof =
        this->proof_to_string(last_proof) + proof_to_string(proof);

    std::hash<std::string> hasher;
    size_t hash = hasher(now_proof);
    std::string hash_string = tmpCoin::to_hex(hash);

    return hash_string.substr(14, 2) == "ff";
  }

  long long proof_of_work(long long last_proof) {
    long long proof = 0;

    while (!this->valid_proof(last_proof, proof))
      proof++;

    return proof;
  }

private:
  static std::string to_hex(size_t hash_value) {
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash_value;
    return ss.str();
  }

  std::string proof_to_string(long long proof) {
    std::ostringstream oss;
    oss << proof;
    return oss.str();
  }
};

#endif