#include "BankAccount.h"
#include <cstring>

// Default constructor
BankAccount::BankAccount() : accountNumber(""), accountHolderName(nullptr), balance(0.0) {}

// Parameterized constructor
BankAccount::BankAccount(std::string accountNumber, std::string accountHolderName, double balance)
    : accountNumber(accountNumber), balance(balance) {
    this->accountHolderName = new char[accountHolderName.length() + 1];
    std::strcpy(this->accountHolderName, accountHolderName.c_str());
}

// Setter for account holder name
void BankAccount::SetAccountHolderName(std::string accountHolderName) {
    delete[] this->accountHolderName;
    this->accountHolderName = new char[accountHolderName.length() + 1];
    std::strcpy(this->accountHolderName, accountHolderName.c_str());
}

// Getter for account holder name
std::string BankAccount::GetAccountHolderName() const {
    if (accountHolderName != nullptr) {
        return std::string(accountHolderName);
    }
    return "";
}

// Rule of Three: Copy Constructor
BankAccount::BankAccount(const BankAccount& other)
    : accountNumber(other.accountNumber), balance(other.balance) {
    if (other.accountHolderName != nullptr) {
        accountHolderName = new char[std::strlen(other.accountHolderName) + 1];
        std::strcpy(accountHolderName, other.accountHolderName);
    } else {
        accountHolderName = nullptr;
    }
}

// Rule of Three: Assignment Operator
BankAccount& BankAccount::operator=(const BankAccount& other) {
    if (this != &other) {
        delete[] accountHolderName;
        accountNumber = other.accountNumber;
        balance = other.balance;
        if (other.accountHolderName != nullptr) {
            accountHolderName = new char[std::strlen(other.accountHolderName) + 1];
            std::strcpy(accountHolderName, other.accountHolderName);
        } else {
            accountHolderName = nullptr;
        }
    }
    return *this;
}

// Rule of Three: Destructor
BankAccount::~BankAccount() {
    delete[] accountHolderName;
}

// Operator Overloading for balance manipulation
BankAccount& BankAccount::operator+=(double amount) {
    Deposit(amount);
    return *this;
}

BankAccount& BankAccount::operator-=(double amount) {
    Withdraw(amount);
    return *this;
}

// Operator Overloading for account comparison
bool BankAccount::operator==(const BankAccount& other) const {
    return balance == other.balance;
}

bool BankAccount::operator<(const BankAccount& other) const {
    return balance < other.balance;
}

bool BankAccount::operator>(const BankAccount& other) const {
    return balance > other.balance;
}

// Static helper methods
void BankAccount::printAccount(const BankAccount& account) {
    std::cout << "Account Number: " << account.GetAccountNumber() << std::endl;
    std::cout << "Account Holder: " << account.GetAccountHolderName() << std::endl;
    std::cout << "Balance: $" << account.GetBalance() << std::endl;
}

BankAccount BankAccount::createAccountFromInput() {
    std::string accountNumber, accountHolderName;
    double balance;
    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    std::cout << "Enter account holder name: ";
    std::cin.ignore();
    std::getline(std::cin, accountHolderName);
    std::cout << "Enter initial balance: ";
    std::cin >> balance;
    return BankAccount(accountNumber, accountHolderName, balance);
}
