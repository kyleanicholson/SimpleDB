

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


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
} User;

// Function prototypes
void add_user();

void view_user();

void update_user();

void delete_user();


int main() {

    char choice;
    do {
        printf("Please choose an operation: \n");
        printf("Choose from the list of options or enter q to quit:\n");
        printf("(1) Edit User \n");
        printf("(2) Create User\n");
        printf("(3) Delete User\n");
        printf("(Q) Quit \n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        // Process the choice

        switch (choice) {
            case '1':
                printf("Edit User Form\n");
                break;
            case '2':
                printf("Create User Form\n");
                break;
            case '3':
                printf("Delete User Form\n");
                break;
            case 'q':
                printf("Exiting App\n");
                return 0;
            default:
                printf("Invalid operation.\n\n");

        }

    } while (
            choice != 'q'
            );


    return 0;
}
