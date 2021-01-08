#include "transaction.h"
#include "blockchain.h"

Transaction::Transaction (chainAddr fromAddr, chainAddr toAddr, uint64_t nValue, uint64_t nonce, 
                          string context, string nameBC) {
  this->fromAddr = fromAddr;
  this->toAddr = toAddr;
  this->nValue = nValue;
  this->nonce = nonce;
  this->context = context;
  this->txnHash = 0;
  this->nameBlockChain = nameBC;
}

void Transaction::printTransaction (void) {
  if (fromAddr) {
    cout << "printTransaction: from";
    printPublicKey(fromAddr);
  }
//  cout << " toAddr:" << toAddr << " amt:" << nValue << " nonce:" << nonce << " context: " << context << endl;
  cout << " to ";
  printPublicKey(toAddr);
  cout << " amt:" << nValue << " nonce:" << nonce << " context: " << context << endl;

  getTransactionToJSON();
}

hash_t Transaction::calcHash (void) {

  stringstream ss;

  if (fromAddr) {
    char* serPKfromAddr = getCharPublicKey(fromAddr);
    string fromStr(serPKfromAddr);
    ss << fromStr;
    //cout << "000000000000000 calcHash: fromStr:" << fromStr << endl;
  }

  char* serPKtoAddr = getCharPublicKey(toAddr);
  string toStr(serPKtoAddr);
  ss << toStr;
  //cout << "000000000000000 calcHash: toStr:" << toStr << endl;

  ss << nValue << nonce << context;

  string str;
  ss >> str;

  hash_t md = 0;

  if (!calcSHA256(str.c_str(), str.length(), &md)) {
    cout << "Failed Transaction calcSHA256()" << endl;
  }

  this->txnHash = md;
  //cout << " Transaction::calcHash: md: " << md << endl;
  return md;
}

bool Transaction::setSig (ecdsaSig_t sig) {
  fromSig = sig;
  return verify();
}

bool Transaction::verify (void) {
  hash_t txnHash = calcHash();
  if (txnHash == 0) {
    // TO DO hash can be 0 - a valid value !
    cout << "txn calcHash failed" << endl;
    return false;
  }

  EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(CURVE_ID);
  if (fromAddr != 0) {
    EC_KEY_set_public_key(eckeyPublic, fromAddr);
  } else {
    cout << "Transaction verify : CoinBase transaction, verify with toAddress" << endl;
    EC_KEY_set_public_key(eckeyPublic, toAddr);
  }
  
  //cout << "Transaction::verify txnHash:" << txnHash << " fromSig:" << fromSig << endl;

  int rc = ECDSA_do_verify((const unsigned char *) &txnHash, sizeof txnHash, fromSig, eckeyPublic);
  EC_KEY_free(eckeyPublic);

  if (rc == 1) {
    cout << "Transaction ECDSA signature verify success" << endl;
  } else if (rc == 0) {
    cout << "Transaction ECDSA signature verify fail: incorrect signature" << endl;
  } else {
    cout << "Transaction ECDSA signature verify fail error code:" << rc << endl;
  }

  return rc == 1 ? true : false;
}

///////////////////// JSON queries /////////////////////

Json::Value Transaction::getTransactionToJSON (void) {

  Json::Value root; 

  if (fromAddr) {
    EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_set_public_key(eckeyPublic, fromAddr);
    char *serPK = getSerializedPublicKey(eckeyPublic);
    root["fromAddr"] = serPK;
    EC_KEY_free(eckeyPublic);  
  } else {
    root["fromAddr"] = 0;
  }

  if (toAddr) {
    EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(CURVE_ID);
    EC_KEY_set_public_key(eckeyPublic, toAddr);
    char *serPK = getSerializedPublicKey(eckeyPublic);
    root["toAddr"] = serPK;
    EC_KEY_free(eckeyPublic);  
  } 

  root["nValue"] = nValue;
  root["nonce"] = nonce;
  root["context"] = context;

  const BIGNUM *r;
  const BIGNUM *s;
  ECDSA_SIG_get0(fromSig, &r, &s);
  char* rStr = getSerializedBIGNUM(r);
  char* sStr = getSerializedBIGNUM(s);

//  Json::Value sigJ;
//  sigJ["r"] = rStr;
//  sigJ["s"] = sStr;
//  root["fromSig"] = sigJ;
  root["r"] = rStr;
  root["s"] = sStr;

  OPENSSL_free(sStr);
  OPENSSL_free(rStr);

/*
  // openSSL needs unsigned char pointer and jsoncpp returns bool for unsigned
  // char pointer, so this is not going work

  // Serialize using openSSL api
  int sigLen = i2d_ECDSA_SIG(fromSig, NULL);
  cout << "sigLen" << sigLen << endl;
  unsigned char *sigBytes = (unsigned char *) OPENSSL_malloc(sigLen);
  sigLen = i2d_ECDSA_SIG(fromSig, &sigBytes);
  cout << "SERIALIZING signature len:" << sigLen << " sign:" << sigBytes << endl; 
  root["fromSig"] = reinterpret_cast<char *>(sigBytes);
  root["sigLen"] = sigLen;
  
*/
  string strHash = hashToString(txnHash);
  root["txnHash"] = strHash;

  //Json::StreamWriterBuilder builder;
  //string message = Json::writeString(builder, root);
  //cout << message << endl;

  return root;
}

#include "concurrentQueue.h"
extern ConcurrentQueue <Transaction *> conQ;


void createTransactionFromJSON (string contextStr, string fromAddrStr, string rStr, string sStr, 
                                int nValue, int nonce, string toAddrStr, string txnHashStr) {

  const char* fromAddrPtr = fromAddrStr.c_str(); // These pointers point to internal string - no need to free
  const char* toAddrPtr = toAddrStr.c_str();
  const char* rPtr = rStr.c_str();
  const char* sPtr = sStr.c_str();
  const char* txnHashPtr = txnHashStr.c_str();
  
  EC_KEY* fromEckey;
  fromEckey = deserPublicKey(fromAddrPtr);
  
  EC_KEY* toEckey;
  toEckey = deserPublicKey(toAddrPtr);

  chainAddr fromAddr = getPublicKey(fromEckey);
  chainAddr toAddr = getPublicKey(toEckey);

  cout << endl << "createTransactionFromJSON: ################" << endl << endl;

  ECDSA_SIG* sig = ECDSA_SIG_new();
  BIGNUM* r = NULL;
  BIGNUM* s = NULL;

  getDeserializedBIGNUM(&r, rPtr);
  getDeserializedBIGNUM(&s, sPtr);
  int ret = ECDSA_SIG_set0(sig, r, s);

  Transaction* txn = new Transaction(fromAddr, toAddr, nValue, nonce, contextStr, BLOCKCHAIN_NAME);
  hash_t txnHash = txn->calcHash();

  txn->setSig(sig);

  txn->printTransaction();
  
  conQ.push(txn);
}
