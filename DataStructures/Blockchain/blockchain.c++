#include <iostream>
#include <ctime>

#include <openssl/sha.h>
#include <boost/multiprecision/cpp_int.hpp>

#include <unordered_map>
#include <string>
#include <sstream>    

using namespace boost::multiprecision;
using namespace std;

class Block {

  struct BlockHeader_ {
    int32_t nVersion; // 4B 
    uint256_t hashPrevBlock; //32B :  SHA256(SHA256(prevBlockHeader))
    uint256_t hashMerkleRoot; // 32B : merkle root of transactions
    uint32_t nTime; // 4B : timestamp
    uint32_t nBits; // 4B : target difficulty
    uint32_t nNonce;// 4B 
  };

  BlockHeader_ block;
  
  void setNonce (uint32_t nonce) {
    block.nNonce = nonce;
  }

  void sethashPrevBlock (size_t hash) {
    block.hashPrevBlock = hash;
  }

  void setTime (uint32_t time) {
    block.nTime = time;
  }

  public :
  
  Block (int ver, size_t prevHash, size_t merkleHash, time_t nTime) {
    block.nVersion = ver;
    block.hashPrevBlock = prevHash;
    block.hashMerkleRoot = merkleHash;
    block.nTime = nTime;
  }

  string toString () {
    // to_string() can not take 256b number - so do not use this method
    return  to_string(block.nTime) + to_string(block.nBits) + to_string(block.nNonce);
  }

  size_t getHash () {

    hash<string> hashfn;
    /*
    string str = toString();
    size_t hash = hashfn(str);
    */
    stringstream ss;
    ss << block.nTime << block.nNonce << block.hashPrevBlock << block.hashMerkleRoot;
    size_t hash = hashfn(ss.str());

    return hash;
  }
  
  friend class BlockChain;
  
};

class BlockChain {

private :
  vector <class Block *> vecChain;
  unordered_map <size_t, class Block *> mapChain;
  size_t last;
  Block *gen;
public:
  BlockChain () {
    last = 0;
    // Create a genesis block here in the constructor
    gen = new Block(1, 0, 0, time(0));
    cout << "Created the Genesis block " << endl ;
    mineBlock(gen);
  }

  Block *findBlock (size_t hash) {
    if (mapChain.find(hash) != mapChain.end()) {
      return mapChain[hash];
    }
    return nullptr;
  }

  Block *findBlock (unsigned int index) {
    if (index >= vecChain.size()) return nullptr;
    return vecChain[index];
  }

  void addBlock (Block *b) {
    if (!b) return;
    cout << "Adding block# " << last << endl;
    vecChain.push_back(b);
    mapChain[b->getHash()] = b;
    last++;
  }

  size_t getLastBlockHash () {
    if (!last) return 0;
    Block *b = vecChain[last-1];
    if (!b) return 0;
    return b->getHash();
  }

  void mineBlock (Block *b) {
    size_t hash;
    uint32_t nonce = b->block.nNonce;
    time_t now = time(0);  

    b->setTime(now);
    b->sethashPrevBlock(getLastBlockHash());

    do {
      nonce++;
      b->setNonce(nonce);
      hash = b->getHash();
    } while (hash < b->block.nBits);
    cout << "Mined a block, hash: " << hash << endl;
    addBlock(b);
  }
};

//time_t now = time(0);  
/*  
  // convert now to string form
  char* dt = ctime(&now);
  cout << "The local date and time is: " << dt << endl;
  
  // convert now to tm struct for UTC
  tm *gmtm = gmtime(&now);
  dt = asctime(gmtm);
  cout << "The UTC date and time is:"<< dt << endl;
*/ 

int main() {
  class BlockChain bc;
  //class Block *b = genesisBlock();
  //bc.mineBlock(b);

  return 0;
}
