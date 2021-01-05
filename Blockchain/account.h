
#ifndef ACCOUNT_H
#define ACCOUNT_H
#pragma once

#include "commonHeader.h"
#include "eckey.h"

class Account {
 private:
  chainAddr publicAddr;
  uint64_t balance;
  uint64_t nonce;
  string blockChainName;
  bool isWalletAccount;
 public:
  Account (string blockChainName, chainAddr publicAddrIn, uint64_t deposit, bool isWalletAccountIn);
  uint64_t getBalance (void);
  uint64_t getNonce (void);
  bool debitFromAccount (uint64_t debitAmount);
  bool creditIntoAccount (uint64_t addAmount);
  void printAccount (void);
};

#endif
