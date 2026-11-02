# Banking-management-system
# Bank Management System (C)

A simple console-based banking management system written in C. It includes 10 sample accounts numbered 1001 to 1010, each with a name, PIN, and starting balance. Users log in with an account number and PIN, then choose from a menu to check balance, withdraw, deposit, or transfer money. Withdrawals and transfers ask for confirmation and are blocked if the balance is insufficient. During transfers, the recipient's name is shown before confirming. Balances are saved to accounts.txt, so they persist between runs. To use it, compile with gcc bank.c -o bank, then run ./bank. Delete accounts.txt to reset balances to default.

