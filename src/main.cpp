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

  server.Post("/trxs/new", [uuid, blockchain](const httplib::Request &req,
                                              httplib::Response &res) {
    json response_json;
    response_json["node_uuid"] = uuid;

    if (req.body.empty()) {
      res.status = 400;
      response_json["message"] = "body can not be empty";
      res.set_content(response_json.dump(), "application/json");
      return;
    }

    json received_json = json::parse(req.body);

    if (!received_json.contains("sender")) {
      response_json["message"] = "sender can not be empty";
      res.status = 400;
      res.set_content(response_json.dump(), "application/json");
      return;
    }

    if (!received_json.contains("recipient")) {
      response_json["message"] = "recipient can not be empty";
      res.status = 400;
      res.set_content(response_json.dump(), "application/json");
      return;
    }

    if (!received_json.contains("amount")) {
      response_json["message"] = "amount can not be empty";
      res.status = 400;
      res.set_content(response_json.dump(), "application/json");
      return;
    }

    std::string sender = received_json.at("sender");
    std::string recipient = received_json.at("recipient");
    double amount = received_json.at("amount").get<double>();

    Transaction *trx =
        blockchain->new_trx(new Transaction(sender, recipient, amount));

    response_json["timestamp"] = std::time(0);

    res.status = 200;
    response_json["new_trx"] = trx->to_json();
    res.set_content(response_json.dump(), "application/json");
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