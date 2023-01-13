#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <Windows.h>


char *ADD = "F:\\Uni\\Fop\\Project";
char *ADDclip = "F:\\Uni\\Fop\\Project\\clipboard.txt";


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

void createUndo(char address[]){
    int cnt=0;
    char add[100];
    for (int i=0 ; i<100 ; i++){
        add[i]=0;
    }
    char c;
    while (address[cnt] != '.'){
        add[cnt] = address[cnt];
        cnt++;
    }
    add[cnt] = '-';cnt++;
    add[cnt] = 'u';cnt++;
    add[cnt] = 'n';cnt++;
    add[cnt] = 'd';cnt++;
    add[cnt] = 'o';cnt++;
    add[cnt] = '.';cnt++;
    add[cnt] = 't';cnt++;
    add[cnt] = 'x';cnt++;
    add[cnt] = 't';cnt++;

    FILE* fp=fopen(add,"w");
    DWORD attributes = GetFileAttributes(add);
    SetFileAttributes(add,attributes+FILE_ATTRIBUTE_HIDDEN);

    FILE* fi=fopen(address,"r+");
    cnt=0;
    while((c=(char)getc(fi))!=EOF){
        fprintf(fp,"%c",c);
    }
    fclose(fp);
    fclose(fi);
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
    char textNew[10000];
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
    createUndo(address);

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

                    int start1 = -1;
                    int line1 = 1;
                    int ii=0;
                    int j=0;
                    while((textNew[j] = (char)fgetc(fp)) != EOF){
                        start1++;
                        if (start1 == strt && lno == line1){
                            ii=j;
                        }
                        if (textNew[j] == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        j++;
                    }
                    textNew[j] = EOF;
                    fclose(fp);
                    remove(address);

                    FILE *f;
                    f = fopen(address, "w");
                    int i = 0;
                    while ((textNew[i]) != EOF){
                        if (i == ii){
                            int count = 0;
                            while (text[count] != 0 && text[count] != EOF && text[count] != '\0'){

                                if (text[count] == 92 && text[count+1] == 'n'){
                                    count++;
                                    fprintf(f , "%c",'\n');
                                    count++;
                                }
                                else if(text[count] == 92 && text[count+1] == 92){
                                    count++;
                                    fprintf(f , "%c", text[count]);
                                    count++;
                                }
                                else{
                                    fprintf(f , "%c",text[count]);
                                    //printf("%c",text[count]);
                                    count++;
                                }

                            }

                        }
                        fprintf(f , "%c",textNew[i]);
                        i++;
                    }
                    fclose(f);
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
                int start1 = -1;
                int line1 = 1;
                int ii=0;
                int j=0;
                while((textNew[j] = (char)fgetc(fp)) != EOF){
                    start1++;
                    if (start1 == strt && lno == line1){
                        ii=j;
                    }
                    if (textNew[j] == '\n'){
                        line1++;
                        start1 = -1;
                    }
                    j++;
                }
                textNew[j] = EOF;
                fclose(fp);
                remove(address);

                FILE *f;
                f = fopen(address, "w");
                int i = 0;
                while (textNew[i] != EOF){
                    if (i == ii){
                        int count = 0;
                        while (text[count] != 0 && text[count] != EOF && text[count] != '\0'){
                            if (text[count] == 92 && text[count+1] == 'n'){
                                count++;
                                fprintf(f , "%c",'\n');
                                count++;
                            }
                            else if(text[count] == 92 && text[count+1] == 92){
                                count++;
                                fprintf(f , "%c", text[count]);
                                count++;
                            }
                            else{
                                fprintf(f , "%c",text[count]);
                                //printf("%c",text[count]);
                                count++;
                            }
                        }
                    }

                    fprintf(f , "%c",textNew[i]);
                    i++;
                }

                fclose(f);
                return 1;
            }
        }

    }

    printf("Invalid arguments\n");
    return -1;

}

void cat(char list[]) {
    char address[200];
    int cnt = 0;
    int cnt1 = 0;
    if (list[cnt] == '"'){
        cnt++;
        while(list[cnt] != '"'){
            if (list[cnt] == '/'){
                list[cnt] = '\\';
            }
            address[cnt1] = list[cnt];
            cnt1++;
            cnt++;

        }
        //printf("%s\n",address);
        strcpy(address , appendAddress(ADD , address));
        //printf("%s",address);
    }
    else{
        while(list[cnt] != ' ' && list[cnt] != 0 && list[cnt] != EOF && list[cnt] != '\n' ){
            if (list[cnt] == '/'){
                list[cnt] = '\\';
            }
            address[cnt1] = list[cnt];
            cnt1++;
            cnt++;
            //printf("%c",address[cnt1-1]);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    printf("%s\n",address);
    FILE *fp;
    fp = fopen(address, "r");
    if (fp == NULL){
        printf("File does not exist\n");
    }
    else{
        char c;
        fscanf(fp , "%c",&c);
        while(c != EOF){
            printf("%c",c);
            c = (char)fgetc(fp);
        }
        printf("\n");
        fclose(fp);
    }

}

void remve() {

    char size[30];
    char pos[30];
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200];
    char text[10000];
    int cnt = 0;
    char c = 0;
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
    createUndo(address);

    scanf("%s ",pos);
    if (strcmp(pos , "--pos") == 0){
        scanf("%d:%d" , &lno,&strt);
        scanf("%s ",size);
        if (strcmp(size , "-size") == 0) {
            scanf("%d", &sizei);
            scanf(" -%c" , &fb);
            if (fb == 'f'){
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                }
                else{
                    int line1 = 1;
                    int start1 = -1;
                    int count = 0;
                    while ((c = (char)fgetc(fp)) != EOF){
                        start1++;
                        if (start1 == strt && lno == line1){
                            for (int i=0 ; i<sizei-1 ; i++){
                                c = (char)fgetc(fp);
                            }
                            continue;
                        }
                        text[count] = c;
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }
                    text[count] = EOF;
                    fclose(fp);
                    remove(address);
                    FILE *fil;
                    fil = fopen(address, "w");
                    int i = 0;
                    while (text[i] != EOF){
                        fprintf(fil,"%c",text[i]);
                        i++;
                    }
                    fclose(fil);
                }

            }
            else if(fb == 'b'){
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                }
                else{
                    int line1 = 1;
                    int start1 = -1;
                    int count = 0;
                    int ii;
                    while ((c = (char)fgetc(fp)) != EOF){
                        start1++;
                        text[count] = c;
                        if (start1 == strt && line1 == lno){
                            ii = count;
                        }
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }

                    text[count] = EOF;
                    fclose(fp);
                    remove(address);
                    FILE *fil;
                    fil = fopen(address, "w");
                    int i = -1;
                    start1 = -1;
                    line1 = 1;
                    while (text[++i] != EOF){

                        if (i == (ii-sizei)+1){
                            i += sizei-1;
                        }
                        else{
                            fprintf(fil,"%c",text[i]);
                        }
                    }
                    fclose(fil);
                }
            }

            else{
                printf("Invalid arguments\n");
            }
        }
        else{
            printf("Invalid arguments\n");
        }
    }
    else{
        printf("Invalid arguments\n");
    }


}

void copy() {

    char size[30];
    char pos[30];
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200];
    char text[10000];
    int cnt = 0;
    char c = 0;
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

    scanf("%s ",pos);
    if (strcmp(pos , "--pos") == 0){
        scanf("%d:%d" , &lno,&strt);
        scanf("%s ",size);
        if (strcmp(size , "-size") == 0) {
            scanf("%d", &sizei);
            scanf(" -%c" , &fb);
            if (fb == 'f'){
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                }
                else{
                    int line1 = 1;
                    int start1 = -1;
                    int count = 0;
                    while ((c = (char)fgetc(fp)) != EOF){
                        start1++;
                        if (start1 == strt && lno == line1){
                            for (int i=0 ; i<sizei ; i++){
                                text[count] = c;
                                count++;
                                c = (char)fgetc(fp);
                            }
                            continue;
                        }
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }

                    }
                    text[count] = EOF;
                    fclose(fp);

                    FILE *clip;
                    clip = fopen(ADDclip, "w");
                    int i = 0;
                    while (text[i] != EOF){
                        fprintf(clip,"%c",text[i]);
                        i++;
                    }
                    fclose(clip);
                }

            }
            else if(fb == 'b'){
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                }
                else{
                    int line1 = 1;
                    int start1 = -1;
                    int count = 0;
                    int ii;
                    while ((c = (char)fgetc(fp)) != EOF){
                        start1++;
                        text[count] = c;
                        if (start1 == strt && line1 == lno){
                            ii = count;
                        }
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }

                    text[count] = EOF;
                    fclose(fp);

                    FILE *fil;
                    fil = fopen(ADDclip, "w");
                    int i = -1;
                    start1 = -1;
                    line1 = 1;
                    while (text[++i] != EOF){

                        if ((i >= (ii-sizei)+1) && (i <= ii)){
                            fprintf(fil,"%c",text[i]);
                        }
                    }
                    fclose(fil);
                }
            }

            else{
                printf("Invalid arguments\n");
            }
        }
        else{
            printf("Invalid arguments\n");
        }
    }
    else{
        printf("Invalid arguments\n");
    }
}

void cut(){

    char size[30];
    char pos[30];
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200];
    char text[10000];
    char clip[10000];
    int cnt = 0;
    char c = 0;
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
    createUndo(address);

    scanf("%s ",pos);
    if (strcmp(pos , "--pos") == 0){
        scanf("%d:%d" , &lno,&strt);
        scanf("%s ",size);
        if (strcmp(size , "-size") == 0) {
            scanf("%d", &sizei);
            scanf(" -%c" , &fb);
            if (fb == 'f'){
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                }
                else{
                    int line1 = 1;
                    int start1 = -1;
                    int count = 0;
                    int clipcount = 0;
                    while ((c = (char)fgetc(fp)) != EOF){
                        start1++;
                        if (start1 == strt && lno == line1){
                            clip[clipcount] = c;
                            clipcount++;
                            for (int i=0 ; i<sizei-1 ; i++){
                                c = (char)fgetc(fp);
                                clip[clipcount] = c;
                                clipcount++;
                            }
                            continue;
                        }
                        clip[clipcount]=EOF;
                        text[count] = c;
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }
                    text[count] = EOF;
                    fclose(fp);
                    remove(address);
                    FILE *fil;
                    fil = fopen(address, "w");
                    int i = 0;
                    while (text[i] != EOF){
                        fprintf(fil,"%c",text[i]);
                        i++;
                    }
                    fclose(fil);


                    FILE *cli;
                    cli = fopen(ADDclip, "w");
                    int j = 0;
                    while (clip[j] != EOF){
                        fprintf(cli,"%c",clip[j]);
                        j++;
                    }
                    fclose(cli);
                }

            }
            else if(fb == 'b'){
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist\n");
                    fclose(fp);
                }
                else{
                    int line1 = 1;
                    int start1 = -1;
                    int count = 0;
                    int ii;
                    while ((c = (char)fgetc(fp)) != EOF){
                        start1++;
                        text[count] = c;
                        if (start1 == strt && line1 == lno){
                            ii = count;
                        }
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }

                    text[count] = EOF;
                    fclose(fp);
                    remove(address);
                    FILE *fil;
                    fil = fopen(address, "w");
                    int i = -1;
                    start1 = -1;
                    line1 = 1;
                    int clipcount = 0;
                    while (text[++i] != EOF){

                        if (i == (ii-sizei)+1){

                            for (int j=0 ; j<sizei ; j++){
                                clip[j]=text[i];
                                i++;
                            }
                            i += -1;
                        }
                        else{
                            fprintf(fil,"%c",text[i]);
                        }
                    }
                    fclose(fil);

                    FILE *cli;
                    cli = fopen(ADDclip, "w");
                    int j = 0;
                    while (clip[j] != EOF && clip[j] != '\0' && clip[j] != 0){
                        fprintf(cli,"%c",clip[j]);
                        j++;
                    }
                    fclose(cli);


                }
            }

            else{
                printf("Invalid arguments\n");
            }
        }
        else{
            printf("Invalid arguments\n");
        }
    }
    else{
        printf("Invalid arguments\n");
    }

}

void paste(){

    char pos[30];
    int lno;
    int strt;
    char address[200];
    char text[10000];
    int cnt = 0;
    char c = 0;
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
    createUndo(address);

    scanf("%s ",pos);
    if (strcmp(pos , "--pos") == 0){
        scanf("%d:%d" , &lno,&strt);

        FILE *fp;
        fp = fopen(address, "r+");
        if (fp == NULL){
            printf("File does not exist\n");
            fclose(fp);
        }

        else{
            FILE *cli;
            cli = fopen(ADDclip, "r");

            int line1 = 1;
            int start1 = -1;
            int count = 0;
            char dum;
            while ((c = (char)fgetc(fp)) != EOF){
                start1++;
                if (start1 == strt && lno == line1){
                    dum = c;
                    while ((c = (char)fgetc(cli)) != EOF){
                        text[count] = c;
                        count++;
                    }
                    text[count]=dum;
                    count++;
                }
                else{
                    text[count] = c;
                    count++;
                }
                if (c == '\n'){
                    line1++;
                    start1 = -1;
                }
            }
            text[count] = EOF;
            fclose(fp);
            fclose(cli);
            remove(address);
            FILE *fil;
            fil = fopen(address, "w");
            int i = 0;
            while (text[i] != EOF){
                fprintf(fil,"%c",text[i]);
                i++;
            }
            fclose(fil);
        }
    }
    else{
        printf("Invalid arguments\n");
    }
}

int find(){
    char address[200];
    char text[10000];
    char str[1000];
    char file[30];
    int cnt = 0;
    char c = 0;
    int cond = 0;
    int mode = 0;
    char all[30];
    char mod[30];
    int index = 0;


    scanf("%c",&c);
    if (c == '"'){
        char c1;
        scanf("%c",&c);
        while(c!='"') {

            if (cnt == 0 && c=='*'){
                cond = 1;
                scanf("%c",&c);
            }
            if (c == '*'){
                scanf("%c", &c1);
                if(c1 == '"'){
                    cond = 0;
                }
                else{
                    cond = 2;
                    index = cnt;
                    text[cnt]=c1;
                    cnt++;
                    scanf("%c", &c);
                }
            }
            if (c == 92) {
                scanf("%c", &c1);
                if (c1 == '*' || c1 == '"') {
                    text[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                } else {
                    text[cnt] = c;
                    cnt++;
                    text[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                }
            } else {
                text[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }
        }
    }

    if (c != '"') {
        char c1;
        while (c != ' ') {
            if (cnt == 0 && c=='*'){
                cond = 1;
                scanf("%c",&c);
            }
            else if (c == '*'){
                scanf("%c", &c1);
                if(c1 == ' '){
                    cond = 0;
                    c=c1;
                }
                else{
                    cond = 2;
                    index = cnt;
                    text[cnt]=c1;
                    cnt++;
                    scanf("%c", &c);
                }
            }
            else if (c == 92) {
                scanf("%c", &c1);
                if (c1 == '*') {
                    text[cnt] = c1;
                    cnt++;
                } else {
                    text[cnt] = c;
                    cnt++;
                    text[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                }
            } else {
                text[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }

        }

    }

    scanf("%s ", file);
    if (strcmp(file, "--file") != 0){
        return -2;
    }


    cnt = 0;
    char c1;
    scanf("%c",&c);
    if (c == '"'){
        scanf("%c",&c);
        while(c != '"'){
            address[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        scanf("%c",&c);
        strcpy(address , appendAddress(ADD , address));
        if (c == '\n'){
            mode = 0;
        }
        else if (c == ' '){
            mode = 1;
        }
    }
    else{
        while(c != ' ' && c != '\n'){
            address[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address , appendAddress(ADD , address));
        if (c == '\n'){
            mode = 0;
        }
        else if (c == ' '){
            mode = 1;
        }
    }
    if (mode != 0) {

        int shom = 0;
        scanf("%c", &c);
        while (c != '\n' && c != ' ') {
            all[shom]=c;
            scanf("%c", &c);
            shom++;
        }
        all[shom] = '\0';

        if (strcmp(all, "-all") == 0) {

            if (c == ' '){
                scanf("%s",mod);
                if (strcmp(mod , "-byword")==0){
                    FILE *fp;
                    fp = fopen(address, "r+");
                    //printf("%s\n",address);
                    if (fp == NULL){
                        printf("File does not exist!\n");
                    }
                    else{
                        cnt=0;
                        int cnt1 =0;
                        int res;
                        int y=0;
                        char hfile[10000];
                        int word = 1;
                        int word1 =1;
                        int u=0;
                        int hcnt = 0;
                        int init = 0;
                        int counts=0;
                        int true=0;
                        while((c = (char)fgetc(fp)) != EOF){
                            hfile[hcnt]=c;
                            hcnt++;
                        }
                        while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                            if (hfile[cnt1] == text[0]){
                                init = cnt1;
                                while (hfile[cnt1] == text[counts]){
                                    if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                        if (cond == 0){
                                            true++;
                                            if (true==1){
                                                printf("%d",word);
                                            }
                                            else{
                                                printf(",%d",word);
                                            }
                                        }
                                        else if(cond == 1){
                                            true++;
                                            if (true==1){
                                                printf("%d",word);
                                            }
                                            else{
                                                printf(",%d",word);
                                            }
                                        }

                                        else if(cond == 2){
                                            int indic = 0;
                                            while(hfile[cnt1]!=0 && indic==0){
                                                if(hfile[cnt1] == text[index]){
                                                    counts=index;
                                                    int init1 = cnt1;
                                                    while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                        if(text[counts+1]==0){
                                                            true++;
                                                            if (true==1){
                                                                printf("%d",word);
                                                                indic++;
                                                            }
                                                            else{
                                                                printf(",%d",word);
                                                                indic++;
                                                            }
                                                        }
                                                        cnt1++;
                                                        counts++;
                                                    }
                                                    counts=index;
                                                    cnt1=init1;
                                                }
                                                cnt1++;
                                            }
                                        }
                                    }
                                    cnt1++;counts++;
                                }
                                cnt1 = init;
                                counts = 0;
                            }
                            if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                                word++;
                            }
                            cnt1++;
                        }
                        if (true == 0){
                            printf("string not found\n");
                            fclose(fp);
                            return -3;
                        }
                        printf("\n");
                        fclose(fp);
                        return -3;
                    }
                }
                else return -1;
            }
            else{
                FILE *fp;
                fp = fopen(address, "r+");
                //printf("%s\n",address);
                if (fp == NULL){
                    printf("File does not exist!");
                }
                else{
                    cnt=0;
                    int cnt1 =0;
                    int res;
                    int y=0;
                    char hfile[10000];
                    int word = 1;
                    int word1 =1;
                    int u=0;
                    int hcnt = 0;
                    int init = 0;
                    int counts=0;
                    int true=0;
                    while((c = (char)fgetc(fp)) != EOF){
                        hfile[hcnt]=c;
                        hcnt++;
                    }
                    while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                        if (hfile[cnt1] == text[0]){
                            init = cnt1;
                            while (hfile[cnt1] == text[counts]){
                                if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                    if (cond == 0){
                                        u++;
                                        true++;
                                        if (true==1){
                                            printf("%d",init+1);
                                        }
                                        else{
                                            printf(",%d",init+1);
                                        }
                                    }
                                    else if(cond == 1){
                                        u++;
                                        true++;
                                        cnt1=init;
                                        while(hfile[cnt1-1] != ' ' && hfile[cnt1-1] != '\n' && cnt1>0){
                                            cnt1--;
                                        }
                                        if (true==1){
                                            printf("%d",cnt1+1);
                                        }
                                        else{
                                            printf(",%d",cnt1+1);
                                        }
                                    }

                                    else if(cond == 2){
                                        int indic = 0;
                                        while(hfile[cnt1]!=0 && indic==0){
                                            if(hfile[cnt1] == text[index]){
                                                counts=index;
                                                int init1 = cnt1;
                                                while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                    if(text[counts+1]==0){
                                                        true++;
                                                        if (true==1){
                                                            printf("%d",init+1);
                                                            indic++;
                                                        }
                                                        else{
                                                            printf(",%d",init+1);
                                                            indic++;
                                                        }
                                                    }
                                                    cnt1++;
                                                    counts++;
                                                }
                                                counts=index;
                                                cnt1=init1;
                                            }
                                            cnt1++;
                                        }
                                    }
                                }
                                cnt1++;counts++;
                            }
                            cnt1 = init;
                            counts = 0;
                        }
                        cnt1++;
                    }
                    if (true == 0){
                        printf("string not found\n");
                        fclose(fp);
                        return -3;
                    }
                    printf("\n");
                    fclose(fp);
                    return -3;
                }
            }
        }

        else if(strcmp(all , "-byword")==0){
            if (c == ' '){
                scanf("%s",mod);
                if (strcmp(mod , "-all")==0){

                    FILE *fp;
                    fp = fopen(address, "r+");
                    if (fp == NULL){
                        printf("File does not exist!");
                    }
                    else{
                        cnt=0;
                        int cnt1 =0;
                        int res;
                        int y=0;
                        char hfile[10000];
                        int word = 1;
                        int word1 =1;
                        int u=0;
                        int hcnt = 0;
                        int init = 0;
                        int counts=0;
                        int true=0;
                        while((c = (char)fgetc(fp)) != EOF){
                            hfile[hcnt]=c;
                            hcnt++;
                        }
                        while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                            if (hfile[cnt1] == text[0]){
                                init = cnt1;
                                while (hfile[cnt1] == text[counts]){
                                    if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                        if (cond == 0){
                                            true++;
                                            if (true==1){
                                                printf("%d",word);
                                            }
                                            else{
                                                printf(",%d",word);
                                            }
                                        }
                                        else if(cond == 1){
                                            true++;
                                            if (true==1){
                                                printf("%d",word);
                                            }
                                            else{
                                                printf(",%d",word);
                                            }
                                        }

                                        else if(cond == 2){
                                            int indic = 0;
                                            while(hfile[cnt1]!=0 && indic==0){
                                                if(hfile[cnt1] == text[index]){
                                                    counts=index;
                                                    int init1 = cnt1;
                                                    while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                        if(text[counts+1]==0){
                                                            true++;
                                                            if (true==1){
                                                                printf("%d",word);
                                                                indic++;
                                                            }
                                                            else{
                                                                printf(",%d",word);
                                                                indic++;
                                                            }
                                                        }
                                                        cnt1++;
                                                        counts++;
                                                    }
                                                    counts=index;
                                                    cnt1=init1;
                                                }
                                                cnt1++;
                                            }
                                        }
                                    }
                                    cnt1++;counts++;
                                }
                                cnt1 = init;
                                counts = 0;
                            }
                            if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                                word++;
                            }
                            cnt1++;
                        }
                        if (true == 0){
                            printf("string not found\n");
                            fclose(fp);
                            return -3;
                        }
                        printf("\n");
                        fclose(fp);
                        return -3;
                    }
                }
                else if(strcmp(mod , "-at")==0){
                    int num;
                    scanf("%d",&num);
                    scanf("%c",&c);
                    FILE *fp;
                    fp = fopen(address, "r+");
                    if (fp == NULL){
                        printf("File does not exist!");
                    }
                    else{
                        cnt=0;
                        int cnt1 =0;
                        int res;
                        int y=0;
                        char hfile[10000];
                        int word = 1;
                        int word1 =1;
                        int u=0;
                        int hcnt = 0;
                        int init = 0;
                        int counts=0;
                        int true=0;
                        while((c = (char)fgetc(fp)) != EOF){
                            hfile[hcnt]=c;
                            hcnt++;
                        }
                        while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                            if (hfile[cnt1] == text[0]){
                                init = cnt1;
                                while (hfile[cnt1] == text[counts]){
                                    if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                        if (cond == 0){
                                            true++;
                                            if (num == true){
                                                printf("%d",word);
                                            }
                                        }
                                        else if(cond == 1){
                                            true++;
                                            if (num == true){
                                                printf("%d",word);
                                            }
                                        }

                                        else if(cond == 2){
                                            int indic = 0;
                                            while(hfile[cnt1]!=0 && indic==0){
                                                if(hfile[cnt1] == text[index]){
                                                    counts=index;
                                                    int init1 = cnt1;
                                                    while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                        if(text[counts+1]==0){
                                                            true++;
                                                            if (num == true){
                                                                printf("%d",word);
                                                            }
                                                        }
                                                        cnt1++;
                                                        counts++;
                                                    }
                                                    counts=index;
                                                    cnt1=init1;
                                                }
                                                cnt1++;
                                            }
                                        }
                                    }
                                    cnt1++;counts++;
                                }
                                cnt1 = init;
                                counts = 0;
                            }
                            if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                                word++;
                            }
                            cnt1++;
                        }
                        if(num > true){
                            printf("-at argument too big\n");
                            fclose(fp);
                            return -3;
                        }
                        if (true == 0){
                            printf("string not found\n");
                            fclose(fp);
                            return -3;
                        }
                        printf("\n");
                        fclose(fp);
                        return -3;
                    }

                }
                return -1;
            }
            else{
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist!");
                }
                else{
                    cnt=0;
                    int cnt1 =0;
                    int res;
                    int y=0;
                    char hfile[10000];
                    int word = 1;
                    int word1 =1;
                    int u=0;
                    int hcnt = 0;
                    int init = 0;
                    int counts=0;
                    int true=0;
                    while((c = (char)fgetc(fp)) != EOF){
                        hfile[hcnt]=c;
                        hcnt++;
                    }
                    while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                        if (hfile[cnt1] == text[0]){
                            init = cnt1;
                            while (hfile[cnt1] == text[counts]){
                                if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                    if (cond == 0){
                                        true++;
                                        printf("%d\n",word);
                                        fclose(fp);
                                        return -3;


                                    }
                                    else if(cond == 1){
                                        true++;
                                        printf("%d\n",word);
                                        fclose(fp);
                                        return -3;
                                    }

                                    else if(cond == 2){
                                        int indic = 0;
                                        while(hfile[cnt1]!=0 && indic==0){
                                            if(hfile[cnt1] == text[index]){
                                                counts=index;
                                                int init1 = cnt1;
                                                while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                    if(text[counts+1]==0){
                                                        true++;
                                                        printf("%d\n",word);
                                                        fclose(fp);
                                                        return -3;
                                                    }
                                                    cnt1++;
                                                    counts++;
                                                }
                                                counts=index;
                                                cnt1=init1;
                                            }
                                            cnt1++;
                                        }
                                    }
                                }
                                cnt1++;counts++;
                            }
                            cnt1 = init;
                            counts = 0;
                        }
                        if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                            word++;
                        }
                        cnt1++;
                    }
                    if (true == 0){
                        printf("string not found\n");
                        fclose(fp);
                        return -3;
                    }
                    return -3;
                }
            }

        }

        else if(strcmp(all , "-count")==0){

            FILE *fp;
            fp = fopen(address, "r+");
            //printf("%s\n",address);
            if (fp == NULL){
                printf("File does not exist!");
            }
            else {
                cnt = 0;
                int cnt1 = 0;
                int res;
                int y = 0;
                char hfile[10000];
                int word = 1;
                int word1 = 1;
                int u = 0;
                int hcnt = 0;
                int init = 0;
                int counts = 0;
                int true = 0;
                while ((c = (char) fgetc(fp)) != EOF) {
                    hfile[hcnt] = c;
                    hcnt++;
                }
                while (hfile[cnt1] != 0 && hfile[cnt1] != '\0') {
                    if (hfile[cnt1] == text[0]) {
                        init = cnt1;
                        while (hfile[cnt1] == text[counts]) {
                            if ((text[counts + 1] == 0 || text[counts + 1] == '\0') ||
                                (cond == 2 && counts + 1 == index)) {

                                if (cond == 0) {
                                    u++;
                                    true++;

                                } else if (cond == 1) {
                                    u++;
                                    true++;

                                } else if (cond == 2) {
                                    int indic = 0;
                                    while (hfile[cnt1] != 0 && indic == 0) {
                                        if (hfile[cnt1] == text[index]) {
                                            counts = index;
                                            int init1 = cnt1;
                                            while (hfile[cnt1] == text[counts] && text[counts] != 0) {
                                                if (text[counts + 1] == 0) {
                                                    true++;
                                                }
                                                cnt1++;
                                                counts++;
                                            }
                                            counts = index;
                                            cnt1 = init1;
                                        }
                                        cnt1++;
                                    }
                                }
                            }
                            cnt1++;
                            counts++;
                        }
                        cnt1 = init;
                        counts = 0;
                    }
                    cnt1++;
                }
                printf("%d\n",true);
                fclose(fp);
                return -3;
            }

        }

        else if(strcmp(all , "-at")==0){
            int num;
            scanf("%d",&num);
            scanf("%c",&c);

            if (c==' '){
                scanf("%s" , mod);
                if (strcmp(mod , "-byword")==0){
                    FILE *fp;
                    fp = fopen(address, "r+");
                    //printf("%s\n",address);
                    if (fp == NULL){
                        printf("File does not exist!");
                    }
                    else{
                        cnt=0;
                        int cnt1 =0;
                        int res;
                        int y=0;
                        char hfile[10000];
                        int word = 1;
                        int word1 =1;
                        int u=0;
                        int hcnt = 0;
                        int init = 0;
                        int counts=0;
                        int true=0;
                        while((c = (char)fgetc(fp)) != EOF){
                            hfile[hcnt]=c;
                            hcnt++;
                        }
                        while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                            if (hfile[cnt1] == text[0]){
                                init = cnt1;
                                while (hfile[cnt1] == text[counts]){
                                    if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                        if (cond == 0){
                                            true++;
                                            if (num == true){
                                                printf("%d",word);
                                            }
                                        }
                                        else if(cond == 1){
                                            true++;
                                            if (num == true){
                                                printf("%d",word);
                                            }
                                        }

                                        else if(cond == 2){
                                            int indic = 0;
                                            while(hfile[cnt1]!=0 && indic==0){
                                                if(hfile[cnt1] == text[index]){
                                                    counts=index;
                                                    int init1 = cnt1;
                                                    while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                        if(text[counts+1]==0){
                                                            true++;
                                                            if (num == true){
                                                                printf("%d",word);
                                                            }
                                                        }
                                                        cnt1++;
                                                        counts++;
                                                    }
                                                    counts=index;
                                                    cnt1=init1;
                                                }
                                                cnt1++;
                                            }
                                        }
                                    }
                                    cnt1++;counts++;
                                }
                                cnt1 = init;
                                counts = 0;
                            }
                            if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                                word++;
                            }
                            cnt1++;
                        }
                        if(num > true){
                            printf("-at argument too big\n");
                            fclose(fp);
                            return -3;
                        }
                        if (true == 0){
                            printf("string not found\n");
                            fclose(fp);
                            return -3;
                        }
                        printf("\n");
                        fclose(fp);
                        return -3;
                    }
                }
                else{
                    printf("Invalid args\n");
                    return -3;
                }
            }
            else{
                FILE *fp;
                fp = fopen(address, "r+");
                if (fp == NULL){
                    printf("File does not exist!");
                }
                else{
                    cnt=0;
                    int cnt1 =0;
                    int res;
                    int y=0;
                    char hfile[10000];
                    int word = 1;
                    int word1 =1;
                    int u=0;
                    int hcnt = 0;
                    int init = 0;
                    int counts=0;
                    int true=0;
                    while((c = (char)fgetc(fp)) != EOF){
                        hfile[hcnt]=c;
                        hcnt++;
                    }
                    while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                        if (hfile[cnt1] == text[0]){
                            init = cnt1;
                            while (hfile[cnt1] == text[counts]){
                                if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                                    if (cond == 0){
                                        true++;
                                        if (num == true){
                                            printf("%d",init+1);
                                        }
                                    }
                                    else if(cond == 1){
                                        true++;
                                        cnt1=init;
                                        while(hfile[cnt1-1]!=' ' && hfile[cnt1-1]!='\n' && cnt1>0){
                                            cnt1--;
                                        }
                                        if (num == true){
                                            printf("%d",cnt1+1);
                                        }
                                    }

                                    else if(cond == 2){
                                        int indic = 0;
                                        while(hfile[cnt1]!=0 && indic==0){
                                            if(hfile[cnt1] == text[index]){
                                                counts=index;
                                                int init1 = cnt1;
                                                while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                                    if(text[counts+1]==0){
                                                        true++;
                                                        if (num == true){
                                                            printf("%d",init+1);
                                                        }
                                                    }
                                                    cnt1++;
                                                    counts++;
                                                }
                                                counts=index;
                                                cnt1=init1;
                                            }
                                            cnt1++;
                                        }
                                    }
                                }
                                cnt1++;counts++;
                            }
                            cnt1 = init;
                            counts = 0;
                        }
                        if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                            word++;
                        }
                        cnt1++;
                    }
                    if(num > true){
                        printf("-at argument too big\n");
                        fclose(fp);
                        return -3;
                    }
                    if (true == 0){
                        printf("string not found\n");
                        fclose(fp);
                        return -3;
                    }
                    printf("\n");
                    fclose(fp);
                    return -3;
                }
            }
        }
    }

    else if (mode == 0){
        //printf("%s",text);
        FILE *fp;
        fp = fopen(address, "r+");
        //printf("%s\n",address);
        if (fp == NULL){
            printf("File does not exist!");
        }
        else{
            cnt=0;
            int cnt1 =0;
            int res;
            int y=0;
            char hfile[10000];
            int word = 1;
            int word1 =1;
            int u=0;
            int hcnt = 0;
            int init = 0;
            int counts=0;
            int true=0;
            while((c = (char)fgetc(fp)) != EOF){
                hfile[hcnt]=c;
                hcnt++;
            }
            while (hfile[cnt1] != 0 && hfile[cnt1] != '\0'){
                if (hfile[cnt1] == text[0]){
                    init = cnt1;
                    while (hfile[cnt1] == text[counts]){
                        if ((text[counts+1] == 0 || text[counts+1] == '\0') || (cond==2 && counts+1 == index)){

                            if (cond == 0){
                                true++;

                                printf("%d\n",init+1);
                                fclose(fp);
                                return -3;

                            }
                            else if(cond == 1){
                                true++;
                                cnt1=init;
                                while(hfile[cnt1-1]!=' ' && hfile[cnt1-1]!='\n' && cnt1>0){
                                    cnt1--;
                                }
                                printf("%d\n",cnt1+1);
                                fclose(fp);
                                return -3;
                            }

                            else if(cond == 2){
                                int indic = 0;
                                while(hfile[cnt1]!=0 && indic==0){
                                    if(hfile[cnt1] == text[index]){
                                        counts=index;
                                        int init1 = cnt1;
                                        while(hfile[cnt1] == text[counts] && text[counts]!=0){
                                            if(text[counts+1]==0){
                                                true++;
                                                printf("%d\n",init+1);
                                                fclose(fp);
                                                return -3;
                                            }
                                            cnt1++;
                                            counts++;
                                        }
                                        counts=index;
                                        cnt1=init1;
                                    }
                                    cnt1++;
                                }
                            }
                        }
                        cnt1++;counts++;
                    }
                    cnt1 = init;
                    counts = 0;
                }
                if (hfile[cnt1] == ' ' || hfile[cnt1] == '\n'){
                    word++;
                }
                cnt1++;
            }
            if (true == 0){
                printf("string not found\n");
                fclose(fp);
                return -3;
            }
            printf("\n");
            fclose(fp);
            return -3;
        }
    }

    return -1;
}

void replace(){
    char address[200];
    char str1[1000] = {0};
    char str2[10000];
    char st[30];
    char file[30];
    int cnt = 0;
    char c = 0;
    int cond = 0;
    int mode = 0;
    char all[30];
    char mod[30];


    scanf("%c",&c);
    if (c == '"'){
        char c1;
        scanf("%c",&c);
        while(c!='"') {

            if (cnt == 0 && c=='*'){
                cond = 1;
                scanf("%c",&c);
            }
            else if (c == '*'){
                cond = 2;
                scanf("%c", &c);
                continue;
            }

            if (c == 92) {
                scanf("%c", &c1);
                if (c1 == '*' || c1 == '"') {
                    str1[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }
        }
    }

    if (c != '"') {
        char c1;
        while (c != ' ') {
            if (cnt == 0 && c=='*'){
                cond = 1;
                scanf("%c",&c);
            }
            else if (c == '*'){
                cond = 2;
                scanf("%c", &c);
                continue;
            }
            if (c == 92) {
                scanf("%c", &c1);
                if (c1 == '*') {
                    str1[cnt] = c1;
                    cnt++;
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }
        }
    }

    scanf("%s ", st);
    cnt=0;
    if (strcmp(st , "--str2")==0){
        scanf("%c",&c);
        if (c == '"'){
            char c1;
            scanf("%c",&c);
            while(c!='"') {
                if (c == 92) {
                    scanf("%c", &c1);
                    if (c1 == '"') {
                        str2[cnt] = c1;
                        cnt++;
                        scanf("%c", &c);
                    } else {
                        str2[cnt] = c;
                        cnt++;
                        str2[cnt] = c1;
                        cnt++;
                        scanf("%c", &c);
                    }
                } else {
                    str2[cnt] = c;
                    cnt++;
                    scanf("%c", &c);
                }
            }
        }

        if (c != '"') {
            char c1;
            while (c != ' ') {
                str2[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }

        }

        scanf("%s ",file);
        if (strcmp(file , "--file")==0){

            cnt = 0;
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
                scanf("%c",&c);
                strcpy(address , appendAddress(ADD , address));
            }
            else{
                while(c != ' ' && c != '\n'){
                    if (c == '/'){
                        c = '\\';
                    }
                    address[cnt] = c;
                    cnt++;
                    scanf("%c",&c);
                }
                strcpy(address , appendAddress(ADD , address));
            }
            createUndo(address);

            FILE *fp;
            fp = fopen(address, "r+");
            if (fp == NULL){
                printf("File does not exist\n");
                fclose(fp);
            }
            else{
                if (c == '\n'){
                    int count=0;
                    char htext[10000];
                    while ((htext[count]=(char)fgetc(fp)) != EOF){
                        count++;
                    }
                    fclose(fp);
                    count = 0;
                    int counts = 0;
                    int size = 0;
                    int index = 0;
                    int true = 0;
                    int init = 0;
                    int u =0;
                    while (htext[count] != 0 && htext[count] != '\0' && true == 0){
                        if (htext[count] == str1[0]){
                            init = count;
                            while (htext[count] == str1[counts]){
                                if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                    if (cond == 0){
                                        index = init;
                                        size = counts;
                                        true = 1;
                                        break;
                                    }
                                    else if(cond == 1){
                                        u = count;
                                        count = init;
                                        while(htext[count] != ' ' && htext[count] != '\n' && count >= 0){
                                            count--;
                                        }
                                        index = count+1;
                                        size = u-count-1;
                                        true = 1;
                                        break;
                                    }

                                    else if(cond == 2){
                                        u = count;
                                        while(htext[count] != ' ' && htext[count] != '\n' && htext[count] != 0){
                                            count++;
                                        }
                                        index = init;
                                        size = count -init-1;
                                        true = 1;
                                        break;
                                    }

                                }
                                count++;counts++;
                            }
                            count = init;
                            counts = 0;
                        }
                        count++;
                    }
                    if (index == 0 && size == 0){
                        printf("string not found\n");
                    }
                    else{
                        remove(address);
                        FILE *fil;
                        fil = fopen(address, "w");
                        cnt = 0;
                        while(htext[cnt] != 0 && htext[cnt] != EOF ){
                            if (cnt == index){
                                for (int i=0 ; str2[i]!=0 ; i++){
                                    fprintf(fil , "%c" , str2[i]);

                                }
                                cnt += size+1;
                            }
                            fprintf(fil , "%c" , htext[cnt]);
                            cnt++;
                        }
                        printf("Success\n");
                        fclose(fil);

                    }

                }

                else if(c==' '){
                    scanf("%s",all);
                    if (strcmp(all,"-all")==0){
                        int count=0;
                        char htext[10000];
                        while ((htext[count]=(char)fgetc(fp)) != EOF){
                            count++;
                        }
                        fclose(fp);

                        count = 0;
                        int counts = 0;
                        int size[1000] = {0};
                        int true = 0;
                        int index[1000] = {0};
                        int init = 0;
                        int u =0;
                        int indexc=0;
                        int sizec=0;

                        while (htext[count] != 0 && htext[count] != '\0'){
                            if (htext[count] == str1[0]){
                                init = count;
                                while (htext[count] == str1[counts]){
                                    if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                        true++;
                                        if (cond == 0){
                                            index[indexc] = init;
                                            size[sizec] = counts;
                                            indexc++;sizec++;
                                        }
                                        else if(cond == 1){
                                            u = count;
                                            count = init;
                                            while(htext[count] != ' ' && htext[count] != '\n' && count >= 0){
                                                count--;
                                            }
                                            index[indexc] = count+1;
                                            size[sizec] = u-count-1;
                                            sizec++;indexc++;
                                        }

                                        else if(cond == 2){
                                            u = count;
                                            while(htext[count] != ' ' && htext[count] != '\n' && htext[count] != 0  && htext[count] != EOF){
                                                count++;
                                            }
                                            index[indexc] = init;
                                            size[sizec] = count -init -1;
                                            sizec++;indexc++;
                                            count = init;
                                        }

                                    }
                                    count++;counts++;
                                }
                                count = init;
                                counts = 0;
                            }
                            count++;
                        }
                        if (true == 0){
                            printf("string not found\n");
                        }
                        else{
                            remove(address);
                            FILE *fil;
                            fil = fopen(address, "w");
                            cnt = 0;
                            int cnti=0;
                            while(htext[cnt] != 0 && htext[cnt] != EOF ){
                                if (cnt == index[cnti]){
                                    for (int i=0 ; str2[i]!=0 ; i++){
                                        fprintf(fil , "%c" , str2[i]);

                                    }
                                    cnt += size[cnti]+1;
                                    cnti++;
                                }
                                if (htext[cnt] != 0 && htext[cnt] != EOF){
                                    fprintf(fil , "%c" , htext[cnt]);
                                    cnt++;
                                }
                            }
                            fclose(fil);
                            printf("Success\n");

                        }
                    }
                    else if(strcmp(all,"-at")==0){

                        int num;
                        scanf("%d",&num);
                        int count=0;
                        char htext[10000];
                        while ((htext[count]=(char)fgetc(fp)) != EOF){
                            count++;
                        }
                        fclose(fp);

                        count = 0;
                        int counts = 0;
                        int size=0;
                        int true = 0;
                        int index=0;
                        int init = 0;
                        int u =0;
                        int numnum=0;

                        while (htext[count] != 0 && htext[count] != '\0'){
                            if (htext[count] == str1[0]){
                                init = count;
                                while (htext[count] == str1[counts]){
                                    if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                        true++;
                                        numnum++;
                                        if (cond == 0 && numnum==num){
                                            index = init;
                                            size = counts;
                                        }
                                        else if(cond == 1 && numnum==num){
                                            u = count;
                                            count = init;
                                            while(htext[count] != ' ' && htext[count] != '\n' && count >= 0){
                                                count--;
                                            }
                                            index = count+1;
                                            size = u-count-1;

                                        }

                                        else if(cond == 2 && numnum==num){
                                            u = count;
                                            while(htext[count] != ' ' && htext[count] != '\n' && htext[count] != 0  && htext[count] != EOF){
                                                count++;
                                            }
                                            index = init;
                                            size = count -init -1;
                                            count = init;
                                        }

                                    }
                                    count++;counts++;
                                }
                                count = init;
                                counts = 0;
                            }
                            count++;
                        }
                        if (true == 0){
                            printf("string not found\n");
                        }
                        else if(numnum<num){
                            printf("-1\n");
                        }
                        else{
                            remove(address);
                            FILE *fil;
                            fil = fopen(address, "w");
                            cnt = 0;
                            int cnti=0;
                            while(htext[cnt] != 0 && htext[cnt] != EOF ){
                                if (cnt == index){
                                    for (int i=0 ; str2[i]!=0 ; i++){
                                        fprintf(fil , "%c" , str2[i]);

                                    }
                                    cnt += size+1;
                                    cnti++;
                                }
                                if (htext[cnt] != 0 && htext[cnt] != EOF){
                                    fprintf(fil , "%c" , htext[cnt]);
                                    cnt++;
                                }
                            }
                            fclose(fil);
                            printf("Success\n");
                        }
                    }
                    else{
                        printf("Invalid args\n");
                    }
                }

            }

        }
        else{
            printf("Invalid args\n");
        }

    }
    else{
        printf("Invalid args\n");
    }

}

int grepFunc(char address[] , char str[] , int mode){
    char row[1000];
    int index;
    int res=0;
    char text[100][100];
    char c;
    FILE *fp = fopen(address,"r+");
    if (fp == NULL){
        printf("File not found\n");
        return -1;
    }
    int i=0;
    int j=0;
    while((text[i][j]=(char)getc(fp)) != EOF){
        j++;
        if (text[i][j-1] == '\n'){
            i++;
            j=0;
        }
    }
    fclose(fp);
    if (mode == 0){
        int count = 0;
        j=0;
        int init;
        int counts=0;
        while (text[count][0] != 0){
            if(text[count][j]==0){
                count++;
                j=0;
            }

            if (text[count][j] == str[0]){
                init = j;
                while (text[count][j] == str[counts] && text[count][j]!='\n' && str[counts]!=0){
                    if (str[counts+1] == 0 || str[counts+1] == '\0'){
                        j=0;
                        printf("%s: ",address);
                        while(text[count][j]!=0){
                            printf("%c",text[count][j]);
                            j++;
                        }
                        j=0;
                        count++;
                    }
                    j++;counts++;
                }
                j = init;
                counts = 0;
            }
            j++;
        }
    }
    else if(mode == 1){
        int count = 0;
        j=0;
        int init;
        int result=0;
        int counts=0;
        while (text[count][0] != 0){
            if(text[count][j]==0){
                count++;
                j=0;
            }

            if (text[count][j] == str[0]){
                init = j;
                while (text[count][j] == str[counts] && text[count][j]!='\n' && str[counts]!=0){
                    if (str[counts+1] == 0 || str[counts+1] == '\0'){
                        result++;
                        j=0;
                        count++;
                    }
                    j++;counts++;
                }
                j = init;
                counts = 0;
            }
            j++;
        }
        return result;
    }
    else if(mode == 2){
        int count = 0;
        j=0;
        int init;
        int counts=0;
        while (text[count][0] != 0){
            if(text[count][j]==0){
                count++;
                j=0;
            }

            if (text[count][j] == str[0]){
                init = j;
                while (text[count][j] == str[counts] && text[count][j]!='\n' && str[counts]!=0){
                    if (str[counts+1] == 0 || str[counts+1] == '\0'){
                        j=0;
                        printf("%s\n",address);
                        return 0;
                        count++;
                    }
                    j++;counts++;
                }
                j = init;
                counts = 0;
            }
            j++;
        }
    }

}

void grep(){
    char address[100][100];
    char str1[1000];
    char st[30];
    char op[10];
    char file[30];
    int cnt = 0;
    char c = 0;
    int mode = 0;

    scanf("%s ",op);

    if (strcmp(op,"--str")!=0){
        mode = 1;
        scanf("%s ",st);
        if (strcmp(st,"--str")!=0){
            printf("Invalid command\n");
            return;
        }

        if(strcmp(op,"-c")==0){
            mode = 1;
        }
        else if(strcmp(op,"-l")==0){
            mode = 2;
        }
        else{
            printf("Invalid command\n");
            return;
        }
    }
    scanf("%c",&c);
    if (c == '"'){
        char c1;
        scanf("%c",&c);
        while(c!='"') {
            if (c == 92) {
                scanf("%c", &c1);
                if (c1 == '"') {
                    str1[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    scanf("%c", &c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }
        }
    }

    if (c != '"') {
        while (c != ' ') {
            str1[cnt] = c;
            cnt++;
            scanf("%c", &c);
        }
    }
    scanf("%s ",file);
    if (strcmp(file,"--files")!=0){
        printf("Invalid args\n");
        return;
    }
    c=1;

    int res=0;
    int i=0;
    while(c!='\n'){
        cnt=0;
        scanf("%c",&c);
        if (c == '"'){
            scanf("%c",&c);
            while(c != '"'){
                if (c == '/'){
                    c = '\\';
                }
                address[i][cnt] = c;
                cnt++;
                scanf("%c",&c);
            }
            scanf("%c",&c);
            strcpy(address[i] , appendAddress(ADD , address[i]));
        }
        else{
            while(c != ' ' && c != '\n'){
                if (c == '/'){
                    c = '\\';
                }
                address[i][cnt] = c;
                cnt++;
                scanf("%c",&c);
            }
            strcpy(address[i] , appendAddress(ADD , address[i]));
        }
        res += grepFunc(address[i],str1,mode);
        i++;
    }
    if (mode==1){
        printf("%d\n",res);
    }


}

void undo(){
    char address[200]={0};
    char add[100]={0};
    int cnt = 0;
    char c = 0;
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
    }
    else{
        while(c != '\n'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address , appendAddress(ADD , address));
    }

    cnt=0;
    while (address[cnt] != '.'){
        add[cnt] = address[cnt];
        cnt++;
    }
    add[cnt] = '-';cnt++;
    add[cnt] = 'u';cnt++;
    add[cnt] = 'n';cnt++;
    add[cnt] = 'd';cnt++;
    add[cnt] = 'o';cnt++;
    add[cnt] = '.';cnt++;
    add[cnt] = 't';cnt++;
    add[cnt] = 'x';cnt++;
    add[cnt] = 't';cnt++;

    FILE* fp=fopen(add,"r+");
    if (fp == NULL){
        printf("no action to undo\n");
        return;
    }
    FILE* fi=fopen(address,"r+");
    cnt=0;
    while((c=(char)getc(fp))!=EOF){
        fprintf(fi,"%c",c);
    }
    fclose(fp);
    fclose(fi);
    remove(add);
}

void indent(){
    char address[200]={0};
    char text[10000] = {0};
    char textn[10000]={0};
    int cnt = 0;
    char c = 0;
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
    }
    else{
        while(c != '\n'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address , appendAddress(ADD , address));
    }

    FILE* fp=fopen(address,"r+");
    if (fp==NULL){
        printf("file not found\n");
        return;
    }
    cnt=0;
    int br1=0;
    int br2=0;
    while ((text[cnt]=(char)getc(fp)) != EOF){
        if (text[cnt] == '{'){
            br1++;
        }
        else if(text[cnt] == '}'){
            br2++;
        }
        if (br2 > br1){
            fclose(fp);
            printf("Invalid brackets\n");
            return;
        }
        cnt++;
    }
    if (br1 != br2){
        fclose(fp);
        printf("Invalid brackets\n");
        return;
    }
    fclose(fp);

    int tab=0;
    cnt=0;
    int n=0;
    while (text[cnt] !=0){
        if(text[cnt] == ' '){
            int init=cnt;
            while (text[cnt] == ' '){
                cnt++;
            }
            cnt--;
            n--;
        }
        else if(text[cnt] == '{'){
            tab++;
            if(n!=0){
                if(textn[n-1] != '\n' && textn[n-1] != '\t'){
                    textn[n++]=' ';
                }
            }
            if (textn[n-1] == '\n'){
                for (int i=0 ; i<tab-1 ; i++){
                    textn[n++]='\t';
                }
            }

            textn[n++]='{';
            textn[n++]=' ';
            cnt++;
            while(text[cnt]==' '){
                cnt++;
            }
            cnt--;
            textn[n++]='\n';
            n--;
        }
        else if(text[cnt] == '\n'){
            textn[n++]='\n';
            for (int i=0 ; i<tab ; i++){
                textn[n++]='\t';
            }
            n--;
        }
        else if(text[cnt] == '}'){

            tab--;
            if(textn[n-1]!='\n'){
                textn[n++]='\n';
            }
            for (int i=0 ; i<tab ; i++){
                textn[n++]='\t';
            }
            textn[n++] = '}';
            cnt++;
            while(text[cnt]==' '){
                cnt++;
            }
            cnt--;
            textn[n] = '\n';
        }
        else{
            if (textn[n-1] == '\n'){
                for (int i=0 ; i<tab ; i++){
                    textn[n++]='\t';
                }
            }
            textn[n]=text[cnt];
        }
        n++;
        cnt++;
    }
    FILE* fi=fopen(address , "w");
    cnt=0;
    while (textn[cnt] != 0 && textn[cnt] != EOF){
        fprintf(fi , "%c",textn[cnt]);
        cnt++;
    }
    fclose(fi);

}

int compareFn(char list[] , char list1[]){
    int word=1;
    int wordnum=0;
    int res;
    int i=0;
    int j=0;
    i=0;
    while (list[i] != 0 && list[i] != EOF){
        if (list[i] != list1[j]){
            wordnum++;
            if (wordnum > 1){
                return -1;
            }
            res=word;
            while(list[i] != ' ' && list[i] != 0 && list[i] != '\n'){
                i++;
            }
            while(list1[j] != ' ' && list1[j] != 0 && list1[j] != '\n'){
                j++;
            }
            j--;i--;
        }
        else if(list[i] == ' '){
            word++;
        }
        i++;j++;
    }
    if (wordnum>1){
        return -1;
    }
    else{
        return res;
    }
}

void compare(){
    char address[100];
    char address2[100];
    char text[10000]={0};
    char text2[10000]={0};
    int cnt = 0;
    char c = 0;
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

    cnt=0;
    scanf("%c",&c);
    if (c == '"'){
        scanf("%c",&c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address2[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address2 , appendAddress(ADD , address2));
    }
    else{
        while(c != '\n'){
            if (c == '/'){
                c = '\\';
            }
            address2[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address2 , appendAddress(ADD , address2));
    }

    FILE* f1=fopen(address , "r+");
    FILE* f2=fopen(address2 , "r+");
    if (f1 == NULL || f2 == NULL){
        printf("file not found\n");
        fclose(f1);
        fclose(f2);
        return;
    }
    cnt=0;
    c=0;
    int line1=1;
    while ((c=(char)getc(f1)) != EOF){
        text[cnt++]=c;
        if (c=='\n'){
            line1++;
        }
    }
    cnt=0;
    int line2=1;
    c=0;
    while ((c=(char)getc(f2)) != EOF){
        text2[cnt++]=c;
        if (c=='\n'){
            line2++;
        }
    }
    fclose(f1);
    fclose(f2);

    int i=0;
    int j=0;
    int ii=1;
    int jj=1;
    char l1[1000]={0};
    char l2[1000]={0};
    char w1[30]={0};
    char w2[30]={0};
    int wi=0;
    int wj=0;
    int li=0;
    int lj=0;
    while (text[i]!=0 || text2[j] !=0){
        if (text[i] == 0){
            printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n" , ii , line2);
            while (text2[j] !=0 && text2[j] !=EOF){
                printf("%c",text2[j++]);
            }
            printf("\n");
            return;
        }
        else if(text2[j]==0){
            printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n" , ii , line1);
            while (text[i] !=0 && text[i] !=EOF){
                printf("%c",text[i++]);
            }
            printf("\n");
            return;
        }
        else if (text[i] != text2[j]){
            printf("============ #%d ============\n",ii);
            ii++;jj++;
            while(text[i]!='\n' && text[i]!=0 && text[i]!=EOF){
                l1[li++]=text[i];
                i++;
            }
            while (text2[j] != '\n' && text2[j] != 0 && text2[j] != EOF){
                l2[lj++]=text2[j];
                j++;
            }
            int res = compareFn(l2,l1);
            j++;i++;
            li=0;lj=0;
            if (res == -1){
                while(l1[li] !=0 && l1[li] !=EOF){
                    printf("%c",l1[li]);
                    l1[li++]=0;
                }
                printf("\n");
                li=0;
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    printf("%c",l2[lj]);
                    l2[lj++]=0;
                }
                printf("\n");
                lj=0;
            }
            else{
                int word=1;
                while(l1[li] !=0 && l1[li] !=EOF){
                    if (l1[li] == ' '){
                        word++;
                    }
                    else if (li == 0 && res == 1){
                        printf(">>");
                        while (l1[li] != ' ' && l1[li] != 0){
                            printf("%c",l1[li]);
                            l1[li++]=0;
                        }
                        printf("<<");
                        continue;
                    }
                    else if(word == res){
                        printf(">>");
                        while (l1[li] != ' ' && l1[li] != 0){
                            printf("%c",l1[li]);
                            l1[li++]=0;
                        }
                        printf("<<");
                        continue;
                    }

                    printf("%c",l1[li]);
                    l1[li++]=0;
                }
                printf("\n");
                li=0;

                word=1;
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    if (l2[lj] == ' '){
                        word++;
                    }
                    else if (lj == 0 && res == 1){
                        printf(">>");
                        while (l2[lj] != ' ' && l2[lj] != 0){
                            printf("%c",l2[lj]);
                            l2[lj++]=0;
                        }
                        printf("<<");
                        continue;
                    }
                    else if(word == res){
                        printf(">>");
                        while (l2[lj] != ' ' && l2[lj] != 0){
                            printf("%c",l2[lj]);
                            l2[lj++]=0;
                        }
                        printf("<<");
                        continue;
                    }

                    printf("%c",l2[lj]);
                    l2[lj++]=0;
                }

                printf("\n");
                lj=0;
            }

        }
        else{
            if(text2[j] == '\n'){
                ii++;jj++;i++;j++;
                li=0;lj=0;
                while(l1[li] !=0 && l1[li] !=EOF){
                    l1[li++]=0;
                }
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    l2[lj++]=0;
                }
                li=0;lj=0;
            }

            l1[li++]=text[i];
            l2[lj++]=text2[j];
            i++;
            j++;
        }

    }
    printf("\n");

}

int command(char list[]) {
    if (strcmp(list, "exit") == 0) {

        return -1;
    }

    if (strcmp(list, "createfile") == 0) {

        return 1;
    }

    if (strcmp(list, "insertstr") == 0) {

        return 2;
    }

    if (strcmp(list, "cat") == 0) {

        return 3;
    }

    if (strcmp(list, "removestr") == 0) {

        return 4;
    }

    if (strcmp(list, "copystr") == 0) {

        return 5;
    }

    if (strcmp(list, "copystr") == 0) {

        return 5;
    }

    if (strcmp(list, "cutstr") == 0) {

        return 6;
    }

    if (strcmp(list, "pastestr") == 0) {

        return 7;
    }

    if (strcmp(list, "find") == 0) {

        return 8;
    }

    if (strcmp(list , "replace")==0){
        return 9;
    }

    if (strcmp(list , "grep")==0){
        return 10;
    }
    if (strcmp(list , "undo")==0){
        return 11;
    }
    if (strcmp(list , "auto-indent")==0){
        return 12;
    }
    if (strcmp(list , "compare")==0){
        return 13;
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

        if (com == 3){
            char dum;
            char file[30];
            char address[200];
            scanf("%s", file);
            scanf("%c", &dum);
            //printf("%s",address);
            if (strcmp(file, "--file") == 0) {
                fgets(address, 200, stdin);
                //printf("%s\n",address);
                cat(address);
            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 4) {
            char dum;
            char file[30];
            scanf("%s", file);
            scanf("%c", &dum);
            if (strcmp(file, "--file") == 0) {
                remve();

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 5) {
            char dum;
            char file[30];
            scanf("%s", file);
            scanf("%c", &dum);
            if (strcmp(file, "--file") == 0) {
                copy();

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 6){
            char dum;
            char file[30];
            scanf("%s", file);
            scanf("%c", &dum);
            if (strcmp(file, "--file") == 0) {
                cut();

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 7){
            char dum;
            char file[30];
            scanf("%s", file);
            scanf("%c", &dum);
            if (strcmp(file, "--file") == 0) {
                paste();

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 8){
            char dum;
            char str[30];
            scanf("%s ", str);
            if (strcmp(str, "--str") == 0) {
                int u = find();
                if (u == -3){

                }else{
                    printf("%d\n",u);
                }


            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 9){
            char dum;
            char str[30];
            scanf("%s ", str);
            if (strcmp(str, "--str1") == 0) {
                //printf("aa");
                replace();
            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        if (com == 10){
            grep();

        }

        if (com == 11){
            char dum;
            char file[30];
            scanf("%s ", file);
            if (strcmp(file, "--file") == 0) {
                undo();

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }


        if (com == 12){
            indent();
        }

        if (com == 13){
            compare();
        }
    }

    return 0;
}
