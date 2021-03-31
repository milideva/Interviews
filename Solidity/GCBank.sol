//SPDX-License-Identifier: UNLICENSED

// Deploy with JavaScript VM @ https://remix.ethereum.org/

pragma solidity ^0.8.0;

import "https://github.com/OpenZeppelin/openzeppelin-contracts/blob/master/contracts/access/Ownable.sol";

contract Allowance is Ownable {
    
    event AllowanceChanged(address indexed _forWho, address indexed _byWhom, uint _oldAmount, uint _newAmount);
    
    function isOwner() internal view returns(bool) {
        return owner() == msg.sender;
    }
    
    // using SafeMath for uint; // Add this only if you are using solidity < 0.8!!! 
    // Note about SafeMath : In a recent update of Solidity the Integer type variables cannot overflow anymore.
    // https://docs.soliditylang.org/en/v0.8.0/080-breaking-changes.html#silent-changes-of-the-semantics
    mapping (address => uint) public allowance;

    function setAllowance(address _who, uint _amount) public onlyOwner {
        emit AllowanceChanged(_who, msg.sender, allowance[_who], _amount);
        allowance[_who] = _amount;
    }

    modifier ownerOrAllowed(uint _amount) {
        require(isOwner() || allowance[msg.sender] >= _amount, "You are not allowed OR amount > allowance!");
        _;
    }
    
    // An internal function to reduce the allowance to avoid repeated withdraw of allowance
    function reduceAllowance(address _who, uint _amount) internal ownerOrAllowed(_amount) {
        emit AllowanceChanged(_who, msg.sender, allowance[_who], allowance[_who] - _amount);
        allowance[_who] -= _amount;
    }
    
    function addAllowance (address _who, uint _amount) public onlyOwner {
        emit AllowanceChanged(_who, msg.sender, allowance[_who], allowance[_who] + _amount);
        allowance[_who] += _amount;
    }
}

contract GCBank is Allowance  {
    
    event MoneySent(address indexed _beneficiary, uint _amount);
    
    event MoneyReceived(address indexed _from, uint _amount);
    
    constructor() payable {
    }
    
    function withdrawPoints (uint256 _amount) public ownerOrAllowed  (_amount)  {
        require(_amount <= address(this).balance, "Contract doesn't have enough money");

        // Comment the following line if you do not want the allowance, also remove contract's "is Allowance" inheritance
        reduceAllowance(msg.sender, _amount);  // calls ownerOrAllowed which checks for allowance > _amount

        address payable _to = payable(msg.sender);
        _to.transfer(_amount);
        emit MoneySent(_to, _amount);
    }
    
    function renounceOwnership() public view  override onlyOwner  {
        revert("Can't renounceOwnership here"); //not possible with this smart contract
    }
    
    function receive() external payable {
        emit MoneyReceived(msg.sender, msg.value);
    }
}

contract GCBankWithoutAllowance {
    
    event MoneySent(address indexed _beneficiary, uint _amount);
    
    event MoneyReceived(address indexed _from, uint _amount);

    constructor() payable {
    }
    
    function withdrawPoints (uint256 _amount) public {
        require(_amount <= address(this).balance, "Contract doesn't have enough money");

        address payable _to = payable(msg.sender);
        _to.transfer(_amount);
        emit MoneySent(_to, _amount);
    }
    
    function receive() external payable {
        emit MoneyReceived(msg.sender, msg.value);
    }
}