#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "func.h"

int version[3]={0, 5, 0};
char versionInfo[8]="alpha";


// Information

void start()
{
    printf("\n\n会员卡管理程序\n版本 %s %d.%d.%d\n", versionInfo, version[0], version[1], version[2]);
}

void getOp()
{
    while(1) {
        printf("\n请输入需要的操作代号并按Enter（回车键）：");
        int valid=1;
        if ((valid=scanf("%d", &op))==0) {
            printf("您的输入不正确，请重新输入：");
            continue;
        } else {
            return;
        }
    }
}

// Menu

void menu3() {
    printf("1. 按姓名查找\n2. 按卡号查找\n3. 用户遍历\n");
    getOp();
    switch (op) {
        case 1: {
            searchWithName();
            break;
        }
        case 2: {
            searchWithNum();
            break;
        }
        case 3: {
            userTraversal();
            break;
        }
    }
}

void menu(char *path, char *userFilePath) {
    printf("1. 用户消费\n2. 用户充值\n3. 查找用户\n4. 新增用户\n5. 修改用户资料\n6. 删除用户\n7. 导出用户资料\n0. 退出程序\n");
    getOp();
    
    switch(op) {
        case 0: {
            fwrite(user, sizeof(struct userInfo), MAX_USER, userFile);
            rewind(userFile);
            fclose(userFile);
            free(userFilePath);
            userFilePath=NULL;
            exit(1);
            break;
        }
        case 1: {
            consume();
            break;
        }
        case 2: {
            charge();
            break;
        }
        case 3: {
            menu3();
            break;
        }
        case 4: {
            addUser();
            break;
        }
        case 5: {
            editUser();
            break;
        }
        case 6: {
            deleteUser();
            break;
        }
        case 7: {
            exportFile(path);
            break;
        }
        default: {
            printf("未知操作，请重试：\n\n");
            sleep(1);
        }
    }
}

// Main

int main(int argc, char *argv[])
{
    start();
    char *path=argv[0];
    char *truncate;
    truncate=strrchr(path, 'm');
    *truncate='\0';
    char *userFilePath=malloc(sizeof(char)*(strlen(path)+16));
    strcpy(userFilePath, path);
    strcat(userFilePath, "userFile");
    printf("当前用户资料存放目录：%s\n", path);
    checkUserFile(userFilePath);

    while (1) {
        menu(path, userFilePath);
    }
    return 0;
}
