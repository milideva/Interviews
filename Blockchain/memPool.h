#ifndef MEMPOOL_H
#define MEMPOOL_H
#pragma once

#include "commonHeader.h"
#include "transaction.h"

class MemPool {
  private :
  vector <Transaction *> vTxn;
  unordered_map <hash_t, Transaction *> hash2txn;

  public:
  MemPool ();
  ~MemPool ();

  bool addTransaction (Transaction* txn);
  bool isTransactionInMemPool (hash_t txnHash);

  Transaction* minerPopTransaction (void);
};

#endif
