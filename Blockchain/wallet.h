
#ifndef WALLET_H
#define WALLET_H
#pragma once

#include "commonHeader.h"
#include "account.h"
#include "transaction.h"

class Wallet {
 private:
  vector <chainAddr> id;
  unordered_map <chainAddr, ECKey*> pk2eckey;
  unordered_map <chainAddr, Account*> pk2acct;
  ECKey* getECKey (chainAddr pubKey);

 public:
  Wallet (string name);
  ~Wallet ();
  string name;
  bool openAccount (string blockChainName, uint64_t deposit);
  Transaction* createTransaction (chainAddr from, chainAddr to, uint64_t amount, 
                                  string context, string nameBC);  
  chainAddr getPublicAddr (uint index); // 1 based account number
};

#endif
