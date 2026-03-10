#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "Transaction.h"
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <memory>

/**
 * BankAccount class to manage bank accounts with name, number, and balance.
 * Implements the Rule of Three due to dynamic memory allocation for name.
 */
class BankAccount {

public:
    // Default constructor
    BankAccount();

    // Parameterized constructor
    BankAccount(std::string accountNumber, std::string accountHolderName, double balance);

    /* This function will allow deposits to perform true if successful. If the amount is invalid, it will return false. */
    bool Deposit(double amount) {
        if (amount > 0) {
            balance += amount;

            // This creates a current time for the timestamp
            std::time_t now = std::time(nullptr);
            std::string timeString = std::ctime(&now);

            // This is the Transaction object
            Transaction newTrans;
            newTrans.type = "Deposit";
            newTrans.amount = amount;
            newTrans.timeStamp = timeString;

            // This push backs to the transaction history vector
            transactionHistory.push_back(newTrans);
            return true;
        }
        return false;
    };

    /* This bool function will allow withdraws to perform true if successful. If the amount is invalid or exceeds the balance, it will return false. */
    virtual bool Withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;

            // This creates a current time for the timestamp
            std::time_t now = std::time(nullptr);
            std::string timeString = std::ctime(&now);

            // This is the Transaction object
            Transaction newTrans;
            newTrans.type = "Withdrawal";
            newTrans.amount = amount;
            newTrans.timeStamp = timeString;

            // This push backs to the transaction history vector
            transactionHistory.push_back(newTrans);
            return true;
        }
        return false;
    };

    // Setters
    void SetBalance(double balance) {
        this->balance = balance;
    };
    void SetAccountNumber(std::string accountNumber) {
        this->accountNumber = accountNumber;
    };
    void SetAccountHolderName(std::string accountHolderName);

    // Getters
    double GetBalance() const {
        return balance;
    };
    std::string GetAccountNumber() const {
        return accountNumber;
    };
    std::string GetAccountHolderName() const;

    // Rule of Three: Copy Constructor
    BankAccount(const BankAccount& other);

    // Rule of Three: Assignment Operator
    BankAccount& operator=(const BankAccount& other);

    // Rule of Three: Destructor (virtual for proper derived class cleanup)
    virtual ~BankAccount();

    // Operator Overloading for balance manipulation
    BankAccount& operator+=(double amount);
    BankAccount& operator-=(double amount);

    // Operator Overloading for account comparison
    bool operator==(const BankAccount& other) const;
    bool operator<(const BankAccount& other) const;
    bool operator>(const BankAccount& other) const;

    // Static helper methods
    static void printAccount(const BankAccount& account);
    static std::unique_ptr<BankAccount> createAccountFromInput();

    void printHistory() const;

private:
    /* These are variables that the user can't see, but we have them here to manage account details */
    std::string accountNumber;
    char* accountHolderName;
    double balance;
    std::vector<Transaction> transactionHistory;
};

#endif
