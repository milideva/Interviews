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
    cout << "printTransaction: fromAddr:" << fromAddr;
  }
  cout << " toAddr:" << toAddr << " amt:" << nValue << " nonce:" << nonce << " context: " << context << endl;

  getTransactionToJSON();
}

bool Transaction::calcSHA256 (const char* input, unsigned long length, hash_t *md) {
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

hash_t Transaction::calcHash (void) {

  // cout << "Entered Transaction::calcHash: this->txnHash: " << this->txnHash << endl;
  //if (this->txnHash) 
  // return this->txnHash;

  stringstream ss;
  ss << fromAddr << toAddr << nValue << nonce << context;

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

  EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(NID_secp256k1);
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
    EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_set_public_key(eckeyPublic, toAddr);
    char *serPK = getSerializedPublicKey(eckeyPublic);
    root["toAddr"] = serPK;
    EC_KEY_free(eckeyPublic);  
  } 

  root["nValue"] = nValue;
  root["nonce"] = nonce;
  root["context"] = context;
  Json::Value sigJ;

  const BIGNUM *r;
  const BIGNUM *s;
  ECDSA_SIG_get0(fromSig, &r, &s);
  char* rStr = getSerializedBIGNUM(r);
  char* sStr = getSerializedBIGNUM(s);

  sigJ["r"] = rStr;
  sigJ["s"] = sStr;
  root["fromSig"] = sigJ;

  OPENSSL_free(sStr);
  OPENSSL_free(rStr);
  
  string strHash = hashToString(txnHash);
  root["txnHash"] = strHash;

  Json::StreamWriterBuilder builder;
  string message = Json::writeString(builder, root);
  cout << message << endl;

  return root;
}
