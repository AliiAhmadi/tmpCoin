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
  std::string uuid = node_uuid();

  auto x = new tmpCoin{};

  server.Get("/mine", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("{\"message\": \"I will mine one block!\"}",
                    "application/json");
  });

  server.Get("/trx/new", [](const httplib::Request &req,
                            httplib::Response &res) {
    res.set_content("{\"message\": \"A new trx added\"}", "application/json");
  });

  server.Get("/me",
             [uuid](const httplib::Request &req, httplib::Response &res) {
               res.set_content("{\"uuid\":" + uuid + "}", "application/json");
             });

  server.listen("0.0.0.0", 3000);

  return EXIT_SUCCESS;
}