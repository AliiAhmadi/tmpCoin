/** */
#include "crow.h"
#include "tmpCoin.cpp"

int main(void) {

  crow::SimpleApp app;

  auto x = new tmpCoin{};
  auto trx = new Transaction("ali", "reza", 2.1);
  x->new_trx(trx);

  // std::cout << x->new_block() << std::endl;

  return EXIT_SUCCESS;
}