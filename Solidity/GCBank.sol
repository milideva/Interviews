//SPDX-License-Identifier: UNLICENSED

pragma solidity ^0.8.0;

import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/master/contracts/access/Ownable.sol";

contract GCBank is Ownable {
    
    event MoneySent(address indexed _beneficiary, uint _amount);
    
    event MoneyReceived(address indexed _from, uint _amount);
    
    constructor() payable {
    }
    
    mapping(address => mapping(uint256 => bool)) usedNonces;

    function withdrawPoints (uint256 _amount, uint256 _nonce, bytes calldata _sig) public {
        require(_amount <= address(this).balance, "Contract doesn't have enough money");
        require (!usedNonces[msg.sender][_nonce]);

        // This recreates the message that was signed on the client.
        bytes32 message = prefixed(keccak256(abi.encodePacked(msg.sender, _amount, _nonce, address(this))));

        require (recoverSigner(message, _sig) == owner());
        // Set the nonce first, before transfer
        usedNonces[msg.sender][_nonce] = true;

        address payable _to = payable(msg.sender);
        _to.transfer(_amount);
        
        emit MoneySent(_to, _amount);
    }
    
    function receive() external payable {
        emit MoneyReceived(msg.sender, msg.value);
    }
    
    function renounceOwnership () public pure override {
        revert("Can't renounceOwnership here"); //not possible with this smart contract
    }
    
    function getContractAddress ()  public view returns(address){
        return address(this);
    }
    
    function getContractBalance () public view returns(uint256){
        return address(this).balance;
    }
    
    function getOwnerBalance () public view returns(uint256){
        return owner().balance;
    }
    
    // Signature methods

    function splitSignature (bytes memory sig)
        internal
        pure
        returns (uint8, bytes32, bytes32)
    {
        require(sig.length == 65);

        bytes32 r;
        bytes32 s;
        uint8 v;

        assembly {
            // first 32 bytes, after the length prefix
            r := mload(add(sig, 32))
            // second 32 bytes
            s := mload(add(sig, 64))
            // final byte (first byte of the next 32 bytes)
            v := byte(0, mload(add(sig, 96)))
        }

        return (v, r, s);
    }
    
    function recoverSigner (bytes32 message, bytes calldata sig)
        internal
        pure
        returns (address)
    {
        uint8 v;
        bytes32 r;
        bytes32 s;

        (v, r, s) = splitSignature(sig);

        return ecrecover(message, v, r, s);
    }

    function prefixed (bytes32 hash) 
        internal 
        pure 
        returns (bytes32) 
    {
        return keccak256(abi.encodePacked("\x19Ethereum Signed Message:\n32", hash));
    }
}
