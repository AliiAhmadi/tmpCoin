/** */
#include "json.hpp"
#include "trx.cpp"
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

#ifndef __CLASS_BLOCK
#define __CLASS_BLOCK

using json = nlohmann::json;

class Block {
private:
  time_t timestamp;
  long long index;
  std::vector<Transaction *> trxs;
  long long proof;
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

  long long get_proof() { return this->proof; }

  std::string get_prev_hash() { return this->prev_hash; }

  std::string serialize() const {
    std::ostringstream oss;
    oss << this->timestamp << "|" << this->index << "|";

    for (auto i : this->trxs) {
      oss << &i << "|";
    }

    oss << this->proof << "|" << this->prev_hash;

    return oss.str();
  }

  json to_json() const {
    json j;
    j["index"] = this->index;
    j["timestamp"] = this->timestamp;

    for (auto trx : this->trxs) {
      j["trxs"].push_back(trx->to_json());
    }

    j["proof"] = this->proof;
    j["prev_hash"] = this->prev_hash;

    return j;
  }
};

#endif
