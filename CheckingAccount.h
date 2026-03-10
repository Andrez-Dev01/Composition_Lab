#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include "BankAccount.h"

class CheckingAccount : public BankAccount {
private:
    double transactionFee;

public:
    // Constructor calls the base class default constructor and initializes the transaction fee.
    CheckingAccount(std::string accountName, double fee)
        : BankAccount() {
        transactionFee = fee;
        SetAccountHolderName(accountName);
    }

    // Constructor with full account data (for menu creation).
    CheckingAccount(std::string accountNumber, std::string accountHolderName, double balance, double fee)
        : BankAccount(accountNumber, accountHolderName, balance), transactionFee(fee) {
    }

    bool Withdraw(double amount) override;
};

#endif
