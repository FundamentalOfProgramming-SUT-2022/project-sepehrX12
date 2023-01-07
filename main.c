#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char* ADD = "F:\\Uni\\Fop\\Project";


char* appendAddress(char str1[] , char str2[]){
    char* fin = calloc(1000 , sizeof (char));
    int c =0;
    int count1 = 0;
    int count2 = 0;
    while (str1[count1] != 0){
        fin[c] = str1[count1];
        count1++;
        c++;
    }
    fin[c] = '\\';
    c++;
    while (str2[count2] != 0){
        fin[c] = str2[count2];
        count2++;
        c++;
    }
    return fin;
}


void createFile(char list[]){

    char c = 0;
    int check =0;
    char dirname[70];
    int count = 0;
    char address1[100] = {0};
    strcpy(address1 , ADD);
    if (list[0] == '"'){
        count+=1;
        while (list[count] != '"' && list[count] != '\n'){
            count+=1;
            c = list[count];
            int cnt=0;
            while (list[count] != '/' && list[count] !='"' && list[count] != '\n'){
                c = list[count];
                dirname[cnt] = list[count];
                cnt++;
                count++;
                if (list[count] == '"'){
                    check = 1;
                }
            }
            dirname[cnt] = '\0';
            strcpy(address1 ,  appendAddress(address1 , dirname));
            if (check != 1){
                mkdir(address1);
            }
        }
        FILE *fp;
        fp = fopen(address1 , "w");
        fclose(fp);

    }
    else{
        while (list[count] != 0 && list[count] != EOF && list[count] != '\n'){
            c = list[count];
            count++;
            int cnt=0;
            while (list[count] != '/' && list[count] != 0 && list[count] != EOF && list[count] != '\n'){
                c = list[count];
                dirname[cnt] = list[count];
                count++;
                cnt++;
                if (list[count] == '\n'){
                    check = 1;
                }
            }
            dirname[cnt] = '\0';
            strcpy(address1 ,  appendAddress(address1 , dirname));
            //printf("%s\n",address1);
            if (check != 1){
                mkdir(address1);
            }

        }

        printf("%s\n",address1);
        FILE *fp;
        fp = fopen(address1 , "w");
        fclose(fp);
    }
}


void insert(){

}
void cat(){

}
void remve(){

}
void copy(){

}

int command(char list[]){
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
    if (strcmp(list , "exit") == 0){

        return 2;
    }

    if (strcmp(list , "createfile") == 0){

        return 1;
    }


    return 0;
}



int main() {
    int com;
    while (1){
        char input1[1000] ={0};
        char input2[100] ={0};
        int counter=0;
        int ident=0;
        char g=0;
        scanf("%c",&g);
        if (g != '\n'){
            input1[counter]=g;
            counter++;
        }

        while (1){
            scanf("%c",&g);
            if(g == ' '){
                ident=1;
                break;
            }
            if(g == '\n'){
                ident=-1;
                break;
            }
            input1[counter]=g;
            counter++;
        }
        com = command(input1);


        if (com == 0){
            if (ident == -1){
                printf("Invalid command\n");
            }
            else{
                char c=0;
                while (c != '\n'){
                    scanf("%c",&c);
                }
                printf("Invalid command\n");
            }
        }

        if(com == 2){
            break;
        }


        if (com == 1){
            char file[30];
            char address[200];
            scanf("%s ",file);
            fgets(address , 200 , stdin);
            //printf("%s",address);
            if (strcmp(file , "--file") == 0){
                createFile(address);
            }
            else{
                printf("Invalid command\n");
            }
        }
    }

    return 0;
}
