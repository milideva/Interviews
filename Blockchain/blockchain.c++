
#include "block.h"
#include "blockchain.h"

unordered_map <string, class BlockChain *> str2BlockChainPtrMap;

BlockChain::BlockChain (string bcNameIn) {
  last = 0;
  bcName = bcNameIn;
  time_t nTime = 1231006505;
  version = 1;
  reward = 100 * COIN;
  CreateGenesisBlock(version, 0, 0, nTime, reward);
  cout << "Creating the Genesis block now " << endl ;
  
  mempool = new MemPool();

  mineBlock(gen);
  cout << "Created the Genesis block " << endl ;
}

int BlockChain::getVersion (void) {
  return version;
}

void BlockChain::updateGlobalAccounts (Block* b) {
  for (int i = 0; i < b->vTxn.size(); i++) {
    Transaction* txn = b->vTxn[i];
    if (!txn)
      continue;
    chainAddr from = txn->fromAddr;
    chainAddr to = txn->toAddr;
    uint64_t amount = txn->nValue;
    Account *acct;
    hash_t pkHash;
    bool ret;
    if (from) {
      pkHash = getPkHash(from);
      acct = pk2acct[pkHash];
      if (acct) {
        cout << "Global account debit " << amount << " from:" << from << endl;
        ret = acct->debitFromAccount(amount);
      } else {
        cout << "Global account NOT FOUND for debit " << amount << " from:" << from << endl;
      }
      if (ret) {
        pkHash = getPkHash(to);
        acct = pk2acct[pkHash];
        if (acct) {
          cout << "Global account credit " << amount << " To:" << to << endl;
          acct->creditIntoAccount(amount);
        } else {
          cout << "Global account NOT FOUND for debit " << amount << " to:" << to << endl;
        }
      }
    } else {
      // Coinbase transaction
      pkHash = getPkHash(to);
      acct = pk2acct[pkHash];
      if (acct) {
        cout << "Global account credit COINBASE transaction " << dec << amount << " To:" << to << endl;
        acct->creditIntoAccount(amount);
      } else {
        cout << "Global account NOT FOUND credit COINBASE transaction " << dec << amount << " To:" << to << endl;
      }

    }
  }
}

bool BlockChain::validateBlock (Block* b) {
  if (!b) return false;
  // Many a validations are required
  // We will do some most basic ones.

  // Check for matching proposed block's prevBlock hash with blockchain's last block's hash
  hash_t chainLastHash = getLastBlockHash();
  hash_t blockLastHash = b->blockHdr.hashPrevBlock;
  if (chainLastHash != blockLastHash) {
    cout << "==================Mismatched hashes chainLastHash:" << chainLastHash << " blockLastHash:" << blockLastHash << endl;
    return false;
  }

  // Verify proposed block's hash
  hash_t currHash = b->getBlockHash();
  hash_t calcHash = b->calcHash();
  if (currHash != calcHash) {
    cout << "validateBlock failed block Hash:0x" << hex << currHash << " calcHash:0x" << calcHash << endl;
    return false;
  }
  // Validate transactions
  // Validate nonce
  // This is similar to code implemented in Miner::validateTransaction

  cout << "BlockChain validateBlock() SUCCESS block Hash:0x" << hex << currHash << " calcHash:0x" << calcHash << endl;
  return true;
}

bool BlockChain::addBlock (Block* b) {

  if (!b) return false;

  cout << "BlockChain:" << bcName << " Adding block# " << last << endl;
  b->printBlock();

  // Validate block
  if (validateBlock(b) == false) {
    cout << "BlockChain:" << bcName << " Failed block validation " << last << endl;
    return false;
  }

  // Update Global Account for each transaction
  updateGlobalAccounts(b);
  vecChain.push_back(b);
  mapChain[b->getBlockHash()] = b;
  last++;
  return true;
}

void BlockChain::CreateGenesisBlock (int ver, size_t prevHash, size_t merkleHash, time_t nTime, coin_t reward) {
  gen = new Block(ver, 0, 0, nTime, reward, "This is the Genesis block");
}

Block* BlockChain::findBlock (hash_t hash) {
  if (mapChain.find(hash) != mapChain.end()) {
    return mapChain[hash];
  }
  return nullptr;
}

Block* BlockChain::findBlock (unsigned int index) {
  if (index >= vecChain.size()) return nullptr;
  return vecChain[index];
}

hash_t BlockChain::getLastBlockHash () {
  if (!last) return 0;
  Block* b = vecChain[last-1];
  if (!b) return 0;
  return b->getBlockHash();
}

void BlockChain::mineBlock (Block* b) {
  if (!b) 
    return;
 
  b->setHashPrevBlock(getLastBlockHash());
  b->proofOfWork();

  addBlock(b);
}

// 0-based index
Block* BlockChain::getBlock (uint index) {
  if (index >= vecChain.size()) return nullptr;
  Block* b = vecChain[index];
  return b;
}

uint BlockChain::getBlockCount (void) {
  return vecChain.size();
}

uint getBlockCount (string nameBC) {
  class BlockChain *bcPtr;
  uint cnt = 0;
  if (str2BlockChainPtrMap.find(nameBC) != str2BlockChainPtrMap.end()) {
    bcPtr = str2BlockChainPtrMap[nameBC];
    cnt = bcPtr->getBlockCount();
  } 
  return cnt;
}

uint getBlockCount (void) {
  return getBlockCount(BLOCKCHAIN_NAME);
}
hash_t getLastBlockHash (string nameBC) {
  class BlockChain *bcPtr;
  hash_t lastBlockHash = 0;
  if (str2BlockChainPtrMap.find(nameBC) != str2BlockChainPtrMap.end()) {
    bcPtr = str2BlockChainPtrMap[nameBC];
    lastBlockHash = bcPtr->getLastBlockHash();
  }

  return lastBlockHash;
}

// Mining reward halves every HALVING_NUM_BLOCKS blocks.
coin_t BlockChain::getBlockReward (void) {
  if (getBlockCount() % HALVING_NUM_BLOCKS == 0) 
    reward = reward >> 2;
  return reward;
}

coin_t getBlockReward (string nameBC) {
  coin_t reward = 0;
  class BlockChain *bcPtr;

  if (str2BlockChainPtrMap.find(nameBC) != str2BlockChainPtrMap.end()) {
    bcPtr = str2BlockChainPtrMap[nameBC];
    reward = bcPtr->getBlockReward();
  }
  return reward;
}

bool BlockChain::openAccount (chainAddr newAddr, uint64_t deposit) {

  hash_t pkHash = getPkHash(newAddr);

  if (pk2acct.find(pkHash) != pk2acct.end()) {
    cout << "BlockChain: account:" << newAddr << " already exists!" << endl;
    return false;
  }
  bool isWalletAccount = false;
  Account *acct = new Account(bcName, newAddr, deposit, isWalletAccount);
  pk2acct[pkHash] = acct;
  cout << "######## On " << bcName << " : opened account for pubAddr:" << newAddr << " balance:" << deposit << " acct:0x" << acct << endl;
  return true;
}

bool openGlobalBlockChainAccount (string nameBC, chainAddr addr, uint64_t deposit) {
  class BlockChain *bcPtr;
  if (str2BlockChainPtrMap.find(nameBC) == str2BlockChainPtrMap.end()) {
    return false;
  }
  
  bcPtr = str2BlockChainPtrMap[nameBC];
  return bcPtr->openAccount(addr, deposit);
}

bool addBlockToBlockChain (string nameBC, Block *block) {
  class BlockChain *bcPtr;
  if (!block) 
    return false;

  if (str2BlockChainPtrMap.find(nameBC) == str2BlockChainPtrMap.end()) {
    return false;
  }
  
  bcPtr = str2BlockChainPtrMap[nameBC];
  return bcPtr->addBlock(block);
}

///////////////////// JSON queries /////////////////////

Json::Value getBlockCountToJSON (string nameBC) {
  uint cnt = getBlockCount(nameBC);
  
  Json::Value root;
  root["blockCount"] = cnt;

  cout << root << endl;
  return root;
}

Json::Value getBlockCountToJSON (void) {
  return getBlockCountToJSON(BLOCKCHAIN_NAME);
}

Json::Value getBlockToJSON (hash_t bHash) {
  string nameBC = BLOCKCHAIN_NAME;
  Json::Value root;

  if (str2BlockChainPtrMap.find(nameBC) == str2BlockChainPtrMap.end()) {
    root["Block"] = "Not found";
    return root;
  }

  BlockChain *bcPtr = str2BlockChainPtrMap[nameBC];
  Block *bptr = bcPtr->findBlock(bHash);
  if (!bptr) {
    root["Block"] = "Not found";
    return root;
  }

  root["Block"] = bptr->getBlockToJSON();
  return root;
}

Json::Value getBlockToJSON (uint index) {
  string nameBC = BLOCKCHAIN_NAME;
  Json::Value root;

  if (str2BlockChainPtrMap.find(nameBC) == str2BlockChainPtrMap.end()) {
    root["Block"] = "Not found";
    return root;
  }

  BlockChain *bcPtr = str2BlockChainPtrMap[nameBC];
  Block *bptr = bcPtr->findBlock(index);
  if (!bptr) {
    root["Block"] = "Not found";
    return root;
  }

  root["Block"] = bptr->getBlockToJSON();
  return root;
}

Json::Value getTransactionToJSON (uint bIndex, uint tIndex) {
  string nameBC = BLOCKCHAIN_NAME;
  Json::Value root;

  if (str2BlockChainPtrMap.find(nameBC) == str2BlockChainPtrMap.end()) {
    root["Block"] = "Not found";
    return root;
  }

  BlockChain *bcPtr = str2BlockChainPtrMap[nameBC];
  uint count = bcPtr->getBlockCount();
  Block *b;
  if (bIndex > count) {
    root["txn"] = "Incorrect block index. Not found";
    return root;
  }
  b = bcPtr->getBlock(bIndex);
  if (!b) {
    root["txn"] = "Block not found";
    return root;
  }
  if (tIndex > b->vTxn.size()) {
    root["txn"] = "Incorrect transaction index. Not found";
    return root;
  }

  Transaction* txn = b->vTxn[tIndex];
  if (!txn) {
    root["txn"] = "Transaction not found";
    return root;
  }
  root["txn"] = txn->getTransactionToJSON();
  return root;
}

Json::Value getTransactionByHashJSON (hash_t txnHash) {
  string nameBC = BLOCKCHAIN_NAME;
  Json::Value root;

  if (str2BlockChainPtrMap.find(nameBC) == str2BlockChainPtrMap.end()) {
    root["Block"] = "Not found";
    return root;
  }

  BlockChain *bcPtr = str2BlockChainPtrMap[nameBC];
  uint count = bcPtr->getBlockCount();
  Block *b;
  for (int bIndex = 0; bIndex < count; bIndex++) {
    b = bcPtr->getBlock(bIndex);
    if (!b) continue;
    for (int i = 0; i < b->vTxn.size(); i++) {
      Transaction* txn = b->vTxn[i];
      if (!txn)
        continue;
      if (txnHash == txn->txnHash) {
        root["txn"] = txn->getTransactionToJSON();
        return root;
      }
    }
  }
  root["txn"] = "Not found";
  return root;
}

class ChainParams {
  // seed nodes
  // default port
  // nPowTargetTimespan
  // Initial reward
  // Halving num blocks
  // Initial difficulty
  // dampening threshold for dynamic difficulty adjustments
};
