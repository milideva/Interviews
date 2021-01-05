#include "memPool.h"

MemPool::MemPool (void) {
}

MemPool::~MemPool (void) {

  while (!vTxn.empty()) {
    Transaction* txn = vTxn.back();
    vTxn.pop_back();

    hash_t txnHash = txn->calcHash();
    hash2txn.erase(txnHash);
  }
}

bool MemPool::addTransaction (Transaction* txn) {

  if (!txn) return false;

  hash_t txnHash = txn->calcHash();
  // Need to validate the hash with mempool's own hash function

  if (isTransactionInMemPool(txnHash)) {
    return false;
  }
  
  vTxn.push_back(txn);
  hash2txn[txnHash] = txn;

  return true;
}

bool MemPool::isTransactionInMemPool (hash_t txnHash) {
  if (hash2txn.find(txnHash) != hash2txn.end()) {
    return true;
  }
  return false;
}

Transaction* MemPool::minerPopTransaction (void) {
  if (vTxn.empty()) return nullptr;
  Transaction* txn = vTxn.back();
  vTxn.pop_back();

  hash_t txnHash = txn->calcHash();
  hash2txn.erase(txnHash);
  return txn;
}
