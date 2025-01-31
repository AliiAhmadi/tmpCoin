/** */
#include "httplib.h"
#include "json.hpp"
#include "tmpCoin.cpp"
#include <uuid/uuid.h>

using json = nlohmann::json;

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

  auto blockchain = new tmpCoin{};

  server.Get("/mine", [](const httplib::Request &req, httplib::Response &res) {
    res.set_content("{\"message\": \"I will mine one block!\"}",
                    "application/json");
  });

  server.Get("/trxs/new", [](const httplib::Request &req,
                             httplib::Response &res) {
    res.set_content("{\"message\": \"A new trx added\"}", "application/json");
  });

  server.Get("/me",
             [uuid](const httplib::Request &req, httplib::Response &res) {
               res.set_content("{\"uuid\":" + uuid + "}", "application/json");
             });

  server.Get("/chain",
             [blockchain](const httplib::Request &req, httplib::Response &res) {
               struct chain {
                 std::vector<Block *> chain;
                 long long length;

                 json to_json() const {
                   json j;
                   for (auto blk : chain) {
                     j["chain"].push_back(blk->to_json());
                   }

                   j["length"] = this->length;

                   return j;
                 }
               };

               chain result = {
                 chain : blockchain->chain,
                 length : static_cast<long long>(blockchain->chain.size())
               };

               res.set_content(result.to_json().dump(), "application/json");
             });

  server.listen("0.0.0.0", 3000);

  return EXIT_SUCCESS;
}