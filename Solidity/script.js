

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
		"inputs": [],
		"name": "receive",
		"outputs": [],
		"stateMutability": "payable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "uint256",
				"name": "_amount",
				"type": "uint256"
			}
		],
		"name": "withdrawPoints",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [],
		"name": "renounceOwnership",
		"outputs": [],
		"stateMutability": "view",
		"type": "function"
	}
]
; 

abiDecoder.addABI(abi);

// contract address
var contractAddress = '0xF483d691c6c832CC78611A12090E5246395cE175'; 

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

async function getCurrentAccount () {
    const accounts = await window.web3.eth.getAccounts();
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

async function redeemPointsAsync (points) {
    updateStatus(`Redeeming with ${points}`);
    const account = await getCurrentAccount();
    //await window.contract.methods.withdrawPoints(points).send({ from: account });
    const gasLimit = '22222';
    window.contract.methods.withdrawPoints(points).send({ from: account, gas: gasLimit })
    	.on ('transactionHash', function(transactionHash){
            console.log('Transaction submitted with txHash:' + transactionHash);
            updateStatus('Transaction submitted with txHash:' + transactionHash);
            waitForTxToBeMined(transactionHash);
        })
        .catch(console.error);
}

function redeemPoints (points) {

	if (points <= 0) {
	    return;
	}

  	console.log("#################### redeemPoints() Points: " + points);
	redeemPointsAsync(points);
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

