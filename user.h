#ifndef USER_H
#define USER_H

typedef struct {
    int id;
    char name[100];
    // Add more user attributes here
} User;

void createUser(User *user);
void readUser(int id);
void updateUser(int id, User *user);

#endif
