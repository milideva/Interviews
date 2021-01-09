Requirements

Compiler

This project uses g++ compiler with -std=c++2a . It works fine with -std=C++17
as well. It uses some minor C++17 features, so gives some warning if compiled
with -std=c++14.

Libraries

I'm using openSSL library (-lcrypto) for cryptographic support.
For REST support, Microsoft's C++ REST SDK called cpprest is used.
For JSON support, Jsoncpp is used, an open source C++ library that allows
manipulating JSON values, including serialization and deserialization.

Environment

This project was compiled and run and unit tested on MacOS 10.15.7.
The Makefile specifies basic compilation and linking machinery.
Executables


"blockchain" : this is the main blockchain running node along with a miner


"rest client" : this is to GET and to POST some queries to blockchain
I've also tested restServer using queries from Postman.


"protoclient" : this is a sample Protocol Discovery client for discovering other
peers It talks over sockets to async Server thread which stores peer Discovery
message (peer IPv4 address and port). Currently async proto server stores only 5
peers (last 5).


Basic Objects

Block, BlockChain, Miner, Wallet, Account, ECKey, Transaction, memPool, concurrent queue.

Target difficulty changes as the targeted block time is 30 seconds and as
solving the puzzle is a lottery, the actual block time varies. Thus difficulty
adjusts and is dynamic. Currently it adjusts every block, if block time is +40%
or -40% of 30 seconds.

Mining reward is 100000000 and it halves every 100 blocks.

ECKey object provides public/private keys interface such as sign/verify and
serialize/deserialize of keys. It is using ECDSA based keys.

Account object has public address, balance and nonce.
A wallet creates accounts. These are local to wallet.
They are also sync.ed to global blockchain.

Similar to Ethereum model, a global state tracks an account. Hence nonce
protects against double spending.

Blocks and transactions can have additional payload. Wallet can set data payload
for each transaction when a transaction is created and signed. Block's data
payload can be set by the miner before solving proof of work.

SHA256 is used as a hash function.

Each transaction is hashed with the following: fromAddress, toAddress, nValue,
nonce, context. Each transaction is signed by using ECDSA private key. A hash of
transaction is signed and this hash is also part of transaction data structure.

A wallet is used to create an account and it holds private and public key. A
transaction is created by wallet and it signs the transaction and enqueues it on
conCurrent Queue. All transactions in a block are used for "merkle root"
calculation. I've not implemented Merkle root. But each transaction's hash is
used to calculate a blockHdr.hashTransactionsRoot.

Currently a test code creates producer threads and 3 wallets. Alice, Bob and
Charlie. It creates some transactions between them and puts them in a concurrent
Queue. Miner watches this queue and picks up transactions from this queue.

A block hash includes current time, nonce of block header, prev block's hash,
and current transactions' root hash. Miner creates and adds COINBASE transaction
(1st transaction of the block) to the block to reward itself. Miner reads
Current reward amount from BlockChain. Miner starts Proof of work to solve the
puzzle, meeting the difficulty and block time. It calculates the hashes to meet
the difficulty condition (hash < difficulty). It adjusts nonce, and retakes time
if nonce overflows to become 0. Currently miner does not broadcast the
successful block. It just adds it to the blockchain object.

Blockchain will revalidate some of the basic things and add it to its chain. It
also adjusts global accounts for settlement of each transaction. Nonce of each
account are also adjusted in global state. If nonce does not match, the block is
not accepted. Thus it prevents a double spend attack. Blockchain's critical
section is protected by a mutex lock.

JSON interface

A rest client code is provided. It can also be done using Postman client.
Postman :
http://{{chainIPAddr}}:{{port}}/restblockchain

restCommonHeader.h specifies the host and port number for the REST server.

Following 4 Rest APIs are implemented in REST server code.

GET to get getBlockCount()
(no parameters needed)
This is implemented in getBlockCountToJSON() on blockchain side.

POST 
["getBlock", "5"]

Gets Block 5 in JSON format.
This index is 0 based.

This is implemented in getBlockToJSON() on blockchain side.

POST
["getTransaction", "6", "7"]

Gets transaction #7 from block #6 (both are 0-based)

This is implemented in getTransactionToJSON() on blockchain side.

POST
testTxnJson() creates a JSON transaction that is from Bob to Alice and is signed
by Bob's private key. This will be seen in the initial part of the log.

{

        "context" : "@@@@@@ JSON TEST @@@@@@",

        "fromAddr" : "048467FB8E4BBD67D3A08838C6264E9F33305A8AE517E67AD470660730CDAB4B801FF7F7CEDBBD0B68D6EFD46B717023CAA27B412AC306F2CEA05037C9CF986C4E",

        "nValue" : 10,

        "nonce" : 0,

        "r" : "31987E68CE1F27122DEE9986570DE6620C596A3FA51BBCFCDDC6C32CA27F2EE3",

        "s" : "A6816B85FAF9D4ACA81CAFE1E36CEFFDDF0090D6AA1984554A31B894F72B78FC",

        "toAddr" : "0454E1006492B18F568CE42629BFF2F3CF3FEE44AD659119B22612EF148840E65779365FE86AB349338BE762580DE7BA8E38ED9E35B968D29072AEF95B4D6A1137",

        "txnHash" : "o\u0013|\u021f\u07c2b"

}

This transaction is received by restServer in JSON. It converts it into string
and calls createTransactionFromJSON(). This function deserializes it and creates
a transaction object, verifies its signature and submits it for mining to conQ.
A miner picks it up from there and includes it in next block for mining.

