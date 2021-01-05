#include "eckey.h"

ECKey::ECKey() {
  eckey = EC_KEY_new_by_curve_name(NID_secp256k1);
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

ECDSA_SIG* ECKey::sign (const unsigned char* digest, size_t digest_len) {
  ECDSA_SIG* sig = ECDSA_do_sign(digest, digest_len, eckey);
  if (sig == NULL) {
    cout << "ECDSA_do_sign() failed" << endl;
  }
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
