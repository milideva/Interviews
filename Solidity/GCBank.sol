
//SPDX-License-Identifier: UNLICENSED

pragma solidity ^0.8.0;

import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/master/contracts/access/Ownable.sol";

contract GCBank is Ownable {
    /* 
    address public owner;
    
    constructor () public {
        owner = msg.sender;
    } 
    
    modifier onlyOwner () {
        require(msg.sender == owner, "You are not allowed, only owner allowed to withdraw");
        _;
    }
    */
    
    // TO DO. Safemath, events, restructure code to separate allowance as a contract from Bank as another contract 
    function isOwner() internal view returns (bool) {
        return owner() == msg.sender;
    }
    
    mapping (address => uint) public allowance;

    function setAllowance (address _who, uint _amount) public onlyOwner {
        allowance[_who] = _amount;    
    }
    
    function addAllowance (address _who, uint _amount) public onlyOwner {
        allowance[_who] += _amount;    
    }
    
    modifier ownerOrAllowed (uint _amount) {
        require(isOwner() || allowance[msg.sender] >= _amount, "You are not allowed OR amount > allowance!");
        _;
    }
    
    // An internal function to reduce the allowance to avoid repeated withdraw of allowance
    function reduceAllowance (address _who, uint _amount) internal ownerOrAllowed (_amount) {
        allowance[_who] -= _amount;
    }
    
    function withdraw (address payable _to, uint256 _amount) public ownerOrAllowed (_amount) {
        require(_amount <= address(this).balance, "Contract doesn't have enough money");
        reduceAllowance(msg.sender, _amount);
        _to.transfer(_amount);
    }
    
    function receive() external payable {

    }
}