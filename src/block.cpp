/** */
#include "trx.cpp"
#include <ctime>
#include <iostream>
#include <vector>

class Block {
private:
  time_t timestamp;
  long long index;
  std::vector<Transaction *> trxs;
  double proof;
  std::string prev_hash;

public:
  Block(long long index, time_t timestamp, std::vector<Transaction *> trxs,
        double proof, std::string previous_hash) {
    this->index = index;
    this->timestamp = timestamp;
    this->trxs = trxs;
    this->proof = proof;
    this->prev_hash = previous_hash;
  }

  long long get_index() { return this->index; }

  time_t get_timestamp() { return this->timestamp; }

  std::vector<Transaction *> get_trxs() { return this->trxs; }

  double get_proof() { return this->proof; }
};