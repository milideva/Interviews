#ifndef MINER_H
#define MINER_H
#pragma once

#include "commonHeader.h"
#include "eckey.h"
#include "wallet.h"

class Miner {

  Wallet *myWallet;
  string name;
  vector <Transaction *> vTxn;
  Block* currBlock;
  unordered_map <chainAddr, uint64_t> fromAddr2Nonce; 
  void clearCurrBlock (void);
  void clearVTxn (void);
  void copyTransactionsToBlock (void);

 public:
  Miner(string name);
  bool addTransaction (Transaction *Txn);
  string getName (void);
  void createNewBlock (int ver, hash_t prevBlockHash, hash_t merkleHash, time_t nTime, coin_t reward);
  void mineBlock (void);
  void createCoinbaseTransaction (coin_t reward);

  bool validateNonce (Transaction *txn);
  bool validateTransaction (Transaction *txn);
};

void minerMainLoop (BlockChain* bc, Miner* miner);

#endif
