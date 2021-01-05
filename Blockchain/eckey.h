#ifndef ECKEY_H
#define ECKEY_H
#pragma once

#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h> // for NID
#include <openssl/bio.h>
#include <openssl/pem.h>

#include <iostream>
using namespace std;

typedef EC_POINT const* publicKey_t;
typedef EC_POINT const* chainAddr;
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
#endif
