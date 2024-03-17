#ifndef USER_H
#define USER_H
#define TELEPHONE_MAX_LENGTH 30
#define EMAIL_MAX_LENGTH 255
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// User role definition

typedef enum {
    ADMIN,
    EDITOR,
    VIEWER
} Role;

// User structure definitions

typedef struct {
    int userID;
    char firstName[100];
    char lastName[100];
    Role userRole;
    char emailAddress[EMAIL_MAX_LENGTH];// Email address
    char telephone[TELEPHONE_MAX_LENGTH];// Telephone
    // Password??
    // Account creation date
    // Date of last update
    // Free Text Notes
} User;


// Function prototypes
void getString(char *buffer, size_t bufferSize);
void clearInputBuffer();

bool isValidEmail(const char *email);
bool isValidTelephone(const char *telephone);
Role getRoleFromInput();
void getUserData();
void displayUserData(const User* user);
void displayAllUsers();
void updateUser(int id, User *user);
void promptForUser();
void findAndDisplayUser(const char* userInput);
void saveUser(const User* user);
bool parseLine(const char* line, User* user, const char* userInput);
bool parseLineForDisplay(const char* line, User* user);
int getNextUserId();


#endif
