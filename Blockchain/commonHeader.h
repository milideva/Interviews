 
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <sstream>    
#include <iostream>
#include <json/json.h>

#include <boost/multiprecision/cpp_int.hpp> // For uint256_t
using namespace boost::multiprecision;

#include <openssl/sha.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h> // for NID

using namespace std;

typedef uint256_t hash_t;
typedef uint64_t coin_t;

// TO DO move these to chain params
#define COIN (100000000ULL)
#define HALVING_NUM_BLOCKS (100)
#define BLOCKCHAIN_NAME "toyChain"

