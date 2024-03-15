

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TELEPHONE_MAX_LENGTH 30
#define EMAIL_MAX_LENGTH 255

// User roles
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
    // Date of Birth
    // Password??
    // Account creation date
    // Date of last update
    // Free Text Notes
} User;

// Function prototypes
void add_user();

void view_user();

void update_user();

void delete_user();


int main() {

    char choice;
    do {
        printf("----------------------------\n");
        printf("       Main Menu\n");
        printf("----------------------------\n");
        printf("(1) Edit User \n");
        printf("(2) Create User\n");
        printf("(3) Delete User\n");
        printf("(Q) Quit \n\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        // Process the choice

        switch (choice) {
            case '1':
                printf("\nEdit User Form\n");
                break;
            case '2':
                printf("\nCreate User Form\n");
                break;
            case '3':
                printf("\nDelete User Form\n");
                break;
            case 'q':
                printf("\nExiting App\n");
                return 0;
            default:
                printf("\nInvalid operation.\n\n");

        }

    } while (
            choice != 'q'
            );


    return 0;
}
