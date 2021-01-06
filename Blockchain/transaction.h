#ifndef TRANSACTION_H
#define TRANSACTION_H
#pragma once

#include "commonHeader.h"
#include "eckey.h"

class Transaction {
 
  string nameBlockChain;

public:
  // Everything in a transaction is public
  chainAddr fromAddr;
  chainAddr toAddr;
  uint64_t nValue;
  uint64_t nonce;
  ecdsaSig_t fromSig;
  string context;

  hash_t txnHash;

  Transaction (chainAddr fromAddr, chainAddr toAddr, uint64_t nValue, 
               uint64_t nonce, string context, string nameBC);
  void printTransaction(void);
  hash_t calcHash (void);
  bool setSig (ecdsaSig_t sig);
  bool verify (void);
  
  Json::Value getTransactionToJSON (void);
};

void createTransactionFromJSON (string contextStr, string fromAddrStr, string sStr, string rStr, 
                                int nValue, int nonce, string toAddrStr, string txnHashStr);

bool calcSHA256 (const char* input, unsigned long length, hash_t *md);

#endif
