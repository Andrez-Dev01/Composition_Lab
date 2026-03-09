# Bank Account Management System

A C++ class for representing a book in a library system.

## Data Dictionary

| Attribute          | Data Type     | Description                         |
|--------------------|---------------|-------------------------------------|
| `accountNumber`    | `std::string` | Unique account identifier.          |
| `accountHolderName`| `std::string` | Name of the account holder.         |
| `balance`          | `double`      | Current account balance.            |

## Methods List

| Method Signature | Return Type   | Description                                  |
|------------------|---------------|----------------------------------------------|
| `BankAccount()`  | (Constructor) | Default constructor.                         |
| `BankAccount(accountNumber, accountHolderName, balance)` | (Constructor) | Parameterized constructor.        |
| `GetAccountNumber() const`    | `std::string` | Gets the account number.              |
| `GetAccountHolderName() const`| `std::string` | Gets the account holder name.         |
| `GetBalance() const`          | `double`      | Gets the current balance.            |
| `SetAccountHolderName(name)`  | `void`        | Sets the account holder name.        |
| `SetAccountNumber(num)`       | `void`        | Sets the account number.             |
| `SetBalance(amount)`          | `void`        | Sets the balance.                    |
| `Deposit(amount)`             | `bool`        | Deposits money. Returns `true` if success.    |
| `Withdraw(amount)`            | `bool`        | Withdraws money. Returns `false` if insufficient funds. |

## Helper Function

| Function | Return Type | Description |
|----------|-------------|-------------|
| `findAccountIndex(accounts, accountNumber)` | `int` | Returns the index of the account in the vector, or -1 if not found. |

## Program Menu

1. **Create a new account** — Add an account with number, holder name, and initial balance.
2. **Deposit money** — Add funds to an existing account (validates positive amount).
3. **Withdraw money** — Remove funds from an account (validates positive amount and sufficient funds).
4. **Display account information** — Show account number, holder name, and balance.
5. **Exit** — Quit the program.

## Building and Running

```bash
g++ main.cpp -o main.exe

./main.exe
```
