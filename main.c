#include <stdio.h>
#include <ctype.h>
#include "user.h"

int main() {

    char choice;
    do {
        printf("----------------------------\n");
        printf("       Main Menu\n");
        printf("----------------------------\n");
        printf("(1) Create User\n");
        printf("(2) Edit User\n");
        printf("(3) View User\n");
        printf("(4) Display All Users\n");
        printf("(5) Delete User\n");
        printf("(Q) Quit \n\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        choice = tolower(choice);
        printf("\n");

        // Process the choice

        switch (choice) {
            case '1': {
                // Create a new user
                getUserData();
                break;
            }
            case '2':

                printf("Editing user \n\n");
                printf("----------------------------\n");
                break;
            case '3':
                printf("Viewing User\n");
                printf("----------------------------\n");
                promptForUser();
                break;
            case '4':
                printf("All Users\n");
                printf("----------------------------\n");
                displayAllUsers();
                break;
            case '5':
                printf("Deleting User\n");
                printf("----------------------------\n");
                promptForUser();
                break;

            case 'q':
                printf("\nExiting App\n");
                return 0;
            default:
                printf("\nInvalid operation.\n\n");

        }


    } while (choice != 'q');


    return 0;
}
