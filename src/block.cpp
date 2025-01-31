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
  std::string proof;

public:
  Block(long long index, time_t timestamp, std::vector<Transaction *> trxs,
        std::string proof) {
    this->index = index;
    this->timestamp = timestamp;
    this->trxs = trxs;
    this->proof = proof;
  }

  long long get_index() { return this->index; }

  time_t get_timestamp() { return this->timestamp; }

  std::vector<Transaction *> get_trxs() { return this->trxs; }

  std::string get_proof() { return this->proof; }
};