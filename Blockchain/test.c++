#include <unistd.h>
#include <iostream>
#include <thread>
#include "json/json.h"

#include "test.h"
#include "wallet.h"
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
    //txn->printTransaction();
    conQ.push(txn);
    sleep(2);
  }
}

static string nameBC = BLOCKCHAIN_NAME;
static Wallet *alice;
static Wallet *bob;
static Wallet *charlie;
chainAddr acctAlice1, acctBob1, acctCharlie1;

void txnProducerThreadA2B (void) {
  produce(alice, acctAlice1, acctBob1, "from Alice to Bob", conQ); 
}

void txnProducerThreadB2C (void) {
  produce(bob, acctBob1, acctCharlie1, "from Bob to Charlie", conQ);
}

void txnProducerThreadC2A (void) {
  produce(charlie, acctCharlie1, acctAlice1, "from Charlie to Alice", conQ);
}

void testTxnJson (void) {
    cout << endl << "=========== Creating JSON Test transaction ============" << endl;
    Transaction* txn = bob->createTransaction(acctBob1, acctAlice1, 10, "@@@@@@ JSON TEST @@@@@@", BLOCKCHAIN_NAME);
    if (txn == nullptr) {
      return;
    }
    txn->printTransaction();
    Json::Value root = txn->getTransactionToJSON();

    Json::StreamWriterBuilder builder;
    string message = Json::writeString(builder, root);
    cout << message << endl;
}

void createTestTxnProducerThreads (void) {

  alice = new Wallet("Alice");
  alice->openAccount(nameBC, 50000);

  bob = new Wallet("Bob");
  bob->openAccount(nameBC, 30000);

  charlie = new Wallet("Charlie");
  charlie->openAccount(nameBC, 70000);

  acctAlice1 = alice->getPublicAddr(1);
  acctBob1 = bob->getPublicAddr(1);
  acctCharlie1 = charlie->getPublicAddr(1);

  testTxnJson();

  thread threadA2B(txnProducerThreadA2B);

  thread threadB2C(txnProducerThreadB2C);
  thread threadC2A(txnProducerThreadC2A);

  threadA2B.join();
  threadB2C.join();
  threadC2A.join();
}
