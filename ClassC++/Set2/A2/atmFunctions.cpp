/*
 * CSCI 200 - Spring 2026
 * A2 - Automated Teller Machine
 * Implementation file
 */

#include <iostream>
#include "atmFunctions.h"
using namespace std;

void boot_machine() {
    int dollars = 0;
    int cents = 0;
    
    while (true) {
        display_options();
        int choice = input_choice();
        
        if (choice == 1) {
            show_me_the_money(&dollars, &cents);
        } else if (choice == 2) {
            make_a_deposit(&dollars, &cents);
        } else if (choice == 3) {
            make_a_withdrawal(&dollars, &cents);
        } else if (choice == 4) {
            cout << "Thanks for coming!" << endl;
            break;
        } else {
            cout << "It is not clear what you are trying to do." << endl << endl;
        }
    }
}

void display_options() {
    cout << "Welcome to the Infinite ATM!" << endl;
    cout << "Please make a selection:" << endl;
    cout << "(1) Print Current Balance" << endl;
    cout << "(2) Deposit" << endl;
    cout << "(3) Withdraw" << endl;
    cout << "(4) Quit" << endl;
    cout << "Choice: ";
}

int input_choice() {
    int choice;
    cin >> choice;
    return choice;
}

void show_me_the_money(int* dollars, int* cents) {
    cout << "You currently have $" << *dollars << "." 
         << ( *cents < 10 ? "0" : "") << *cents << "." << endl << endl;
}

void make_a_deposit(int* dollars, int* cents) {
    int deposit_dollars, deposit_cents;
    cout << "How many dollars would you like to deposit? ";
    cin >> deposit_dollars;
    cout << "How many cents would you like to deposit? ";
    cin >> deposit_cents;
    
    if (deposit_dollars > 0 || deposit_cents > 0) {
        *dollars += deposit_dollars;
        *cents += deposit_cents;
        
        // Handle cents overflow
        if (*cents >= 100) {
            *dollars += *cents / 100;
            *cents %= 100;
        }
        
        cout << "Thank you for depositing $" << deposit_dollars << "." 
             << (deposit_cents < 10 ? "0" : "") << deposit_cents << "!" << endl << endl;
    } else {
        cout << "It seems you are trying to make a withdrawal. Perhaps try that instead?" << endl << endl;
    }
}

void make_a_withdrawal(int* dollars, int* cents) {
    int withdraw_dollars, withdraw_cents;
    cout << "How many dollars do you wish to withdraw? ";
    cin >> withdraw_dollars;
    cout << "How many cents do you wish to withdraw? ";
    cin >> withdraw_cents;
    
    if (withdraw_dollars > 0 || withdraw_cents > 0) {
        int total_balance_cents = (*dollars * 100) + *cents;
        int withdraw_total_cents = (withdraw_dollars * 100) + withdraw_cents;
        
        if (total_balance_cents >= withdraw_total_cents) {
            *dollars -= withdraw_dollars;
            *cents -= withdraw_cents;
            
            // Handle negative cents (borrow from dollars)
            if (*cents < 0) {
                *dollars -= 1;
                *cents += 100;
            }
            
            cout << "Here is your $" << withdraw_dollars << "." 
                 << (withdraw_cents < 10 ? "0" : "") << withdraw_cents << "!" << endl << endl;
        } else {
            cout << "We are sorry, you have insufficient reserves in your treasure store." << endl << endl;
        }
    } else {
        cout << "We are sorry, we are not in the business of giving away money." << endl << endl;
    }
}
