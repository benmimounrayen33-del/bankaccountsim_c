#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bank.h"

int main() {
    FILE *bankFile = fopen("accounts.dat", "r+b");
    if (bankFile == NULL) {
        bankFile = fopen("accounts.dat", "w+b");
        if (bankFile == NULL) {
            perror("Failed to open bank file");
            return EXIT_FAILURE;
        }
    }

    int choice;
    char accountNumber[20], fromAccount[20], toAccount[20];

    do {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. View Account Details\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Transfer Money\n");
        printf("6. Delete Account\n");
        printf("7. Check Balance\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(bankFile);
                break;
            case 2:
                viewAccountDetails(bankFile);
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%s", accountNumber);
                depositmoney(bankFile, accountNumber);
                break;
            case 4:
                printf("Enter account number: ");
                scanf("%s", accountNumber);
                withdrawmoney(bankFile, accountNumber);
                break;
            case 5:
                printf("Enter from account number: ");
                scanf("%s", fromAccount);
                printf("Enter to account number: ");
                scanf("%s", toAccount);
                transfermoney(bankFile, fromAccount, toAccount);
                break;
            case 6:
                printf("Enter account number: ");
                scanf("%s", accountNumber);
                deleteAccount(bankFile, accountNumber);
                break;
            case 7:
                printf("Enter account number: ");
                scanf("%s", accountNumber);
                checkBalance(bankFile, accountNumber);
                break;
            case 8:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 8);

    fclose(bankFile);
    return EXIT_SUCCESS;
}