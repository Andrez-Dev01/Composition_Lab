cmake_minimum_required(VERSION 3.14)
project(Objects_and_Classes_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(Objects_and_Classes_1
        main.cpp
        main.h
        Transaction.h
        BankAccount.cpp
        BankAccount.h
        CheckingAccount.cpp
        CheckingAccount.h
        SavingsAccount.cpp
        SavingsAccount.h)
