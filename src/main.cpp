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

  auto blockchain = new tmpCoin{uuid};

  /**
   *
   */
  server.Get("/mine", [blockchain, uuid](const httplib::Request &req,
                                         httplib::Response &res) {
    auto last_blk = blockchain->last_block();
    auto last_proof = last_blk->get_proof();
    auto proof = blockchain->proof_of_work(last_proof);

    blockchain->new_trx(new Transaction("0", uuid, 50));
    std::string prev_hash = tmpCoin::hash(last_blk);
    auto new_blk = blockchain->new_block(prev_hash, proof);

    json response_json;
    response_json["message"] = "new block created";
    response_json["hash"] = tmpCoin::hash(new_blk);
    response_json["new_block"] = new_blk->to_json();
    response_json["timestamp"] = std::time(0);
    res.status = 200;

    res.set_content(response_json.dump(), "application/json");
  });

  /**
   * Create new Transaction.
   * This callback function just accept POST method and some required data from
   * client. if does not specify them will got 400 http status in response and
   * a human readable message for client to tell what data need to add to
   * request body.
   *
   * ## Request body should be in json format. if not some error will raise.
   * ## TODO: fix internal server error when request format something other that
   * json.
   *
   * This callback will create a new transaction and add it to mempool of this
   * node.
   * ## In this version we not send broadcast to other nodes to tell them this
   * new transaction.
   * ## I ignored that to avoid code complexity.
   *
   * Required request body must contain: {"sender", "recipient", "amount"}
   *
   * In response if all things works correctly client will got the created
   * transaction in json format in response body.
   */
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

  /**
   * Get information about this node.
   * Contain node_uuid
   *
   * body ofthis callback function need a improvement and should use json
   * instead of concatenate strings manualy.
   * ## Just accept GET http method for this path.
   */
  server.Get("/me",
             [uuid](const httplib::Request &req, httplib::Response &res) {
               res.set_content("{\"uuid\":" + uuid + "}", "application/json");
             });

  /** */
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