#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *ADD = "F:\\Uni\\Fop\\Project";


char *appendAddress(char str1[], char str2[]) {
    char *fin = calloc(1000, sizeof(char));
    int c = 0;
    int count1 = 0;
    int count2 = 0;
    while (str1[count1] != 0) {
        fin[c] = str1[count1];
        count1++;
        c++;
    }
    fin[c] = '\\';
    c++;
    while (str2[count2] != 0) {
        fin[c] = str2[count2];
        count2++;
        c++;
    }
    return fin;
}


void createFile(char list[]) {

    char c = 0;
    int check = 0;
    char dirname[70];
    int count = 0;
    char address1[100] = {0};
    strcpy(address1, ADD);
    if (list[0] == '"') {
        count += 1;
        while (list[count] != '"' && list[count] != '\n') {
            count += 1;
            c = list[count];
            int cnt = 0;
            while (list[count] != '/' && list[count] != '"' && list[count] != '\n') {
                c = list[count];
                dirname[cnt] = list[count];
                cnt++;
                count++;
                if (list[count] == '"') {
                    check = 1;
                }
                else if(list[count] == '\n'){
                    check = 1;
                    printf("Invalid arguments\n");
                }
            }
            dirname[cnt] = '\0';
            strcpy(address1, appendAddress(address1, dirname));
            if (check != 1) {
                mkdir(address1);
            }
        }
        FILE *fp;
        fp = fopen(address1, "w");
        fclose(fp);

    } else {
        while (list[count] != 0 && list[count] != EOF && list[count] != '\n') {
            c = list[count];
            count++;
            int cnt = 0;
            while (list[count] != '/' && list[count] != 0 && list[count] != EOF && list[count] != '\n') {
                c = list[count];
                dirname[cnt] = list[count];
                count++;
                cnt++;
                if (list[count] == '\n') {
                    check = 1;
                }
            }
            dirname[cnt] = '\0';
            strcpy(address1, appendAddress(address1, dirname));
            //printf("%s\n",address1);
            if (check != 1) {
                mkdir(address1);
            }

        }

        //printf("%s\n", address1);
        FILE *fp;
        fp = fopen(address1, "w");
        fclose(fp);
    }
}


int insert() {

    char str[30];
    char pos[30];
    int lno;
    int strt;
    char address[200];
    char text[5000] = {0};
    int cnt = 0;
    char c = 0;
    int cond = 0;
    scanf("%c",&c);
    if (c == '"'){
        scanf("%c",&c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address , appendAddress(ADD , address));
        //printf("%s",address);
    }
    else{
        while(c != ' '){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    //printf("%s\n" , address);

    scanf("%s ",str);
    if (strcmp(str , "--str") == 0){
        cnt = 0;
        scanf("%c" , &c);

        if (c == '"'){
            cond = 1;
            char memo[8];
            int num=1;
            scanf("%c",&c);
            while (1){
                text[cnt] = c;
                cnt++;
                scanf("%c" , &c);
                if (c == '"'){
                    num++;
                    if (num %2 == 0){
                        for (int i = 0; i<6 ; i++){
                            scanf("%c",&memo[i]);
                            //printf("%c",memo[i]);
                        }
                        if (strcmp(memo , " --pos") == 0){
                             break;
                        }
                        text[cnt] = c;
                        cnt++;
                        for (int i = 0; i<6 ; i++){
                            text[cnt] = memo[i];
                            cnt++;
                        }
                        scanf("%c" , &c);
                    }

                }
            }

        }
        else{
            cond = -1;
            while(c != ' '){
                text[cnt] = c;
                cnt++;
                scanf("%c" , &c);
                //printf("%c",c);
            }
        }
        if (cond == -1){

            scanf("%s ",pos);
            if(strcmp(pos , "--pos") == 0){
                scanf("%d",&lno);
                scanf("%c",&c);
                if (c == ':'){
                    scanf("%d",&strt);
                    FILE *fp;
                    fp = fopen(address, "r+");
                    if (fp == NULL){
                        printf("File does not exist\n");
                        fclose(fp);
                        return -1;
                    }
                    for (int i=0 ; i<lno-1 ; i++){
                        fprintf(fp , "%c",'\n');
                    }
                    for (int i=0 ; i<strt ; i++){
                        fprintf(fp , "%c",' ');
                    }
                    int count = 0;
                    while (text[count] != 0 && text[count] != EOF && text[count] != '\0'){

                        if (text[count] == 92 && text[count+1] == 'n'){
                            count++;
                            fprintf(fp , "%c",'\n');
                            count++;
                        }
                        else if(text[count] == 92 && text[count+1] == 92){
                            count++;
                            fprintf(fp , "%c", text[count]);
                            count++;
                        }
                        else{
                            fprintf(fp , "%c",text[count]);
                            //printf("%c",text[count]);
                            count++;
                        }

                    }



                    fclose(fp);
                    return 1;
                }
            }
        }

        else if (cond == 1){

            scanf("%d",&lno);
            scanf("%c",&c);
            if (c == ':'){
                scanf("%d",&strt);
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                    return -1;
                }
                for (int i=0 ; i<lno-1 ; i++){
                    fprintf(fp , "%c",'\n');
                }
                for (int i=0 ; i<strt ; i++){
                    fprintf(fp , "%c",' ');
                }
                int count = 0;
                while (text[count] != 0 && text[count] != EOF && text[count] != '\0'){
                    if (text[count] == 92 && text[count+1] == 'n'){
                        count++;
                        fprintf(fp , "%c",'\n');
                        count++;
                    }
                    else if(text[count] == 92 && text[count+1] == 92){
                        count++;
                        fprintf(fp , "%c", text[count]);
                        count++;
                    }
                    else{
                        fprintf(fp , "%c",text[count]);
                        //printf("%c",text[count]);
                        count++;
                    }
                }
                fclose(fp);
                return 1;
            }
        }

    }

    printf("Invalid arguments\n");
    return -1;

}

void cat() {

}

void remve() {

}

void copy() {

}

int command(char list[]) {
    char c;
    //createFile 1 8
    //withdraw 2 8
    //balance 3 7
    //transfer 4  8
    //info 5 4
    //invalid 0 7
    //exit -1 4
    //batchreg 6 8
    //recent actions 7 6
    //deposit 8 7
    if (strcmp(list, "exit") == 0) {

        return -1;
    }

    if (strcmp(list, "createfile") == 0) {

        return 1;
    }

    if (strcmp(list, "insertstr") == 0) {

        return 2;
    }


    return 0;
}


int main() {
    int com;
    while (1) {
        char input1[1000] = {0};
        char input2[100] = {0};
        int counter = 0;
        int ident = 0;
        char g = 0;
        scanf("%c", &g);
        if (g != '\n') {
            input1[counter] = g;
            counter++;
        }

        while (1) {
            scanf("%c", &g);
            if (g == ' ') {
                ident = 1;
                break;
            }
            if (g == '\n') {
                ident = -1;
                break;
            }
            input1[counter] = g;
            counter++;
        }
        com = command(input1);


        if (com == 0) {
            if (ident == -1) {
                printf("Invalid command\n");
            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == -1) {
            break;
        }


        if (com == 2) {
            char dum;
            char file[30];
            scanf("%s", file);
            scanf("%c", &dum);
            if (strcmp(file, "--file") == 0) {
                int rr = insert();

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }


        if (com == 1) {
            char dum;
            char file[30];
            char address[200];
            scanf("%s", file);
            scanf("%c", &dum);
            //printf("%s",address);
            if (strcmp(file, "--file") == 0) {
                fgets(address, 200, stdin);
                createFile(address);
            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }
    }

    return 0;
}
