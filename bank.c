#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bank.h"

struct Account {
    char accountNumber[20];
    char name[100];
    double balance;
};
void createAccount(FILE *file) {
    struct Account newAccount;
    printf("Enter account number: ");
    scanf("%s", newAccount.accountNumber);
    printf("Enter name: ");
    scanf(" %[^\n]", newAccount.name);
    newAccount.balance = 0.0;

    fseek(file, 0, SEEK_END);
    fwrite(&newAccount, sizeof(struct Account), 1, file);
    printf("Account created successfully!\n");
}
void viewAccountDetails(FILE *file) {
    struct Account account;
    fseek(file, 0, SEEK_SET);
    printf("Account Details:\n");
    while (fread(&account, sizeof(struct Account), 1, file)) {
        printf("Account Number: %s, Name: %s, Balance: %.2f\n", account.accountNumber, account.name, account.balance);
    }
}
void depositmoney(FILE *file, const char *accountNumber) {
    struct Account account;
    double amount;
    bool found = false;

    fseek(file, 0, SEEK_SET);
    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (strcmp(account.accountNumber, accountNumber) == 0) {
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);
            account.balance += amount;
            fseek(file, -sizeof(struct Account), SEEK_CUR);
            fwrite(&account, sizeof(struct Account), 1, file);
            printf("Deposited %.2f to account %s. New balance: %.2f\n", amount, accountNumber, account.balance);
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}
void withdrawmoney(FILE *file, const char *accountNumber) {
    struct Account account;
    double amount;
    bool found = false;

    fseek(file, 0, SEEK_SET);
    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (strcmp(account.accountNumber, accountNumber) == 0) {
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);
            if (amount > account.balance) {
                printf("Insufficient balance!\n");
            } else {
                account.balance -= amount;
                fseek(file, -sizeof(struct Account), SEEK_CUR);
                fwrite(&account, sizeof(struct Account), 1, file);
                printf("Withdrew %.2f from account %s. New balance: %.2f\n", amount, accountNumber, account.balance);
            }
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}
void transfermoney(FILE *file, const char *fromAccount, const char *toAccount) {
    struct Account accountFrom, accountTo, tmp;
    double amount;
    bool foundFrom = false, foundTo = false;
    long posFrom = -1, posTo = -1;

    /* Find both accounts and remember their file offsets */
    fseek(file, 0, SEEK_SET);
    while (fread(&tmp, sizeof(struct Account), 1, file)) {
        if (!foundFrom && strcmp(tmp.accountNumber, fromAccount) == 0) {
            accountFrom = tmp;
            posFrom = ftell(file) - sizeof(struct Account);
            foundFrom = true;
        }
        if (!foundTo && strcmp(tmp.accountNumber, toAccount) == 0) {
            accountTo = tmp;
            posTo = ftell(file) - sizeof(struct Account);
            foundTo = true;
        }
        if (foundFrom && foundTo) break;
    }

    if (!foundFrom || !foundTo) {
        printf("One or both accounts not found!\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);

    if (amount > accountFrom.balance) {
        printf("Insufficient balance in the source account!\n");
        return;
    }

    /* Modify balances in memory */
    accountFrom.balance -= amount;
    accountTo.balance += amount;

    /* Write updated accountFrom at its original offset */
    if (posFrom >= 0) {
        fseek(file, posFrom, SEEK_SET);
        fwrite(&accountFrom, sizeof(struct Account), 1, file);
        fflush(file);
    }
    /* Write updated accountTo at its original offset */
    if (posTo >= 0) {
        fseek(file, posTo, SEEK_SET);
        fwrite(&accountTo, sizeof(struct Account), 1, file);
        fflush(file);
    }

    printf("Transferred %.2f from account %s to account %s.\n", amount, fromAccount, toAccount);
}
void deleteAccount(FILE *file, const char *accountNumber) {
    struct Account account;
    struct Account *buffer = NULL;
    size_t count = 0, keep = 0;
    bool found = false;

    /* Read all accounts into memory */
    fseek(file, 0, SEEK_SET);
    while (fread(&account, sizeof(struct Account), 1, file)) {
        struct Account *tmp = realloc(buffer, (count + 1) * sizeof(struct Account));
        if (!tmp) {
            free(buffer);
            printf("Memory allocation failed while deleting account.\n");
            return;
        }
        buffer = tmp;
        buffer[count++] = account;
    }

    /* Filter out the account to delete */
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(buffer[i].accountNumber, accountNumber) == 0) {
            found = true;
            continue;
        }
        buffer[keep++] = buffer[i];
    }

    /* Reopen (truncate) the same FILE* so caller's pointer stays valid */
    if (freopen("accounts.dat", "w+b", file) == NULL) {
        printf("Failed to reopen accounts file for writing.\n");
        free(buffer);
        return;
    }

    /* Write back kept accounts */
    if (keep > 0) {
        fwrite(buffer, sizeof(struct Account), keep, file);
        fflush(file);
    }

    free(buffer);

    if (found) {
        printf("Account %s deleted successfully!\n", accountNumber);
    } else {
        printf("Account not found!\n");
    }
}
void checkBalance(FILE *file, const char *accountNumber) {
    struct Account account;
    bool found = false;

    fseek(file, 0, SEEK_SET);
    while (fread(&account, sizeof(struct Account), 1, file)) {
        if (strcmp(account.accountNumber, accountNumber) == 0) {
            printf("Account Number: %s, Balance: %.2f\n", account.accountNumber, account.balance);
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Account not found!\n");
    }
}
void savetasks(FILE *file) {
    // Implementation for saving tasks if needed

}