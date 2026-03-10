#include "BankAccount.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"
#include <cstring>
#include <iostream>
#include <limits>

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
    : accountNumber(other.accountNumber), balance(other.balance),
      transactionHistory(other.transactionHistory) {
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
        transactionHistory = other.transactionHistory;
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

std::unique_ptr<BankAccount> BankAccount::createAccountFromInput() {
    std::string accountNumber, accountHolderName;
    double balance;
    int accountType;

    std::cout << "Select account type:\n";
    std::cout << "1. Base Account\n";
    std::cout << "2. Checking Account\n";
    std::cout << "3. Savings Account\n";
    std::cout << "Enter choice (1-3): ";

    if (!(std::cin >> accountType) || accountType < 1 || accountType > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid account type." << std::endl;
        return nullptr;
    }

    std::cout << "Enter account number: ";
    std::cin >> accountNumber;
    if (accountNumber.empty()) {
        std::cout << "Invalid account number." << std::endl;
        return nullptr;
    }

    std::cout << "Enter account holder name: ";
    std::cin.ignore();
    std::getline(std::cin, accountHolderName);
    if (accountHolderName.empty()) {
        std::cout << "Invalid account holder name." << std::endl;
        return nullptr;
    }

    std::cout << "Enter initial balance: ";
    if (!(std::cin >> balance) || balance < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid balance." << std::endl;
        return nullptr;
    }

    if (accountType == 1) {
        return std::make_unique<BankAccount>(accountNumber, accountHolderName, balance);
    } else if (accountType == 2) {
        double fee;
        std::cout << "Enter transaction fee: ";
        if (!(std::cin >> fee) || fee < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid transaction fee." << std::endl;
            return nullptr;
        }
        return std::make_unique<CheckingAccount>(accountNumber, accountHolderName, balance, fee);
    } else {
        double rate;
        std::cout << "Enter interest rate: ";
        if (!(std::cin >> rate) || rate < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid interest rate." << std::endl;
            return nullptr;
        }
        return std::make_unique<SavingsAccount>(accountNumber, accountHolderName, balance, rate);
    }
}

void BankAccount::printHistory() const {
    std::cout << "---Transaction History for Account" << GetAccountNumber() << "---" << std::endl;

    if (transactionHistory.empty()) {
        std::cout << "No transactions yet." << std::endl;
        return;
    }
    for (const Transaction& trans : transactionHistory) {
        std::cout << "[" << trans.timeStamp << "]"
        << trans.type << ": $"
        << trans.amount << std::endl;
    }
}
