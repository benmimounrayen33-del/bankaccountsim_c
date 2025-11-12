#ifndef BANK_H
#define BANK_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Function declarations (prototypes)
void createAccount(FILE *file);
void viewAccountDetails(FILE *file);
void depositmoney(FILE *file, const char *accountNumber);
void withdrawmoney(FILE *file, const char *accountNumber);
void transfermoney(FILE *fil, const char *fromAccount, const char *toAccount);
void deleteAccount(FILE *file, const char *accountNumber);
void checkBalance(FILE *file, const char *accountNumber);
void savetasks(FILE *file);






#endif