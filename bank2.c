
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define FILE_NAME "accounts.txt"

int accNo[N] = {1001,1002,1003,1004,1005,
                1006,1007,1008,1009,1010};

char name[N][20] = {"Aman","Riya","Karan","Simran","Rohit",
                    "Neha","Arjun","Pooja","Vikram","Anjali"};

int pin[N] = {1111,2222,3333,4444,5555,
              6666,7777,8888,9999,1234};

float balance[N] = {5000,12000,800,25000,15000,
                    300,9500,40000,2500,7000};


// Clear invalid input
void clearInput
()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}


// Read integer safely
int readInt(char message[])
{
    int value;

    while (1)
    {
        printf("%s", message);

        if (scanf("%d", &value) == 1)
        {
            clearInput();
            return value;
        }

        printf("Invalid input! Enter a number.\n");
        clearInput();
    }
}


// Read amount safely
float readFloat(char message[])
{
    float value;

    while (1)
    {
        printf("%s", message);

        if (scanf("%f", &value) == 1)
        {
            clearInput();
            return value;
        }

        printf("Invalid input! Enter a valid amount.\n");
        clearInput();
    }
}


// Load saved balances
void loadData()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL)
        return;

    float temp[N];
    int i;

    for (i = 0; i < N; i++)
    {
        if (fscanf(fp, "%f", &temp[i]) != 1 ||
            !(temp[i] >= 0))
        {
            printf("Invalid data file. Using default balances.\n");
            fclose(fp);
            return;
        }
    }

    for (i = 0; i < N; i++)
        balance[i] = temp[i];

    fclose(fp);
}


// Save balances
int saveData()
{
    FILE *fp = fopen(FILE_NAME, "w");

    if (fp == NULL)
    {
        printf("Error saving data!\n");
        return 0;
    }

    int i;

    for (i = 0; i < N; i++)
    {
        if (fprintf(fp, "%.2f\n", balance[i]) < 0)
        {
            fclose(fp);
            printf("Error saving data!\n");
            return 0;
        }
    }

    if (fclose(fp) != 0)
    {
        printf("Error closing data file!\n");
        return 0;
    }

    return 1;
}


int main()
{
    int enteredAcc, enteredPin;
    int i, idx, choice, target, t, confirm;
    float amount;

    int running = 1;

    loadData();

    while (running)
    {
        printf("\n========== BANKING SYSTEM ==========\n");

        enteredAcc = readInt("Enter account number (1001-1010): ");

        idx = -1;

        for (i = 0; i < N; i++)
        {
            if (accNo[i] == enteredAcc)
            {
                idx = i;
                break;
            }
        }

        if (idx == -1)
        {
            printf("Account not found!\n");
            continue;
        }

        enteredPin = readInt("Enter PIN: ");

        if (enteredPin != pin[idx])
        {
            printf("Wrong PIN!\n");
            continue;
        }

        printf("\nWelcome, %s!\n", name[idx]);

        // Account menu
        while (1)
        {
            printf("\n========== MENU ==========\n");
            printf("1. Check Balance\n");
            printf("2. Withdraw Money\n");
            printf("3. Deposit Money\n");
            printf("4. Transfer Money\n");
            printf("5. Logout\n");
            printf("6. Exit Program\n");

            choice = readInt("Enter your choice: ");

            // Check balance
            if (choice == 1)
            {
                printf("Your balance: Rs. %.2f\n", balance[idx]);
            }

            // Withdraw
            else if (choice == 2)
            {
                amount = readFloat("Enter withdrawal amount: ");

                if (!(amount > 0) || amount > balance[idx])
                {
                    printf("Payment not possible!\n");
                }
                else
                {
                    confirm = readInt("Are you confirmed? (1=Yes, 0=No): ");

                    if (confirm == 1)
                    {
                        balance[idx] -= amount;

                        if (saveData())
                            printf("Withdrawal successful!\nNew balance: Rs. %.2f\n", balance[idx]);
                        else
                        {
                            balance[idx] += amount;
                            printf("Transaction cancelled. Balance restored.\n");
                        }
                    }
                    else
                    {
                        printf("Withdrawal cancelled.\n");
                    }
                }
            }

            // Deposit
            else if (choice == 3)
            {
                amount = readFloat("Enter deposit amount: ");

                if (!(amount > 0))
                {
                    printf("Invalid amount!\n");
                }
                else
                {
                    balance[idx] += amount;

                    if (saveData())
                        printf("Deposit successful!\nNew balance: Rs. %.2f\n", balance[idx]);
                    else
                    {
                        balance[idx] -= amount;
                        printf("Deposit cancelled. Balance restored.\n");
                    }
                }
            }

            // Transfer
            else if (choice == 4)
            {
                target = readInt("Enter receiver account number: ");

                t = -1;

                for (i = 0; i < N; i++)
                {
                    if (accNo[i] == target)
                    {
                        t = i;
                        break;
                    }
                }

                if (t == -1)
                {
                    printf("Account not found!\n");
                }
                else if (t == idx)
                {
                    printf("You cannot transfer to your own account!\n");
                }
                else
                {
                    printf("Receiver name: %s\n", name[t]);

                    amount = readFloat("Enter transfer amount: ");

                    if (!(amount > 0) || amount > balance[idx])
                    {
                        printf("Payment not possible!\n");
                    }
                    else
                    {
                        confirm = readInt("Are you confirmed? (1=Yes, 0=No): ");

                        if (confirm == 1)
                        {
                            balance[idx] -= amount;
                            balance[t] += amount;

                            if (saveData())
                            {
                                printf("Transfer successful!\n");
                                printf("New balance: Rs. %.2f\n", balance[idx]);
                            }
                            else
                            {
                                balance[idx] += amount;
                                balance[t] -= amount;
                                printf("Transfer cancelled. Balances restored.\n");
                            }
                        }
                        else
                        {
                            printf("Transfer cancelled.\n");
                        }
                    }
                }
            }

            // Logout
            else if (choice == 5)
            {
                printf("Logged out. Thank you, %s!\n", name[idx]);
                break;
            }

            // Exit
            else if (choice == 6)
            {
                printf("Thank you for using our banking system!\n");
                running = 0;
                break;
            }

            else
            {
                printf("Invalid choice! Try again.\n");
            }
        }
    }

    return 0;
}
