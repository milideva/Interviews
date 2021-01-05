#include "blockchain.h"
#include "restServer.h"
#include <thread>

#include "test.h"

#include "concurrentQueue.h"
#include "transaction.h"
#include "miner.h"

ConcurrentQueue<Transaction *> conQ;

int main() {
  string nameBC = BLOCKCHAIN_NAME;
  BlockChain bc(nameBC);
  str2BlockChainPtrMap[nameBC] = &bc;
  Miner minerA("coinMiner");

  thread t1(restServer, 0);
  thread txnProducerThread(entity);

  thread minerThread(minerMainLoop, &bc, &minerA);

  minerThread.join();
  txnProducerThread.join();
  t1.join();

  return 0;
}
