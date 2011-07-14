#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "func.h"


int enterNum ()
{
    printf("请输入卡号（输入“0”跳出）：");
    int number;
    scanf("%d", &number);
    return number;
}
void printNoThisUser() {
    printf("不存在该用户，请检查卡号是否无误并重试。\n");
}

void checkUserFile(char *userFilePath) { //This function will open userFile.
    userFile=fopen(userFilePath, "rb+");
    if (userFile==NULL) {
        firstUseInit(userFilePath);
    } else {
        normalInit(userFilePath);
    }
}

void writeInfo()
{
    fwrite(user, sizeof(struct userInfo), MAX_USER, userFile);
    rewind(userFile);
}

void showTitle() {
    printf("卡号\t\t姓名\t\t余额\n");
}

void showInfo (int num)
{
    printf("%d\t\t%s\t\t%.2f\n", num, user[num].name, user[num].money);
}

void firstUseInit(char *userFilePath)
{
    printf("这似乎是您第一次运行该程序，程序将进行初始化……\n\n");
    int i;
    for (i=0; i<MAX_USER; i++) {
        user[i].isFull=0;
        user[i].money=0;
        strcpy(user[i].name, "\0");
    }
    userFile=fopen(userFilePath, "wb+");
    writeInfo();
    printf("初始化成功。\n\n");
    sleep(1);
}

void normalInit(char *userFilePath)
{
    userFile=fopen(userFilePath, "rb+");
    fread(user, sizeof(struct userInfo), MAX_USER, userFile);
    rewind(userFile);
}


void addUser()
{
    int num=0;
    int returnChk=0;
    while (1) {
        printf("请输入卡号（当前卡号上限：%d）：", MAX_USER-1);
        returnChk=scanf("%d", &num);
        if (user[num].isFull) {
            printf("该用户已经存在，请重新输入。\n");
            continue;
        }
        if (returnChk!=1 || num<=0 || num>MAX_USER) {
            printf("卡号格式有误或卡号大于用户上限数（当前上限数：%d），请重新输入。\n", MAX_USER-1);
            continue;
        }

        printf("请输入用户姓名（长度小于%d个汉字）：", MAX_NAME/3);
        returnChk=scanf("%s", user[num].name);
        if (returnChk!=1) {
            printf("用户姓名格式有误或超过%d个汉字，请重新输入。\n", MAX_NAME/3);
            continue;
        }
        printf("请输入充值金额：");
        returnChk=scanf("%f", &user[num].money);
        if(returnChk!=1) {
            printf("金额格式有误，请重新输入。\n");
            continue;
        }
        user[num].isFull=1;
        writeInfo();
        showTitle();
        showInfo(num);
        printf("添加成功！\n\n");
        sleep(1);
        return;
    }
}

void consume()
{
    while(1) {
        int num=0;
        float money=0;
        printf("请输入卡号（输入“0”可取消）：");
        scanf("%d", &num);
        if (num==0) {
            break;
        }
        if (user[num].isFull==0) {
            printNoThisUser();
            continue;
        }
        showTitle();
        showInfo(num);
        printf("请输入消费金额（输入“0”可取消）：");
        scanf("%f", &money);
        if (money==0) {
            break;
        }
        float after=user[num].money-money;
        if (after<0) {
            printf("余额不足，请充值后重试。\n\n");
            sleep(2);
            break;
        }
        char tempOp;
        printf("消费后余额：%.2f\n输入“y”确认，输入其他字符取消：", after);
        scanf(" %c", &tempOp);
        if (tempOp=='y') {
            user[num].money=after;
            writeInfo();
            printf("消费成功！\n\n");
            sleep(1);
        }
        return;
    }
}

void charge()
{
    while(1) {
        int num=0;
        float money=0;
        printf("请输入卡号（输入“0”可取消）：");
        if ((num=enterNum())==0) {
            break;
        }
        if (user[num].isFull==0) {
            printNoThisUser();
            continue;
        }
        showTitle();
        showInfo(num);
        printf("请输入充值金额（输入“0”可取消）：");
        scanf("%f", &money);
        if (money==0) {
            break;
        }
        float after=user[num].money+money;
        char tempOp;
        printf("充值后余额：%.2f\n输入“y”确认，输入其他字符取消：", after);
        scanf(" %c", &tempOp);
        if (tempOp=='y') {
            user[num].money=after;
            writeInfo();
            printf("充值成功！\n\n");
            sleep(1);
        }
        return;
    }
}

void searchWithNum()
{
    int num;
    printf("请输入卡号：");
    scanf("%d", &num);
    if (user[num].isFull==0) {
        printf("未找到该用户，请检查卡号是否无误并重试。");
        sleep(3);
    } else {
        showTitle();
        showInfo(num);
    }
}

void searchWithName()
{
    char name[MAX_NAME];
    printf("请输入用户姓名（或其一部分）：");
    scanf("%s", name);
    int i;
    int ifShowTitle=1;
    int ifHas=0;
    for (i=0; i<MAX_USER; i++) {
        if (user[i].isFull) {
            ifHas=1;
            if (strstr(user[i].name, name)!=NULL) {
                if (ifShowTitle) {
                    showTitle();
                    ifShowTitle=0;
                }
                showInfo(i);
            }
        }
    }
    if (!ifHas) {
        printf("未找到用户。\n\n");
        sleep(1);
    }
}

void userTraversal()
{
    int i;
    int ifShowTitle=1;
    int ifHas=0;
    for (i=0; i<MAX_USER; i++) {
        if (user[i].isFull) {
            ifHas=1;
            if (ifShowTitle) {
                showTitle();
                ifShowTitle=0;
            }
            showInfo(i);
        }
    }
    if (!ifHas) {
        printf("未找到任何用户。\n\n");
        sleep(1);
    }
}

void deleteUser()
{
    while(1) {
        int num;
        if ((num=enterNum())==0) {
            break;
        }
        if (!user[num].isFull) {
            printNoThisUser();
            continue;
        }

        showTitle();
        showInfo(num);
        char tempOp;
        printf("输入“y”确认，输入其他字符跳出：");
        scanf(" %c", &tempOp); //Damn lang C!!!!
        if (tempOp!='y') {
            break;
        }

        while (1) {
            printf("用户余额为%.2f，请退钱。退钱完毕后输入“y”继续：", user[num].money);
            scanf(" %c", &tempOp);
            if (tempOp=='y') {
                break;
            }
        }

        user[num].isFull=0;
        user[num].money=0;
        strcpy(user[num].name, "\0");
        user[num].isFull=0;
        writeInfo();
        printf("删除成功！\n\n");
        sleep(1);
        return;
    }
}

void editUser()
{
    while(1) {
        int num;
        if ((num=enterNum())==0) {
            break;
        }
        if (!user[num].isFull) {
            printNoThisUser();
            continue;
        }
        showTitle();
        showInfo(num);
        char tempOp='\0';
        printf("输入“y”确认，输入其他字符跳出：");
        scanf(" %c", &tempOp);
        if (tempOp!='y') {
            break;
        }

        int newNum;
        int returnChk;
        printf("请输入新卡号（当前卡号上限：%d，输入“0”保持原卡号不变）：", MAX_USER-1);
        returnChk=scanf("%d", &newNum);
        if (user[newNum].isFull) {
            printf("该用户已经存在，请重新输入。\n");
            continue;
        }
        if (returnChk!=1 || newNum<0 || newNum>MAX_USER) {
            printf("卡号格式有误或卡号大于用户上限数（当前上限数：%d），请重新输入。\n", MAX_USER-1);
            continue;
        }
        if (newNum==0) {
            newNum=num;
        }
        char newName[MAX_NAME];
        printf("请输入新名称（长度小于%d个汉字，输入“0”保持原名不变）：", (MAX_NAME-1)/3);
        scanf("%s", newName);
        user[num].isFull=0;
        user[newNum].isFull=1;
        strcpy(user[newNum].name, newName);
        user[newNum].money=user[num].money;
        fwrite(user, sizeof(struct userInfo), MAX_USER, userFile);
        rewind(userFile);
        printf("修改完成！\n");
        showTitle();
        showInfo(newNum);
        printf("\n\n");
        sleep(3);
        return;
    }
}

void exportFile(char *path)
{
    printf("导出中……\n");
    char *exportFilePath=malloc(sizeof(char)*(strlen(path)+16));
    strcpy(exportFilePath, path);
    strcat(exportFilePath, "exportFile.txt");
    FILE *exportFile;
    if((exportFile=fopen(exportFilePath, "w+"))==NULL) {
        perror("Open file error");
        return;
    }
    int i;
    for (i=0; i<MAX_USER; i++) {
        if (user[i].isFull) {
            fprintf(exportFile, "%d\t%s\t%.2f\n", i, user[i].name, user[i].money);
        }
    }
    fclose(exportFile);
    printf("导出完毕，文件地址：%s\n\n", exportFilePath);
    sleep(4);
    return;
}
