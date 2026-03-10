/* Andrez De La Torre
* Mcsci-272
* 2-23-2026
* Lab Activity: Composition
*/


#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <memory>
#include <cstring>
#include "main.h"

// Helper function to find an account index by its account number
int findAccountIndex(const std::vector<std::unique_ptr<BankAccount>>& accounts, const std::string& accountNumber) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i]->GetAccountNumber() == accountNumber) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int main() {

    std::vector<std::unique_ptr<BankAccount>> accounts;

    int menuChoice;
    std::string userAccountNumber;
    std::string userAccountHolderName;
    double amount;

    do {
        std::cout << "\n================================" << std::endl;
        std::cout << "  BANK ACCOUNT MANAGEMENT SYSTEM" << std::endl;
        std::cout << "================================" << std::endl;
        std::cout << "1. Create a Checking account" << std::endl;
        std::cout << "2. Create a Savings account" << std::endl;
        std::cout << "3. Create base account (using static function)" << std::endl;
        std::cout << "4. Deposit money (using += operator)" << std::endl;
        std::cout << "5. Withdraw money (polymorphic: Checking applies fee)" << std::endl;
        std::cout << "6. Display account information" << std::endl;
        std::cout << "7. Compare two accounts (using ==, <, >)" << std::endl;
        std::cout << "8. Update account holder name" << std::endl;
        std::cout << "9. Calculate interest (Savings account)" << std::endl;
        std::cout << "10. Demo polymorphic withdraw" << std::endl;
        std::cout << "11. Print transaction history" << std::endl;
        std::cout << "12. Exit" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> menuChoice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            menuChoice = 0;
        }

        switch (menuChoice) {
            case 1: {
                
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;
                std::cin.ignore();
                std::cout << "Enter account holder name: ";
                std::getline(std::cin, userAccountHolderName);
                std::cout << "Enter initial balance: ";
                std::cin >> amount;
                double fee;
                std::cout << "Enter transaction fee per withdrawal: ";
                std::cin >> fee;

                if (amount >= 0 && fee >= 0) {
                    accounts.push_back(std::make_unique<CheckingAccount>(userAccountNumber, userAccountHolderName, amount, fee));
                    std::cout << "Checking account created successfully." << std::endl;
                } else {
                    std::cout << "Invalid balance or fee. Account not created." << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;
                std::cin.ignore();
                std::cout << "Enter account holder name: ";
                std::getline(std::cin, userAccountHolderName);
                std::cout << "Enter initial balance: ";
                std::cin >> amount;
                double rate;
                std::cout << "Enter interest rate (e.g. 0.05 for 5%): ";
                std::cin >> rate;

                if (amount >= 0 && rate >= 0) {
                    accounts.push_back(std::make_unique<SavingsAccount>(userAccountNumber, userAccountHolderName, amount, rate));
                    std::cout << "Savings account created successfully." << std::endl;
                } else {
                    std::cout << "Invalid balance or rate. Account not created." << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Creating account using static function..." << std::endl;
                std::unique_ptr<BankAccount> newAccount = BankAccount::createAccountFromInput();
                if (newAccount) {
                    std::cout << "\nAccount created successfully!" << std::endl;
                    BankAccount::printAccount(*newAccount);
                    accounts.push_back(std::move(newAccount));
                } else {
                    std::cout << "\nAccount creation failed." << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;

                int accountIndex = findAccountIndex(accounts, userAccountNumber);
                if (accountIndex >= 0) {
                    std::cout << "Enter amount to deposit: ";
                    std::cin >> amount;
                    if (amount > 0) {
                        *accounts[accountIndex] += amount;
                        std::cout << "Deposit of $" << amount << " successful using += operator." << std::endl;
                        std::cout << "New balance: $" << accounts[accountIndex]->GetBalance() << std::endl;
                    } else {
                        std::cout << "Invalid amount. Deposit must be positive." << std::endl;
                    }
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;

                int accountIndex = findAccountIndex(accounts, userAccountNumber);
                if (accountIndex >= 0) {
                    std::cout << "Current balance: $" << accounts[accountIndex]->GetBalance() << std::endl;
                    std::cout << "Enter amount to withdraw: ";
                    std::cin >> amount;

                    if (amount > 0) {
                        // Polymorphic withdraw: CheckingAccount applies fee, SavingsAccount uses base logic.
                        bool success = accounts[accountIndex]->Withdraw(amount);
                        if (success) {
                            std::cout << "Withdrawal successful." << std::endl;
                            std::cout << "New balance: $" << accounts[accountIndex]->GetBalance() << std::endl;
                        } else {
                            std::cout << "Insufficient funds or invalid amount. Withdrawal failed." << std::endl;
                        }
                    } else {
                        std::cout << "Invalid amount. Withdrawal must be positive." << std::endl;
                    }
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;

                int accountIndex = findAccountIndex(accounts, userAccountNumber);
                if (accountIndex >= 0) {
                    BankAccount::printAccount(*accounts[accountIndex]);
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 7: {
                std::cout << "--------------------------------" << std::endl;
                if (accounts.size() < 2) {
                    std::cout << "Need at least 2 accounts to compare." << std::endl;
                    std::cout << "Current number of accounts: " << accounts.size() << std::endl;
                    break;
                }

                std::string firstAccountNumber, secondAccountNumber;
                std::cout << "Enter first account number: ";
                std::cin >> firstAccountNumber;
                std::cout << "Enter second account number: ";
                std::cin >> secondAccountNumber;

                int firstAccountIndex = findAccountIndex(accounts, firstAccountNumber);
                int secondAccountIndex = findAccountIndex(accounts, secondAccountNumber);

                if (firstAccountIndex >= 0 && secondAccountIndex >= 0) {
                    std::cout << "\n--- Comparison Results ---" << std::endl;

                    if (*accounts[firstAccountIndex] == *accounts[secondAccountIndex]) {
                        std::cout << "Accounts have the SAME account number." << std::endl;
                    } else {
                        std::cout << "Accounts have DIFFERENT account numbers." << std::endl;
                    }

                    std::cout << "\nBalance Comparison:" << std::endl;
                    if (*accounts[firstAccountIndex] > *accounts[secondAccountIndex]) {
                        std::cout << "Account " << firstAccountNumber << " has a HIGHER balance ($"
                                  << accounts[firstAccountIndex]->GetBalance() << " > $"
                                  << accounts[secondAccountIndex]->GetBalance() << ")" << std::endl;
                    } else if (*accounts[firstAccountIndex] < *accounts[secondAccountIndex]) {
                        std::cout << "Account " << secondAccountNumber << " has a HIGHER balance ($"
                                  << accounts[secondAccountIndex]->GetBalance() << " > $"
                                  << accounts[firstAccountIndex]->GetBalance() << ")" << std::endl;
                    } else {
                        std::cout << "Both accounts have the SAME balance ($"
                                  << accounts[firstAccountIndex]->GetBalance() << ")" << std::endl;
                    }
                } else {
                    std::cout << "One or both accounts not found." << std::endl;
                }
                break;
            }
            case 8: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;

                int accountIndex = findAccountIndex(accounts, userAccountNumber);
                if (accountIndex >= 0) {
                    std::cout << "Current holder name: " << accounts[accountIndex]->GetAccountHolderName() << std::endl;
                    std::cout << "Enter new account holder name: ";
                    std::cin.ignore();
                    std::getline(std::cin, userAccountHolderName);
                    accounts[accountIndex]->SetAccountHolderName(userAccountHolderName);
                    std::cout << "Account holder name updated successfully." << std::endl;
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 9: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;

                int accountIndex = findAccountIndex(accounts, userAccountNumber);
                if (accountIndex >= 0) {
                    SavingsAccount* savings = dynamic_cast<SavingsAccount*>(accounts[accountIndex].get());
                    if (savings) {
                        double before = accounts[accountIndex]->GetBalance();
                        savings->calculateInterest();
                        double after = accounts[accountIndex]->GetBalance();
                        std::cout << "Interest applied. Balance: $" << before << " -> $" << after << std::endl;
                    } else {
                        std::cout << "Not a savings account." << std::endl;
                    }
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 10: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Demo: Polymorphic Withdraw" << std::endl;
                BankAccount* checkingPtr = nullptr;
                BankAccount* savingsPtr = nullptr;
                for (size_t i = 0; i < accounts.size(); ++i) {
                    if (!checkingPtr && dynamic_cast<CheckingAccount*>(accounts[i].get()))
                        checkingPtr = accounts[i].get();
                    if (!savingsPtr && dynamic_cast<SavingsAccount*>(accounts[i].get()))
                        savingsPtr = accounts[i].get();
                    if (checkingPtr && savingsPtr) break;
                }
                if (checkingPtr) {
                    std::cout << "Checking account - balance before: $" << checkingPtr->GetBalance();
                    checkingPtr->Withdraw(10.0);
                    std::cout << ", after withdrawing $10 (fee applies): $" << checkingPtr->GetBalance() << std::endl;
                } else {
                    std::cout << "No Checking account in list. Create one to see fee applied." << std::endl;
                }
                if (savingsPtr) {
                    std::cout << "Savings account - balance before: $" << savingsPtr->GetBalance();
                    savingsPtr->Withdraw(10.0);
                    std::cout << ", after withdrawing $10 (no fee): $" << savingsPtr->GetBalance() << std::endl;
                } else {
                    std::cout << "No Savings account in list. Create one to see base withdraw." << std::endl;
                }
                break;
            }
            case 11: {
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Enter account number: ";
                std::cin >> userAccountNumber;

                int accountIndex = findAccountIndex(accounts, userAccountNumber);
                if (accountIndex >= 0) {
                    // Call your new function!
                    accounts[accountIndex]->printHistory();
                } else {
                    std::cout << "Account not found." << std::endl;
                }
                break;
            }
            case 12:
                std::cout << "--------------------------------" << std::endl;
                std::cout << "Thank you for using the Bank Account Management System!" << std::endl;
                std::cout << "Exiting program..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please select 1-12." << std::endl;
                break;

        }

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (menuChoice != 12);

    return 0;
}