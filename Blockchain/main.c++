#include <thread>

#include "blockchain.h"
#include "restServer.h"
#include "concurrentQueue.h"
#include "transaction.h"
#include "miner.h"

#include "commonProto.h"

#include "test.h"

ConcurrentQueue<Transaction *> conQ;

int main() {
  string nameBC = BLOCKCHAIN_NAME;
  BlockChain bc(nameBC);
  str2BlockChainPtrMap[nameBC] = &bc;

  thread protoThread(asyncProtoServer);

  Miner minerA("coinMiner");

  thread restServerThread(restServer, 0);
  thread minerThread(minerMainLoop, &bc, &minerA);
  createTestTxnProducerThreads();

  minerThread.join();
  restServerThread.join();
  protoThread.join();

  return 0;
}
