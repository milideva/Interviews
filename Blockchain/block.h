#ifndef BLOCK_H
#define BLOCK_H
#pragma once

#include "commonHeader.h"
#include "transaction.h"

class Block {
  struct BlockHeader_ {
    int32_t nVersion; 
    hash_t hashPrevBlock; // hash of last BlockHeader in BlockChain
    hash_t hashTransactionsRoot; //merkle root of transactions
    uint32_t nTime; // timestamp
    uint32_t nBits; // target difficulty
    uint32_t nNonce; 
  };
  BlockHeader_ blockHdr;
  hash_t hash; // strictly speaking not required, just an optimization to save cpu cycles

  void setHashPrevBlock (hash_t hash);  

 public :
  string dataPayload;
  vector <Transaction *> vTxn;

  Block () { };
  Block (int ver, hash_t lastHash, hash_t merkleHash, time_t nTime, coin_t reward, string dataPayloadIn);

  uint32_t getDifficulty (void);
  hash_t getBlockHash (void);
  uint32_t getNonce (void);
  void setNonce (uint32_t nonce);
  void setTime (uint32_t time);
  hash_t calcHash (void);
  bool calcSHA256 (const char* input, unsigned long length, hash_t *md);
  void printBlock (void);
  string getDataPayload ();
  void setDataPayload (string str);
  void calcHashTransactionsRoot (void); // Hash of transactions' hashes
  void proofOfWork (void);

  Json::Value getBlockToJSON (void);

  friend class BlockChain;  
};

#endif
