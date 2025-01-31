/** */
#include "json.hpp"
#include <iostream>

#ifndef __TRX_CLASS
#define __TRX_CLASS

using json = nlohmann::json;

class Transaction {
public:
  std::string sender;
  std::string recipient;
  double amount;
  Transaction(std::string sender, std::string recipient, double amount) {
    this->sender = sender;
    this->recipient = recipient;
    this->amount = amount;
  }

  json to_json() const {
    json j;
    j["sender"] = this->sender;
    j["recipient"] = this->recipient;
    j["amount"] = this->amount;

    return j;
  }
};

#endif