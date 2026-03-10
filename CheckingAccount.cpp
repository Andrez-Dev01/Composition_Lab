#include "CheckingAccount.h"

bool CheckingAccount::Withdraw(double amount) {
    if (amount > 0 && GetBalance() >= amount + transactionFee) {
        // Use the base class Withdraw to log the main amount and the fee as a single withdrawal.
        // This ensures the transaction is logged to the history vector.
        return BankAccount::Withdraw(amount + transactionFee);
    }
    return false;
}
