#include "CheckingAccount.h"

bool CheckingAccount::Withdraw(double amount) {
    if (amount > 0 && GetBalance() >= amount + transactionFee) {
        SetBalance(GetBalance() - amount - transactionFee);
        return true;
    }
    return false;
}
