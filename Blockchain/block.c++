
#include "block.h"
#include "blockchain.h"

#include <openssl/sha.h>
#include <iostream>

#define BLOCK_TIME_SECONDS (30)
#define INIT_SHIFT (44);
uint dynDifficulty = INIT_SHIFT;

// Move this to Chain Params TODO
uint32_t getBlockchainParamsDifficulty() {
  return dynDifficulty;
}

void dynamicDifficulty (float blockTimeSeconds) {
  // Dampening thresholds for dynamic difficulty adjustments
  float max = 1.4 * BLOCK_TIME_SECONDS;
  float min = 0.6 * BLOCK_TIME_SECONDS;

  if (blockTimeSeconds < min) {
    dynDifficulty -= 1; // increase difficulty, reduce the shift
    cout << ">>>>>>>>>>> Dynamic difficulty increased. nShift:" << dynDifficulty << endl << endl;
  } else if (blockTimeSeconds > max) {
    dynDifficulty += 1;
    cout << "<<<<<<<<<<< Dynamic difficulty decreased. nShift:" << dynDifficulty << endl << endl;
  }
}


Block::Block (int ver, hash_t prevHash, hash_t merkleHash, time_t nTime, coin_t reward, string dataPayloadIn) {
  blockHdr.nVersion = ver;
  blockHdr.hashPrevBlock = prevHash;
  blockHdr.hashTransactionsRoot = merkleHash;
  blockHdr.nTime = nTime;
  blockHdr.nBits = getBlockchainParamsDifficulty();
  dataPayload = dataPayloadIn;
}

string Block::getDataPayload (void) {
  return dataPayload;
}

void Block::setDataPayload (string str) {
  dataPayload = str;
}

void Block::setNonce (uint32_t nonce) {
  blockHdr.nNonce = nonce;
}

void Block::setHashPrevBlock (hash_t prevHash) {
  blockHdr.hashPrevBlock = prevHash;
}

void Block::setTime (uint32_t time) {
  blockHdr.nTime = time;
}

bool Block::calcSHA256 (const char* input, unsigned long length, hash_t *md) {
  if (!md)
    return false;
  
  SHA256_CTX context;
  if (!SHA256_Init(&context))
    return false;
  
  if (!SHA256_Update(&context, input, length))
    return false;
  
  if (!SHA256_Final((unsigned char *)md, &context))
    return false;
  
  return true;
}

// This is a hash each transaction's hash in the block
void Block::calcHashTransactionsRoot (void) {
  stringstream ss;
   for (int i = 0; i < vTxn.size(); i++) {
     Transaction* txn = vTxn[i];
     if (txn) {
       ss << txn->txnHash;
       cout << "calcHashTransactionsRoot: txn:" << i+1 << " adding txnHash:0x" << txn->txnHash << endl;
     }
   }
   string str;
   ss >> str;

   if (!calcSHA256(str.c_str(), str.length(), &blockHdr.hashTransactionsRoot)) {
     cout << "calcHashTransactionsRoot: Failed calcSHA256()" << endl;
   }
   cout << "calcHashTransactionsRoot:0x" << blockHdr.hashTransactionsRoot << endl;
}

// This is the header hash.
// It includes time, nonce of block header, prev block's hash, and current transactions' hash
hash_t Block::calcHash (void) {
  
  stringstream ss;
  ss << blockHdr.nTime << blockHdr.nNonce << blockHdr.hashPrevBlock << blockHdr.hashTransactionsRoot;

  string str;
  ss >> str;
  
  // Update block's private hash
  if (!calcSHA256(str.c_str(), str.length(), &hash)) {
    cout << "Failed calcSHA256()" << endl;
  }

  //cout << "Block hash: 0x" << hex << hash << endl;  
  return hash;
}

uint32_t Block::getDifficulty () {
  return blockHdr.nBits;
}

hash_t Block::getBlockHash () {
  return hash;
}

uint32_t Block::getNonce () {
  return blockHdr.nNonce;
}

void Block::printBlock (void) {

  cout << "printBlock(): " << dataPayload << endl;
  getBlockToJSON();
/*
  for (int i = 0; i < vTxn.size(); i++) {
    Transaction* txn = vTxn[i];
    if (txn) {
      txn->printTransaction();
    }
  }
*/  
}

void Block::proofOfWork (void) {

  calcHashTransactionsRoot();
  
  hash_t hash;
  int nShift = getDifficulty();
  cout << endl << "Miner starting Proof of work for block# " << getBlockCount() << " nShift:" << nShift << endl;

  const clock_t beginTime = clock();
  time_t now = time(0);
  setTime(now);
  uint32_t nonce = getNonce();

  do {
    nonce++;
    setNonce(nonce);
    hash = calcHash(); // this is header checksum
    if (nonce == 0) {
      now = time(0); // ran out of nonce! change time - or reorder transactions in the block (except coinbase)
      setTime(now);
    }
    hash_t shiftedHash = hash >> nShift;

    if (shiftedHash == 0) 
      break;
  } while (1);

  const clock_t endTime = clock();
  float tickSeconds = float( endTime - beginTime ) /  CLOCKS_PER_SEC;
  cout << endl << "Mined a block, hash:0x" << hash << " in " << tickSeconds << " seconds" << endl;

  dynamicDifficulty(tickSeconds);

  getBlockToJSON();
}

void uint256ToBytes (uint256_t i, uint8_t* output, size_t len) {  
  auto count = i.backend().size();
  auto tsize = sizeof(boost::multiprecision::limb_type);
  auto copy_count = count * tsize;
  if (len < count * tsize)
    throw std::runtime_error("len < count * tsize");
  memcpy(output, i.backend().limbs(), copy_count);
  if (len > copy_count) {
    memset(output + copy_count, 0, len - copy_count);
  }
}

string convertToString (uint8_t* a, int size) { 
    int i; 
    string s = ""; 
    for (i = 0; i < size; i++) { 
      char ch = (char) a[i];
        s = s + ch; 
    } 
    return s; 
} 

string hashToString (hash_t hash) {
  uint8_t output[8] = {0};
  size_t len = 8;
  
  uint256ToBytes(hash, output, len);
  string s = convertToString(output, 8);
  return s;
}

Json::Value Block::getBlockToJSON (void) {
  Json::Value root;

  Json::Value blockJ;
  
  blockJ["nVersion"] = blockHdr.nVersion;
  string strHash;
  strHash = hashToString(blockHdr.hashPrevBlock);
  blockJ["hashPrevBlock"] = strHash;

  strHash = hashToString(blockHdr.hashTransactionsRoot);
  blockJ["hashTransactionsRoot"] = strHash;

  blockJ["nTime"] = blockHdr.nTime;
  blockJ["nBits"] = blockHdr.nBits;
  blockJ["nNonce"] = blockHdr.nNonce;

  root["blockHdr"] = blockJ;
  root["dataPayload"] = dataPayload;

  Json::Value vec;
  for (int i = 0; i < vTxn.size(); i++) {
    Transaction* txn = vTxn[i];
    if (txn) {
      Json::Value txnJ = txn->getTransactionToJSON();
      vec[i]["txn"] = txnJ;
    }
  }
  root["vTxn"] = vec;

  cout << root << endl;

  return root;
}
