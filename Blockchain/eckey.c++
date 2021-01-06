#include "eckey.h"
//#include <iostream>
//using namespace std;

bool calcSHA256 (const char* input, unsigned long length, hash_t *md) {
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

// Think of this as a bitcoin address way.
// TODO cache this
hash_t getPkHash (chainAddr addr) {
  if (!addr) return 0;

  stringstream ss;
  char* serPKAddr = getCharPublicKey(addr);
  string addrStr(serPKAddr);
  ss << addrStr;
  
  string str;
  ss >> str;

  hash_t md = 0;

  if (!calcSHA256(str.c_str(), str.length(), &md)) {
    cout << "getPkHash: Failed Transaction calcSHA256()" << endl;
  }
  return md;
}

ECKey::ECKey() {
  eckey = EC_KEY_new_by_curve_name(CURVE_ID);
  if (eckey == NULL) {
    cout << "Failed to generate eckey using EC_KEY_new_by_curve_name()" << endl;
    return;
  }
  
  if (EC_KEY_generate_key(eckey) == 0) {
    cout << "Failed to generate key using EC_KEY_generate_key()" << endl;
  }
  serPublicKey = serializePublicKey();
}

ECKey::~ECKey() {
  if (serPublicKey) 
    OPENSSL_free(serPublicKey);
  EC_KEY_free(eckey);
}

EC_KEY* ECKey::getECKey () {
  return eckey;
}

EC_POINT const* ECKey::getPublicKey () {
  EC_POINT const* pub = EC_KEY_get0_public_key(eckey);
  //printPublicKey();
  return pub;
}

void printPublicKey (chainAddr pkAddr) {
 EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(CURVE_ID);
 EC_KEY_set_public_key(eckeyPublic, pkAddr);
 char *serPK = getSerializedPublicKey(eckeyPublic);
 cout << "address:" << serPK;
 EC_KEY_free(eckeyPublic);
}

char* getCharPublicKey (chainAddr pkAddr) {
  if (!pkAddr) return nullptr;

  EC_KEY *eckeyPublic = EC_KEY_new_by_curve_name(CURVE_ID);
  EC_KEY_set_public_key(eckeyPublic, pkAddr);

  const EC_GROUP* group = EC_KEY_get0_group(eckeyPublic);
  point_conversion_form_t form = EC_GROUP_get_point_conversion_form(group);

  char *serPK = EC_POINT_point2hex(group, pkAddr, form, NULL);

  EC_KEY_free(eckeyPublic);
  return serPK;
}

chainAddr getPublicKey (EC_KEY *ecKey) {
  EC_POINT const* pub = EC_KEY_get0_public_key(ecKey);
  return pub;
}

void ECKey::printPublicKey (void) {
  
  const EC_GROUP* group = EC_KEY_get0_group(eckey);
  point_conversion_form_t form = EC_GROUP_get_point_conversion_form(group);

  char* pubKeyStr = EC_POINT_point2hex(group,
                                       EC_KEY_get0_public_key(eckey), 
                                       form, NULL);
  cout << "Public Key: 0x" << pubKeyStr << endl;
  OPENSSL_free(pubKeyStr);  
}

char* getSerializedPublicKey (EC_KEY* eckey) {
  const EC_GROUP* group = EC_KEY_get0_group(eckey);
  point_conversion_form_t form = EC_GROUP_get_point_conversion_form(group);
  
  return EC_POINT_point2hex(group, EC_KEY_get0_public_key(eckey), form, NULL);
}

char* getSerializedPrivateKey (BIGNUM *bn) {
  return getSerializedBIGNUM(bn);
}

char* ECKey::serializePublicKey (void) {
  
  if (serPublicKey) {
    return serPublicKey;
  }

  serPublicKey = getSerializedPublicKey(eckey);
  cout << "Public Key: 0x" << serPublicKey << endl;
  return serPublicKey;
}

BIGNUM const* ECKey::getPrivateKey () {
  BIGNUM const* priv = EC_KEY_get0_private_key(eckey);
  //printPrivateKey();
  return priv;
}

void ECKey::printPrivateKey () {
  char* privKeyStr = BN_bn2hex(EC_KEY_get0_private_key(eckey));
  cout << "Private Key: 0x" << privKeyStr << endl;
  OPENSSL_free(privKeyStr);
}

char* getSerializedBIGNUM (const BIGNUM *bignum) {
  char* privKeyStr = BN_bn2hex(bignum);
  return privKeyStr;
}

int getDeserializedBIGNUM (BIGNUM **priv, const char *bigNumStr) {
  return BN_hex2bn(priv, bigNumStr);
}

ECDSA_SIG* ECKey::sign (const unsigned char* digest, size_t digest_len) {
  ECDSA_SIG* sig = ECDSA_do_sign(digest, digest_len, eckey);
  if (sig == NULL) {
    cout << "ECDSA_do_sign() failed" << endl;
  }

/* test signature serializer deserializer code
  unsigned char *sigStr = nullptr;
  int sigLen = i2d_ECDSA_SIG(sig, &sigStr);
  cout << "DER SIGN len:" << sigLen << " SIGN:" << sigStr << endl;

  const unsigned char *sigCStr = sigStr;
  ECDSA_SIG* sig2 = d2i_ECDSA_SIG(NULL, &sigCStr, sigLen);

  return sig2;
*/
  return sig;
}

int ECKey::verify (const unsigned char* digest, int digest_len, ECDSA_SIG* sig) {
  int ret = ECDSA_do_verify(digest, digest_len, sig, eckey);
  if (ret == 1) {
    cout << "ECDSA signature verify success" << endl;
  } else if (ret == 0) {
    cout << "ECDSA signature verify fail: incorrect signature" << endl;
  } else {
    cout << "ECDSA signature verify fail error code:" << ret << endl;
  }
  return ret;
}

EC_KEY* deserPublicKey (const char *pub_key) {

  EC_KEY* eckey;
  EC_KEY* pub_eckey = EC_KEY_new_by_curve_name(CURVE_ID);
  EC_POINT* pub = NULL;

  eckey = EC_KEY_new_by_curve_name(CURVE_ID);
  const EC_GROUP* group = EC_KEY_get0_group(eckey);
  point_conversion_form_t form = EC_GROUP_get_point_conversion_form(group);

  pub = EC_POINT_hex2point(EC_KEY_get0_group(eckey), pub_key, pub, NULL);
  EC_KEY_set_public_key(pub_eckey, pub);

  OPENSSL_free(eckey);
  return pub_eckey;
}
