

(async function() {
	// this returns the provider, or null if it wasn't detected
	const provider = await detectEthereumProvider();
	if (provider) {
  		startApp(provider); // Initialize your app
	} else {
  		console.log('Please install MetaMask!');
	}
}());

function startApp(provider) {
  // If the provider returned by detectEthereumProvider is not the same as
  // window.ethereum, something is overwriting it, perhaps another wallet.
  if (provider !== window.ethereum) {
    console.error('Do you have multiple wallets installed?');
  } else {
  // Access the decentralized web!
  	console.log('Found	 MetaMask!');
  }
}

// GlobalCoin Redeem contract to Withdraw points and get GlobalCoin
// Contract ABI. 
var abi = 
[
	{
		"inputs": [],
		"stateMutability": "payable",
		"type": "constructor"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": true,
				"internalType": "address",
				"name": "_from",
				"type": "address"
			},
			{
				"indexed": false,
				"internalType": "uint256",
				"name": "_amount",
				"type": "uint256"
			}
		],
		"name": "MoneyReceived",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": true,
				"internalType": "address",
				"name": "_beneficiary",
				"type": "address"
			},
			{
				"indexed": false,
				"internalType": "uint256",
				"name": "_amount",
				"type": "uint256"
			}
		],
		"name": "MoneySent",
		"type": "event"
	},
	{
		"anonymous": false,
		"inputs": [
			{
				"indexed": true,
				"internalType": "address",
				"name": "previousOwner",
				"type": "address"
			},
			{
				"indexed": true,
				"internalType": "address",
				"name": "newOwner",
				"type": "address"
			}
		],
		"name": "OwnershipTransferred",
		"type": "event"
	},
	{
		"inputs": [],
		"name": "receive",
		"outputs": [],
		"stateMutability": "payable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "address",
				"name": "newOwner",
				"type": "address"
			}
		],
		"name": "transferOwnership",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "uint256",
				"name": "_amount",
				"type": "uint256"
			},
			{
				"internalType": "uint256",
				"name": "_nonce",
				"type": "uint256"
			},
			{
				"internalType": "bytes",
				"name": "_sig",
				"type": "bytes"
			}
		],
		"name": "withdrawPoints",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "getContractAddress",
		"outputs": [
			{
				"internalType": "address",
				"name": "",
				"type": "address"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "getContractBalance",
		"outputs": [
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "getOwnerBalance",
		"outputs": [
			{
				"internalType": "uint256",
				"name": "",
				"type": "uint256"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "owner",
		"outputs": [
			{
				"internalType": "address",
				"name": "",
				"type": "address"
			}
		],
		"stateMutability": "view",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "renounceOwnership",
		"outputs": [],
		"stateMutability": "pure",
		"type": "function"
	}
]
; 

abiDecoder.addABI(abi);

// contract address
var contractAddress = '0xc23b8081a2ef71FA0b01d6Ab5034b62E09Ab070D'; 
var ownerAddress = '0xd93697773fc828F1e7FD8c28A328B26e28e1c033';

function updateStatus (status) {
    const statusEl = document.getElementById('status');
    statusEl.innerHTML = status;
    console.log("##### upadateStatus: " + status);
}

async function loadContract() {
    return await new window.web3.eth.Contract(abi, contractAddress);
}

async function loadWeb3() {
    if (window.ethereum) {
        window.web3 = new Web3(window.ethereum);
        window.ethereum.enable();
    }
}

async function load() {
    await loadWeb3();
    window.contract = await loadContract();
    updateStatus('Ready!');
}

load();

var defaultAccount;

async function getCurrentAccount () {
    const accounts = await window.web3.eth.getAccounts();
    console.log("#################### getCurrentAccount() : " + accounts[0]);
    defaultAccount = accounts[0];
    web3.eth.defaultAccount = defaultAccount;
    //web3.eth.personal.unlockAccount(web3.eth.defaultAccount);
    console.log("web3.eth.defaultAccount:" + web3.eth.defaultAccount);
    
    return accounts[0];
}

async function waitForTxToBeMined (txHash) {
    let txReceipt
    while (!txReceipt) {
        try {
            txReceipt = await window.web3.eth.getTransactionReceipt(txHash)
        } catch (err) {
        	updateStatus("failure: " + err);
            return;
        }
    }
    updateStatus("Success: transaction confirmed!");
}

var clientNonce = 0;

function getUserNonce () {
	clientNonce = clientNonce + 1;
	return clientNonce;
}

// recipient is the address that should be paid.
// amount, in wei, specifies how much ether should be sent.
// nonce can be any unique number, used to prevent replay attacks.
// contractAddress is used to prevent cross-contract replay attacks.
function calculateHash (recipient, amount, userNonce, addr) {
	/*
	var hash = "0x" + web3.utils.soliditySha3(
    	["address", "uint256", "uint256", "address"],
    	[recipient, amount, userNonce, contractAddr]).toString("hex");
    	*/
    var hash = web3.utils.soliditySha3(recipient, amount, userNonce, addr);
	console.log("#################### calculateHash() ");
	console.log("recipient:" + recipient + " amount:"  + amount + " userNonce:" + userNonce + " addr:" + addr);
	console.log("hash: ", hash);
	return hash;
}

// Move this to node.js server side
async function getServerSign (hash) {

	var passwd = "My Server Secret Password";
	console.log("#################### getServerSign() : ownerAddress:" + ownerAddress + " defaultAccount:" + defaultAccount);
	//var addr = web3.eth.defaultAccount;
	var addr;
	addr = ownerAddress;
	addr = defaultAccount; //works

	console.log("hash:" + hash + " addr:" + addr + " passwd:" + passwd);

	var signature = await web3.eth.personal.sign(hash, addr, passwd);
    console.log("#################### sign =" + signature);

    return signature;
}

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function redeemPointsAsync (points) {
    updateStatus(`Redeeming with ${points}`);
    const account = await getCurrentAccount();
    const gasLimit = '99999';

    var userNonce = getUserNonce();

    var hash = calculateHash(account, points, userNonce, contractAddress);

    var sig = await getServerSign(hash);

    var signing_address = await web3.eth.personal.ecRecover(hash, sig);
    console.log("verify: signing_address: ", signing_address);

    console.log("sig: ", sig);
    console.log("sig len (string): " + sig.length);

/*
    var bytes = web3.utils.asciiToHex(sig);
    console.log("sig len (bytes): " + bytes.length);
    console.log(" $$$$$ Args to contract: points:" + points + " nonce:" + userNonce + " sig:" + bytes);
*/
    window.contract.methods.withdrawPoints(points, 
    	userNonce, 
    	sig)
    	.send({ from: account, gas: gasLimit })
    	.on ('transactionHash', function(transactionHash){
            console.log('Transaction submitted with txHash:' + transactionHash);
            updateStatus('Transaction submitted with txHash:' + transactionHash);
            waitForTxToBeMined(transactionHash);
        })
        .catch(console.error);
}

function points2Coins (points) {
	// formula to convert points to GC coins
	// Currently one point = one coin.
	return points;
}

function redeemPoints (points) {

	if (points <= 0) {
	    return;
	}
  	console.log("#################### redeemPoints() Points: " + points);

	redeemPointsAsync(points2Coins(points));

	return;
}

// =============================================================================
//                                      UI 
// =============================================================================


$("#redeem").click(function() {
  redeemPoints($("#points").val());
  //window.location.reload(true); // refreshes the page after
});

// This is a log function, provided if you want to display things to the page instead of the JavaScript console
// Pass in a discription of what you're printing, and then the object to print
function log(description, obj) {
	$("#log").html($("#log").html() + description + ": " + JSON.stringify(obj, null, 2) + "\n\n");
}

