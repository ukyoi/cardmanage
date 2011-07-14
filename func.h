#ifndef FUNC_H
#define FUNC_H

#define MAX_USER 1024
#define MAX_NAME 32
struct userInfo {
    int isFull;
    char name[MAX_NAME]; //user name are limited to 10 Chinese char.
    float money;
};

struct userInfo user[MAX_USER];
FILE *userFile; //The lenth of the variable name should less than 17 chars.
int op; // op: Operation

void firstUseInit(char *userFilePath);
void normalInit(char *userFilePath);
void showTitle();
void showInfo(int num);
void checkUserFile(char *userFilePath);
void showTitle();
void showInfo(int num);

void consume();
void charge();
void addUser();
void searchWithName();
void searchWithNum();
void deleteUser();
void editUser();
void exportFile(char *path);

#endif
