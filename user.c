//
// Created by Kyle on 3/14/2024.
//
#include "user.h"
#include <stdio.h>
#include <stdlib.h>


#define MAX_LINE_LENGTH 256
const char *USER_FILE_PATH = "../resources/users.txt";


void getString(char *buffer, size_t bufferSize) {
    do {
        if (fgets(buffer, bufferSize, stdin) != NULL) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0'; // Remove newline character
            }
        } else {
            // If fgets fails, clear EOF or error and break the loop
            clearerr(stdin);
            buffer[0] = '\0'; // Ensure buffer is an empty string
            break;
        }
    } while (buffer[0] == '\0'); // If only a newline was read, try again
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
}


bool isValidEmail(const char *email) {
    const char *atSign = strchr(email, '@');
    const char *dot = strrchr(email, '.');
    return atSign && dot && atSign < dot && atSign != email && dot[1] != '\0';
}

bool isValidTelephone(const char *telephone) {
    // Simple validation: ensure all characters are digits or acceptable symbols (e.g., '+', '-', ' ')
    for (int i = 0; telephone[i]; i++) {
        if (!(isdigit(telephone[i]) || telephone[i] == '+' || telephone[i] == '-' || telephone[i] == ' ')) {
            return false;
        }
    }
    return true;
}

Role getRoleFromInput() {
    int roleInput;
    printf("Enter role (1 for Admin, 2 for Editor, 3 for Viewer): ");
    scanf("%d", &roleInput);
    while (getchar() != '\n'); // Clear the buffer

    // Validate the input and adjust to match enum values if starting from 1
    while (roleInput < 1 || roleInput > 3) {
        printf("Invalid role. Please enter 1 for Admin, 2 for Editor, or 3 for Viewer: ");
        scanf("%d", &roleInput);
        while (getchar() != '\n'); // Clear the buffer
    }

    return (Role) (roleInput - 1); // Adjust if your enum starts from 0 and input from 1
}


void updateUser(int id, User *user) {
    printf("Not implemented");
}

void getUserData() {

    User newUser;
    newUser.userID = getNextUserId();
    printf("Auto generated ID: %d\n", newUser.userID);

    // First Name
    printf("Enter first name: ");
    getString(newUser.firstName, sizeof(newUser.firstName));

    // Last Name
    printf("Enter last name: ");
    getString(newUser.lastName, sizeof(newUser.lastName));

    newUser.userRole = getRoleFromInput();


    // Use getString for Email and Telephone with validation loops
    do {
        printf("Enter email address: ");
        getString(newUser.emailAddress, sizeof(newUser.emailAddress));
        if (!isValidEmail(newUser.emailAddress)) {
            printf("Invalid email. Please include an '@' and a domain.\n");
        }

    } while (!isValidEmail(newUser.emailAddress));


    do {
        printf("Enter telephone: ");
        getString(newUser.telephone, sizeof(newUser.telephone));
    } while (!isValidTelephone(newUser.telephone));

    displayUserData(&newUser);
    char saveData;
    printf("Save user data? (y or n): ");
    scanf(" %c", &saveData);
    while (getchar() != '\n'); // Clear the input buffer to handle any extra characters

    saveData = tolower(saveData);

    if (saveData == 'y') {
        saveUser(&newUser);
        printf("User data saved.\n");
    } else {
        printf("User data not saved.\n");
    }
}

// Append the user's data to the 'database' (text file).
void saveUser(const User *user) {
    FILE *file = fopen(USER_FILE_PATH, "a"); // Open the file in append mode
    if (file != NULL) {
        fprintf(file, "%d,%s,%s,%d,%s,%s\n",
                user->userID,
                user->firstName,
                user->lastName,
                user->userRole,
                user->emailAddress,
                user->telephone);
        fclose(file);
    } else {
        printf("Failed to open file for writing.\n");
    }
}

int getNextUserId() {
    FILE *file = fopen(USER_FILE_PATH, "r");
    if (!file) {
        // If the file doesn't exist, start IDs at 1
        return 1;
    }

    int maxId = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        int userId;
        // Use sscanf to read the userID from the line string
        if (sscanf(line, "%d,", &userId) == 1) {
            if (userId > maxId) {
                maxId = userId;
            }
        }
    }

    fclose(file);
    return maxId + 1; // Increment the highest ID by 1
}

void promptForUser() {
    printf("User (name or ID): ");
    char input[100];
    getString(input, sizeof(input));  // Use getString to handle input

    findAndDisplayUser(input);
}

void displayUserData(const User *user) {
    printf("User ID: %d\n", user->userID);
    printf("First Name: %s\n", user->firstName);
    printf("Last Name: %s\n", user->lastName);

    // Convert the userRole enum to a readable string
    const char *roleString = "";
    switch (user->userRole) {
        case ADMIN:
            roleString = "Admin";
            break;
        case EDITOR:
            roleString = "Editor";
            break;
        case VIEWER:
            roleString = "Viewer";
            break;
        default:
            roleString = "Unknown";
    }
    printf("Role: %s\n", roleString);

    printf("Email Address: %s\n", user->emailAddress);
    printf("Telephone: %s\n", user->telephone);

}

void findAndDisplayUser(const char *userInput) {
    FILE *file = fopen(USER_FILE_PATH, "r");
    if (!file) {
        printf("Failed to open file.\n");
        return;
    }

    User user;
    char line[256];
    bool found = false;
    while (fgets(line, sizeof(line), file)) {
        if (parseLine(line, &user, userInput)) {
            displayUserData(&user);
            found = true;
            break;  // Remove break if you want to find all matches, not just the first
        }
    }
    if (!found) {
        printf("No user found matching '%s'.\n", userInput);
    }
    fclose(file);
}

bool parseLine(const char *line, User *user, const char *userInput) {
    // Example of a simple parser; adjust according to your file format
    int userId;
    char firstName[100], lastName[100], email[100], telephone[100];
    int role;

    if (sscanf(line, "%d,%99[^,],%99[^,],%d,%99[^,],%99s",
               &userId, firstName, lastName, &role, email, telephone) == 6) {
        // Fill the user struct
        user->userID = userId;
        strcpy(user->firstName, firstName);
        strcpy(user->lastName, lastName);
        user->userRole = (Role)role;
        strcpy(user->emailAddress, email);
        strcpy(user->telephone, telephone);

        // Check for match with ID or partial name match
        if (strstr(firstName, userInput) || strstr(lastName, userInput) || userId == atoi(userInput)) {
            return true;
        }
    }
    return false;
}

bool parseLineForDisplay(const char* line, User* user) {
    int userId;
    char firstName[100], lastName[100], email[100], telephone[100];
    int role;

    if (sscanf(line, "%d,%99[^,],%99[^,],%d,%99[^,],%99s",
               &userId, firstName, lastName, &role, email, telephone) == 6) {
        user->userID = userId;
        strcpy(user->firstName, firstName);
        strcpy(user->lastName, lastName);
        user->userRole = (Role)role;
        strcpy(user->emailAddress, email);
        strcpy(user->telephone, telephone);
        return true;
    }
    return false;
}

void displayAllUsers() {
    FILE* file = fopen(USER_FILE_PATH, "r");
    if (!file) {
        printf("Failed to open the user database file.\n");
        return;
    }

    User user;
    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (parseLineForDisplay(line, &user)) {
            printf("\nUser %d:\n", ++count);
            displayUserData(&user);
        }
    }

    if (count == 0) {
        printf("No users found in the database.\n");
    }

    fclose(file);
}






