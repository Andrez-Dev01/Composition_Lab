#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>

struct Transaction {
    std::string type;
    double amount;
    std::string timeStamp;
};

#endif