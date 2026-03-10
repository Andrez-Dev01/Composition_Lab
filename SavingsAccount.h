#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include "BankAccount.h"

class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(std::string accountNumber, std::string accountHolderName, double balance, double rate)
        : BankAccount(accountNumber, accountHolderName, balance) {
        interestRate = rate;
    }

    void calculateInterest();
};

#endif
