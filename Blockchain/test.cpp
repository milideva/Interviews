#include "test.h"
#include "wallet.h"
#include <unistd.h>

#include <iostream>
#include <thread>

#include "json/json.h"
#include <fstream>
#include <iostream>

void test_json (void) {
  Json::Value root;
  std::ifstream file("test.json");
  file >> root;
  std::cout << root;
}

#include "transaction.h"
#include "concurrentQueue.h"

extern ConcurrentQueue <Transaction *> conQ;

static void produce (Wallet* aWall, chainAddr A, chainAddr B, string context, 
                     ConcurrentQueue<Transaction *>& conQ) {
  for (int i = 1; i< numTransactions; ++i) {
    cout << endl << "Wallet Sending transaction: amount: " << i << endl;
    Transaction* txn = aWall->createTransaction(A, B, i, context, BLOCKCHAIN_NAME);
    if (txn == nullptr) {
      cout << "Failed to create transaction from " << A << " to " << B << " amt:" << i << " " << context << endl;
      return;
    }
    //txn->printTransaction();

    conQ.push(txn);
    sleep(2);
  }
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

  chainAddr acctAlice1 = alice->getPublicAddr(1);
  chainAddr acctBob1 = bob->getPublicAddr(1);
  chainAddr acctCharlie1 = charlie->getPublicAddr(1);

  // produces test transactions
  produce(alice, acctAlice1, acctBob1, "from Alice to Bob", conQ); 
  produce(bob, acctBob1, acctCharlie1, "from Bob to Charlie", conQ);
  produce(charlie, acctCharlie1, acctAlice1, "from Charlie to Alice", conQ);
}

int main () {

  return 0;
}
