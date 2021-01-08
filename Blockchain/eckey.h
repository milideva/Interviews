#ifndef ECKEY_H
#define ECKEY_H
#pragma once

#include "commonHeader.h"

#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h> // for NID
#define CURVE_ID NID_secp256k1

typedef EC_POINT const* publicKey_t;
typedef EC_POINT const* chainAddr; // This is just a handle and not an actual address, TODO - change name
typedef BIGNUM privateKey_t;
typedef ECDSA_SIG* ecdsaSig_t;

class ECKey {
 private:
  EC_KEY* eckey;
  BIGNUM const* getPrivateKey ();
  EC_KEY* getECKey ();
  char* serPublicKey;

 public:
  ECKey();
  ~ECKey();

  EC_POINT const* getPublicKey ();
  ECDSA_SIG* sign (const unsigned char* digest, size_t digest_len);
  int verify (const unsigned char* digest, int digest_len, ECDSA_SIG* sig);

  char* serializePublicKey (void);

  void printPublicKey (void);
  void printPrivateKey (void);
};

char* getSerializedPublicKey (EC_KEY *);
char* getSerializedBIGNUM (const BIGNUM *);
int getDeserializedBIGNUM (BIGNUM **priv, const char *bigNumStr);

EC_KEY* deserPublicKey (const char *pub_key);
BIGNUM* getDeserializedBIGNUM (char *bigNumStr);

chainAddr getPublicKey (EC_KEY *);
void printPublicKey (chainAddr pkAddr);
char* getCharPublicKey (chainAddr pkAddr);

bool calcSHA256 (const char* input, unsigned long length, hash_t *md);
hash_t getPkHash (chainAddr addr);

#endif
