#include "account.h"
#include "blockchain.h"

Account::Account (string blockChainNameIn, chainAddr publicAddrIn, uint64_t balanceIn, bool isWalletAccountIn) {
  blockChainName = blockChainNameIn;
  publicAddr = publicAddrIn;
  balance = balanceIn;
  nonce = 0;
  isWalletAccount = isWalletAccountIn;
  cout << "Account::Account publicAddr:" << publicAddr << " isWalletAccount:" << isWalletAccount << " acct:" << this << endl;
  if (isWalletAccount == true) {
    // Sync wallet's new account globally on Blockchain
    openGlobalBlockChainAccount(BLOCKCHAIN_NAME, publicAddrIn, balanceIn);
  }
}

uint64_t Account::getBalance (void) {
  return balance;
}

uint64_t Account::getNonce (void) {
  return nonce;
}

void Account::printAccount (void) {
  cout << "$$$$$$ ";
  if (isWalletAccount) {
    cout << "Wallet Account";
  } else {
    cout << "OnChain Global Account:";
  }
  cout << " addr:" << publicAddr << " balance:" << dec << balance << " nonce:" << nonce << endl;
}

bool Account::debitFromAccount (uint64_t debitAmount) {
  if (debitAmount > balance) {
    return false;
  }
  nonce++;
  balance -= debitAmount;
  printAccount();
  return true;
}

bool Account::creditIntoAccount (uint64_t addAmount) {
  nonce++;
  balance += addAmount;
  printAccount();
  return true;
}
