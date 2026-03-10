#include "SavingsAccount.h"

void SavingsAccount::calculateInterest() {
    double interest = GetBalance() * interestRate;
    Deposit(interest);
}
