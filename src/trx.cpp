/** */
#include <iostream>

#ifndef __TRX_CLASS
#define __TRX_CLASS

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
};

#endif