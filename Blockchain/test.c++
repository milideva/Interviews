#include "test.h"
#include "wallet.h"
#include <unistd.h>

#include <iostream>
#include <thread>

#include "transaction.h"

#include "concurrentQueue.h"
extern ConcurrentQueue <Transaction *> conQ;

static void produce (Wallet* aWall, chainAddr A, chainAddr B, string context, ConcurrentQueue<Transaction *>& conQ) {
  for (int i = 1; i< numTransactions; ++i) {
    cout << endl << "Wallet Sending transaction: amount: " << i << endl;
    Transaction* txn = aWall->createTransaction(A, B, i, context, BLOCKCHAIN_NAME);
    if (txn == nullptr) {
      cout << "Failed to create transaction from " << A << " to " << B << " amt:" << i << " " << context << endl;
      return;
    }
    txn->printTransaction();

    conQ.push(txn);
    sleep(3);
  }
}

#include "json/json.h"
#include <fstream>
#include <iostream>

void test_json (void) {
  
  Json::Value root;
  std::ifstream file("test.json");
  file >> root;
  std::cout << root;
}

void entity (void) {
  test_json();
  string nameBC = BLOCKCHAIN_NAME;
  Wallet *alice = new Wallet("Alice");
  alice->openAccount(nameBC, 50000);

  Wallet *bob = new Wallet("Bob");
  bob->openAccount(nameBC, 30000);

  Wallet *charlie = new Wallet("Charlie");
  charlie->openAccount(nameBC, 70000);

  chainAddr acctCharlie1 = charlie->getPublicAddr(1);
  chainAddr acctAlice1 = alice->getPublicAddr(1);

  produce(alice, acctAlice1, acctCharlie1, "from Alice to Bob", conQ); // produces a test transaction
}
