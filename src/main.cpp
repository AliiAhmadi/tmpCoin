/** */
#include "httplib.h"
#include "tmpCoin.cpp"
#include <uuid/uuid.h>

std::string node_uuid() {
  uuid_t uuid;
  char uuidStr[37];

  uuid_generate_random(uuid);
  uuid_unparse(uuid, uuidStr);
  return std::string(uuidStr);
}

int main(void) {

  httplib::Server server;

  server.Get("/", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("Hello, World!", "text/plain");
  });

  std::string uuid = node_uuid();

  auto x = new tmpCoin{};
  auto trx = new Transaction("ali", "reza", 2.1);
  x->new_trx(trx);

  server.listen("0.0.0.0", 3000);

  return EXIT_SUCCESS;
}