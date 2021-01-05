#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#pragma once

#include <block.h>
#include "commonHeader.h"
#include "memPool.h"

#include "account.h"

class BlockChain {
  
private :
  vector <class Block *> vecChain;
  unordered_map <hash_t, class Block *> mapChain; // hash -> block
  size_t last;
  Block* gen; // genesis block
  string bcName; // BlockChain name
  MemPool *mempool;
  int version;
  coin_t reward;

  unordered_map <chainAddr, Account*> pk2acct;

  bool debitFromAccount (chainAddr from, uint64_t amount);
  bool creditIntoAccount (chainAddr to, uint64_t amount);
  void updateGlobalAccounts (Block* b);
  bool validateBlock (Block* b);

public:
  BlockChain (string name);

  void CreateGenesisBlock (int ver, size_t prevHash, size_t merkleHash, time_t nTime, coin_t reward);
  Block* findBlock (hash_t hash);
  Block* findBlock (unsigned int index);
  Block* getBlock (uint index);
  hash_t getLastBlockHash ();
  void mineBlock (Block* b);
  uint getBlockCount (void);
  coin_t getBlockReward (void);
  int getVersion (void);
  
  bool openAccount (chainAddr addr, uint64_t deposit);
  bool addBlock (Block* b);
};

uint getBlockCount (void);
uint getBlockCount (string nameBC);
hash_t getLastBlockHash (string nameBC);
coin_t getBlockReward (string nameBC);
bool openGlobalBlockChainAccount (string nameBC, chainAddr addr, uint64_t deposit);

bool addBlockToBlockChain (string nameBC, Block *);

string hashToString (hash_t hash);

extern unordered_map <string, class BlockChain *> str2BlockChainPtrMap;

// JSON queries
Json::Value getBlockCountToJSON (string nameBC);
Json::Value getBlockCountToJSON (void);

Json::Value getBlockToJSON (hash_t bHash);
Json::Value getBlockToJSON (uint index);

Json::Value getTransactionToJSON (uint blockIndex, uint txnIndex);

#endif
