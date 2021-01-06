
#include "wallet.h"
#include "transaction.h"

Wallet::Wallet (string str) {
  name = str;
}

Wallet::~Wallet () {
  for (auto [addr, ec] : pk2eckey) {
    delete ec;
  }
  for (auto [addr, acct] : pk2acct) {
    delete acct;
  }
}

bool Wallet::openAccount (string blockChainName, uint64_t deposit) {
  ECKey *eckey = new ECKey;
  if (!eckey) {
    cout << "ECKey creation failed for " << name << endl;
    return false;
  }
  chainAddr pubKey = eckey->getPublicKey();

  id.push_back(pubKey);
  pk2eckey[pubKey] = eckey;

  bool isWalletAccount = true;
  Account *acct = new Account(blockChainName, pubKey, deposit, isWalletAccount);
  if (!acct) {
    cout << " Account creation failed for " << name << endl;
    id.pop_back();
    pk2eckey.erase(pubKey);
    return false;
  }
  pk2acct[pubKey] = acct;
  cout << "Wallet " << name << " opened account:" << pubKey << " acct:" << acct << endl;
  eckey->printPublicKey();
  cout << " balance:" << dec << deposit << endl;
  return true;
}

chainAddr Wallet::getPublicAddr (uint index) {
  if (index > id.size()) {
    return nullptr;
  }
  return id[index - 1];
}

Transaction* Wallet::createTransaction (chainAddr from, chainAddr to, uint64_t amount, 
                                        string context, string nameBC) {
  bool coinBase = false;
  uint64_t nonce = 0;
  Account *fromAcct = nullptr;

  if (from == 0) {
    coinBase = true;
  }
  if (coinBase == false) {
    if (pk2eckey.find(from) == pk2eckey.end()) {
      cout << "from: " << from << " not my address : " << name << endl;
      return nullptr;
    }
    
    if (pk2acct.find(from) == pk2acct.end()) {
      cout << "from: " << from << " has no account : " << name << endl;
      return nullptr;
    }
    
    fromAcct = pk2acct[from];
    uint64_t balance = fromAcct->getBalance();
    if (amount > balance) {
      cout << "from: " << from << " amount:" << amount << " insufficient balance : " << balance << endl;
      return nullptr;
    }
  
    nonce = fromAcct->getNonce();
  }
  
  Transaction* txn = new Transaction (from, to, amount, nonce, context, nameBC);
  
  if (!txn) {
    cout << "sendCoin create transaction failed" << endl;
    return nullptr;
  }
  
  hash_t txnHash = txn->calcHash();
  if (txnHash == 0) {
    // TO DO hash can be 0 - a valid value !
    cout << "txn calcHash failed" << endl;
    delete txn;
    return nullptr;
  }
  
  ECKey* eckey;
  if (coinBase) {
    cout << "Wallet : CoinBase signing with toAddress" << endl;
    eckey = getECKey(to);
  } else {
    eckey = getECKey(from);
  }

  ecdsaSig_t sign = eckey->sign((const unsigned char *) &txnHash, sizeof txnHash);

  cout << "txnHash:" << txnHash << " Sign: " << sign << endl;

  if (sign == NULL) {
    cout << "eckey sign failed" << endl;
    delete txn;
    return nullptr;
  }
  cout << name << " sending from account: " << from << " to account: " << to << " amount: " << dec << amount << " nonce:" << nonce << " context: " << context << endl;
  txn->setSig(sign);

/*
  if (pk2acct.find(to) == pk2acct.end()) {
      cout << "to: " << from << " has no account : " << name << endl;
      delete txn;
      return nullptr;
  }
*/
  if (fromAcct && fromAcct->debitFromAccount(amount) == false) {
    cout << "Wallet::createTransaction() : fromAcct->debitFromAccount failed " << endl;
    delete txn;
    return nullptr;
  }

/*
  Account* toAcct = pk2acct[to];
  toAcct->creditIntoAccount(amount);
*/
  return txn;
}

ECKey* Wallet::getECKey (chainAddr pubKey) {
  return pk2eckey[pubKey];
}

