#include "block.h"
#include "blockchain.h"
#include "miner.h"

#include "concurrentQueue.h"

Miner::Miner (string nameIn) {
  name = nameIn;
  myWallet = new Wallet(name);
  if (myWallet) 
    myWallet->openAccount(BLOCKCHAIN_NAME, 0);
  currBlock = nullptr;
}

string Miner::getName (void) {
  return name;
}

bool Miner::validateNonce (Transaction *txn) {
  if (txn->fromAddr != 0) {

    if (fromAddr2Nonce.find(txn->fromAddr) != fromAddr2Nonce.end()) {
      uint64_t minerNonce = fromAddr2Nonce[txn->fromAddr];
      if (minerNonce + 1 == txn->nonce) {
        fromAddr2Nonce[txn->fromAddr]++;
      } else {
        cout << "Miner nonce:" << minerNonce + 1 << " mismatched txn from Nonce:" << txn->nonce << endl;
        return false;
      }

    } else {
      fromAddr2Nonce[txn->fromAddr] = txn->nonce;
      cout << "Miner added fromAddr:" << txn->fromAddr << " Nonce:" << txn->nonce << endl;
    }
  }

  return true;
}

bool Miner::validateTransaction (Transaction *txn) {
  bool ret = txn->verify();
  if (!ret) {
    cout << "Miner transaction's verification failed" << endl;
    return ret;
  }
  if (txn->fromAddr != 0) {
    if (validateNonce(txn) == false) {
      cout << "Miner's nonce verification failed" << endl;
      return false;
    }
  }
  return true;
}

bool Miner::addTransaction (Transaction *txn) {
  if (validateTransaction(txn) == false) {
    return false;
  }
  // Curreently adding to miner's queue and during mining copying all to new curr block
  vTxn.push_back(txn);
  return true;
}

char *getUTCTime (void) { 
  time_t now = time(0);
  char* dt = ctime(&now); // local date and time, this is not from malloc/dont free it.
  tm *gmtm = gmtime(&now);
  dt = asctime(gmtm);
  return dt;
}

void Miner::createNewBlock (int ver, hash_t prevBlockHash, hash_t merkleHash, time_t nTime, coin_t reward) {
  if (currBlock) {
    delete currBlock;
  }
  char *timePtr = getUTCTime();
  currBlock = new Block(ver, prevBlockHash, merkleHash, nTime, reward, name + " mining this block at UTC: " + timePtr);
}

void Miner::clearCurrBlock (void) {
  // Assumes that block is passed to BlockChain
  // If this assumption changes, delete currBlock here
  currBlock = nullptr;
}

void Miner::clearVTxn (void) {
  vTxn.clear();
}

void Miner::copyTransactionsToBlock (void) {
  Block *b = currBlock;
  if (!b) 
    return;
  b->vTxn = vTxn;
}

void Miner::mineBlock (void) {
  Block *b = currBlock;
  if (!b) 
    return;

  // Copy all transactions from miner's queue to block's queue
  copyTransactionsToBlock();  

  b->proofOfWork();

  addBlockToBlockChain(BLOCKCHAIN_NAME, b);

  clearCurrBlock();
  clearVTxn();
}

void Miner::createCoinbaseTransaction (coin_t reward) {
  chainAddr from = 0;
  chainAddr to = myWallet->getPublicAddr(1);
  Transaction *coinBase = myWallet->createTransaction(from, to, reward, 
                                                      name + " CoinBase Transaction", BLOCKCHAIN_NAME);
  coinBase->printTransaction();
  vTxn.push_back(coinBase);
  reverse(vTxn.begin(), vTxn.end());
}

void doProofOfWork (BlockChain *bc, Miner *miner) {

  int ver = bc->getVersion();
  hash_t lastBlockHash = bc->getLastBlockHash();
  hash_t merkleHash = 0;
  coin_t reward = bc->getBlockReward();
  time_t tm = 0;

  // First Create a new block to mine
  miner->createNewBlock(ver, lastBlockHash, merkleHash, tm, reward);

  // Add coinbase transaction to reward self
  miner->createCoinbaseTransaction(reward);

  // Start mining
  miner->mineBlock();
}


extern ConcurrentQueue <Transaction *> conQ;

void minerMainLoop (BlockChain *bc, Miner *miner) {
  uint i = 0;
  while (1) {
    Transaction *txn = conQ.pop();
    if (txn) {
      miner->addTransaction(txn);
      cout << "Miner " << miner->getName() << " received transaction -> " << endl;
      txn->printTransaction();
    }
    i++;
    if ((i % 3) == 0)
      doProofOfWork(bc, miner);
    sleep(2);  
  }
}
