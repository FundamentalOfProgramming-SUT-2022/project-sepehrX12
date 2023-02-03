#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <Windows.h>
#include <dirent.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int depth;
char *ADD = "F:\\Uni\\Fop\\Project";
char *ADDclip = "F:\\Uni\\Fop\\Project\\clipboard.txt";
char *DIRE = "F:\\Uni\\Fop\\Project\\root";
char *ARM = "F:\\Uni\\Fop\\Project\\arman.txt";
int arman=0;

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
    char add[100]={0};
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
    add[cnt] = '\0';cnt++;

    FILE* fffp=fopen(add,"r+");
    if (fffp == NULL){
        fclose(fffp);
        fffp = fopen(add , "w");
        DWORD attributes = GetFileAttributes(add);
        SetFileAttributes(add,attributes+FILE_ATTRIBUTE_HIDDEN);
    }
    else{
        fclose(fffp);
        remove(add);
        fffp = fopen(add , "w");
        DWORD attributes = GetFileAttributes(add);
        SetFileAttributes(add,attributes+FILE_ATTRIBUTE_HIDDEN);
    }
    FILE* fiii=fopen(address,"r");
    cnt=0;
    while((c=(char)getc(fiii))!=EOF){
        fprintf(fffp,"%c",c);
    }
    fclose(fffp);
    fclose(fiii);
}

int undofinder(char list[]){
    char aa[5] = "undo";
    int cnt=0;int j=0;
    int res=0;
    while (list[cnt] != 0 && list[cnt] != '\0'){
        if (list[cnt] == '-'){
            cnt++;
            while (list[cnt] != 0 && list[cnt] != '\0' && list[cnt]==aa[j]){
                res++;
                cnt++;j++;
            }
            if (res==4){
                return 1;
            }
            j=0;
        }
        cnt++;
    }
    return 0;
}

void createFile(char list[]) {

    char c = 0;
    int check = 0;
    char dirname[70]={0};
    int count = 0;
    char address1[100] = {0};
    strcpy(address1, ADD);
    if (list[0] == '"') {
        count += 1;
        while (list[count] != '"' && list[count] != '\n') {
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
            count += 1;
        }
        FILE *fp;
        fp = fopen(address1, "r+");
        if (fp != NULL){
            printf("file already exists\n");
        }
        else{
            fclose(fp);
            fopen(address1,"w");
        }
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

        FILE *fp;
        fp = fopen(address1, "r+");
        if (fp != NULL){
            printf("file already exists\n");
        }
        else{
            fclose(fp);
            fopen(address1,"w");
        }
        fclose(fp);
    }
}

int insert() {

    char str[30]={0};
    char pos[30]={0};
    int lno;
    int strt;
    char address[200]={0};
    char text[5000] = {0};
    char textNew[10000]={0};
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

int insertarman() {

    char str[30]={0};
    char pos[30]={0};
    int lno;
    int strt;
    char address[200]={0};
    char text[5000] = {0};
    char textNew[10000]={0};
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

    FILE* arm = fopen(ARM,"r+");

    scanf("%s",pos);

    cnt = 0;
    fscanf(arm,"%c" , &c);
    fscanf(arm,"%c",&c);

    cond = -1;
    while(c != EOF && c!= 0){
        text[cnt] = c;
        cnt++;
        fscanf(arm,"%c" , &c);
    }

    text[cnt-1]=0;
    fclose(arm);
    cnt=0;
    cnt=0;
    if (cond == -1){
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
    int cnt = 0;
    int cnt1 = 0;

    FILE *fp;
    fp = fopen(list, "r");
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

void catarman(char list[]) {
    int cnt = 0;
    int cnt1 = 0;
    FILE *fp;
    fp = fopen(list, "r");
    FILE *fa;
    fa = fopen(ARM , "w");
    if (fp == NULL){
        fprintf(fa,"File does not exist\n");
    }
    else{
        char c;
        fscanf(fp , "%c",&c);
        fprintf(fa,"\"");
        while(c != EOF){
            fprintf(fa,"%c",c);
            c = (char)fgetc(fp);
        }
        fprintf(fa,"\"");
        fprintf(fa,"%c",EOF);
        fclose(fp);
    }
    fclose(fa);
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

    char size[30]={0};
    char pos[30]={0};
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

            FILE *fp;
            fp = fopen(address, "r+");

            FILE *clip;
            clip = fopen(ADDclip, "w");

            if (fp == NULL){
                printf("File does not exist\n");
                fclose(fp);
                return;
            }

            if (fb == 'f'){
                int line1 = 1;
                int start1 = -1;
                int count = 0;
                while ((c = (char)fgetc(fp)) != EOF){
                    start1++;
                    if (start1 == strt && lno == line1){
                        for (int i=0 ; i<sizei ; i++){
                            fprintf(clip , "%c",c);
                            c = (char)fgetc(fp);
                        }
                        continue;
                    }
                    if (c == '\n'){
                        line1++;
                        start1 = -1;
                    }
                }
                //fprintf(clip , "%c" , EOF);
                fclose(fp);
                fclose(clip);
            }
            else if(fb == 'b'){
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

    char size[30]={0};
    char pos[30]={0};
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200]={0};
    char text[10000]={0};
    char clip[10000]={0};
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

    char pos[30]={0};
    int lno;
    int strt;
    char address[200]={0};
    char text[10000]={0};
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
    char address[200]={0};
    char text[10000]={0};
    char str[1000]={0};
    char file[30]={0};
    int cnt = 0;
    char c = 0;
    int cond = 0;
    int mode = 0;
    char all[30];
    char mod[30];
    int index = 0;
    FILE* arm = fopen(ARM,"r");

    if(arman==0)scanf("%c",&c);
    else fscanf(arm,"%c",&c);
    if (c == '"'){
        char c1;
        if(arman==0)scanf("%c",&c);
        else fscanf(arm,"%c",&c);
        while(c!='"') {

            if (cnt == 0 && c=='*'){
                cond = 1;
                if(arman==0)scanf("%c",&c);
                else fscanf(arm,"%c",&c);
            }
            else if (c == '*'){
                if(arman==0)scanf("%c",&c1);
                else fscanf(arm,"%c",&c1);
                if(c1 == '"'){
                    cond = 0;
                    c=c1;
                }
                else{
                    cond = 2;
                    index = cnt;
                    text[cnt]=c1;
                    cnt++;
                    if(arman==0)scanf("%c",&c);
                    else fscanf(arm,"%c",&c);
                }
            }
            else if (c == 92) {
                if(arman==0)scanf("%c",&c1);
                else fscanf(arm,"%c",&c1);
                if (c1 == '*' || c1 == '"') {
                    text[cnt] = c1;
                    cnt++;
                    if(arman==0)scanf("%c",&c);
                    else fscanf(arm,"%c",&c);
                } else {
                    text[cnt] = c;
                    cnt++;
                    text[cnt] = c1;
                    cnt++;
                    if(arman==0)scanf("%c",&c);
                    else fscanf(arm,"%c",&c);
                }
            } else {
                text[cnt] = c;
                cnt++;
                if(arman==0)scanf("%c",&c);
                else fscanf(arm,"%c",&c);
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
            else if (c == ' '){
                scanf("%c", &c1);
                if(c1 == '"'){
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

    if (arman==0){
        scanf("%s ", file);
        if (strcmp(file, "--file") != 0){
            return -2;
        }
    }
    fclose(arm);
    arman=0;

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
            scanf("%c",&c);
            if(c=='-')
                mode = 1;
            else{
                char c3,c2;
                scanf("%c%c",&c3,&c2);
                if(c3=='D' && c=='=' && c2==' '){
                    arman=1;
                }
            }
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
            scanf("%c",&c);
            if(c=='-')
                mode = 1;
            else{
                char c3,c2;
                scanf("%c%c",&c3,&c2);
                if(c3=='D' && c=='=' && c2==' '){
                    arman=1;
                }
            }
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

        if (strcmp(all, "all") == 0) {

            int ty=0;
            if (c == ' '){
                ty=1;
                scanf("%c",&c);
                if(c=='-'){
                    scanf("%s",mod);scanf("%c",&c);
                    if (strcmp(mod , "byword")==0){
                        if(c != '\n'){
                            char c2,c3;
                            scanf("%c%c%c",&c,&c2,&c3);
                            if(c2=='D')arman=1;
                        }
                        FILE *ar = fopen(ARM,"w");
                        fprintf(ar,"%c",'"');
                        FILE *fp;
                        fp = fopen(address, "r+");
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
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)printf(",%d",word);
                                                    else fprintf(ar,",%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                true++;
                                                if (true==1){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)printf(",%d",word);
                                                    else fprintf(ar,",%d",word);
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
                                                                    if(arman==0)printf("%d",word);
                                                                    else fprintf(ar,"%d",word);
                                                                    indic++;
                                                                }
                                                                else{
                                                                    if(arman==0)printf(",%d",word);
                                                                    else fprintf(ar,",%d",word);
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
                char c2,c3;
                scanf("%c%c",&c2,&c3);
                if(c=='=' && c2=='D' && c3==' '){
                    arman=1;ty=0;
                }
                else{
                    return -1;
                }

            }
            if(ty==0){
                FILE *ar= fopen(ARM,"w");
                fprintf(ar,"%c",'"');
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
                                            if(arman==0)printf("%d",init+1);
                                            else fprintf(ar,"%d",init+1);
                                        }
                                        else{
                                            if(arman==0)printf(",%d",init+1);
                                            else fprintf(ar,",%d",init+1);
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
                                            if(arman==0)printf("%d",cnt1+1);
                                            else fprintf(ar,"%d",cnt1+1);
                                        }
                                        else{
                                            if(arman==0)printf(",%d",cnt1+1);
                                            else fprintf(ar,",%d",cnt1+1);
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
                                                            if(arman==0)printf("%d",init+1);
                                                            else fprintf(ar,"%d",init+1);
                                                            indic++;
                                                        }
                                                        else{
                                                            if(arman==0)printf(",%d",init+1);
                                                            else fprintf(ar,",%d",init+1);
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
                    if(arman==0)printf("\n");
                    else fprintf(ar,"\n");
                    fprintf(ar,"%c%c",'"',EOF);
                    fclose(ar);
                    fclose(fp);
                    return -3;
                }
            }
        }

        else if(strcmp(all , "byword")==0){
            int ty=0;
            if (c == ' '){
                ty=1;
                scanf("%c",&c);
                if(c=='-'){
                    scanf("%s%c",mod,&c);
                    if (strcmp(mod , "all")==0){

                        if(c== ' '){
                            char c2,c3;
                            scanf("%c%c%c",&c2,&c3,&c);
                            arman=1;
                        }
                        FILE *ar= fopen(ARM,"w");
                        fprintf(ar,"%c",'"');
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
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)printf(",%d",word);
                                                    else fprintf(ar,",%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                true++;
                                                if (true==1){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)printf(",%d",word);
                                                    else fprintf(ar,",%d",word);
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
                                                                    if(arman==0)printf("%d",word);
                                                                    else fprintf(ar,"%d",word);
                                                                    indic++;
                                                                }
                                                                else{
                                                                    if(arman==0)printf(",%d",word);
                                                                    else fprintf(ar,",%d",word);
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
                                if(arman==0)printf("string not found\n");
                                else fprintf(ar,"string not found\n");
                                fprintf(ar,"%c%c",'"',EOF);
                                fclose(ar);
                                fclose(fp);
                                return -3;
                            }
                            if(arman==0)printf("\n");
                            else fprintf(ar,"\n");
                            fprintf(ar,"%c%c",'"',EOF);
                            fclose(ar);
                            fclose(fp);
                            return -3;
                        }
                    }
                    else if(strcmp(mod , "at")==0){
                        int num;
                        scanf("%d",&num);
                        scanf("%c",&c);
                        if(c== ' '){
                            char c2,c3;
                            scanf("%c%c%c",&c2,&c3,&c);
                            arman=1;
                        }
                        FILE *ar= fopen(ARM,"w");
                        fprintf(ar,"%c",'"');
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
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                true++;
                                                if (num == true){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
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
                                                                    if(arman==0)printf("%d",word);
                                                                    else fprintf(ar,"%d",word);
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
                                fclose(ar);
                                fclose(fp);
                                return -3;
                            }
                            if (true == 0){
                                printf("string not found\n");
                                fclose(fp);
                                fclose(ar);
                                return -3;
                            }
                            if(arman==0)printf("\n");
                            else fprintf(ar,"\n");
                            fprintf(ar,"%c%c",'"',EOF);
                            fclose(ar);
                            fclose(fp);
                            return -3;
                        }

                    }
                    return -1;
                }
                else{
                    char c2,c3;
                    scanf("%c%c",&c2,&c3);
                    arman=1;ty=0;
                }

            }
            if (ty==0){
                FILE *ar = fopen(ARM , "w");
                fprintf(ar,"%c",'"');
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
                                        if(arman==0)printf("%d\n",word);
                                        else fprintf(ar,"%d\n",word);
                                        fprintf(ar,"%c%c",'"',EOF);
                                        fclose(ar);
                                        fclose(fp);
                                        return -3;


                                    }
                                    else if(cond == 1){
                                        true++;
                                        if(arman==0)printf("%d\n",word);
                                        else fprintf(ar,"%d\n",word);
                                        fprintf(ar,"%c%c",'"',EOF);
                                        fclose(ar);
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
                                                        if(arman==0)printf("%d\n",word);
                                                        else fprintf(ar,"%d\n",word);
                                                        fprintf(ar,"%c%c",'"',EOF);
                                                        fclose(ar);
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
                        if(arman==0)printf("string not found\n");
                        else fprintf(ar,"string not found\n");
                        fprintf(ar,"%c%c",'"',EOF);
                        fclose(fp);
                        fclose(ar);
                        return -3;
                    }
                    return -3;
                }
            }

        }

        else if(strcmp(all , "count")==0){

            if(c==' '){
                scanf("%c",&c);
                if(c!='='){
                    printf("invalid args\n");
                    return -3;
                }
                char c2,c3;
                scanf("%c%c",&c2,&c3);
                arman=1;
            }
            FILE *ar= fopen(ARM,"w");
            fprintf(ar,"%c",'"');
            FILE *fp;
            fp = fopen(address, "r+");
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
                if(arman==0)printf("%d\n",true);
                else fprintf(ar,"%d\n",true);
                fprintf(ar,"%c%c",'"',EOF);
                fclose(ar);
                fclose(fp);
                return -3;
            }

        }

        else if(strcmp(all , "at")==0){
            int ty=0;
            int num;

            scanf("%d",&num);
            scanf("%c",&c);

            if (c==' '){
                ty=1;
                scanf("%c",&c);
                if (c=='-'){
                    scanf("%s%c" , mod,&c);
                    if (strcmp(mod , "byword")==0){
                        if(c==' '){
                            char c2,c3;
                            scanf("%c%c%c",&c,&c2,&c3);
                            arman=1;
                        }
                        FILE *ar= fopen(ARM,"w");
                        fprintf(ar,"%c",'"');
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
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                true++;
                                                if (num == true){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
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
                                                                    if(arman==0)printf("%d",word);
                                                                    else fprintf(ar,"%d",word);
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
                            if(arman==0)printf("\n");
                            else fprintf(ar,"\n");
                            fprintf(ar,"%c%c",'"',EOF);
                            fclose(ar);
                            fclose(fp);
                            return -3;
                        }
                    }
                    else{
                        printf("Invalid args\n");
                        return -3;
                    }
                }
                else {
                    char c2,c3;
                    scanf("%c%c",&c2,&c3);
                    arman=1;ty=0;
                }

            }
            if(ty==0){
                FILE *ar= fopen(ARM,"w");
                fprintf(ar,"%c",'"');
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
                                            if(arman==0)printf("%d",init+1);
                                            else fprintf(ar,"%d",init+1);
                                        }
                                    }
                                    else if(cond == 1){
                                        true++;
                                        cnt1=init;
                                        while(hfile[cnt1-1]!=' ' && hfile[cnt1-1]!='\n' && cnt1>0){
                                            cnt1--;
                                        }
                                        if (num == true){
                                            if(arman==0)printf("%d",cnt1+1);
                                            else fprintf(ar,"%d",cnt1+1);
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
                                                            if(arman==0)printf("%d",init+1);
                                                            else fprintf(ar,"%d",init+1);
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
                        fclose(ar);
                        fclose(fp);
                        return -3;
                    }
                    if (true == 0){
                        printf("string not found\n");
                        fclose(ar);
                        fclose(fp);
                        return -3;
                    }
                    if(arman==0)printf("\n");
                    else fprintf(ar,"\n");
                    fprintf(ar,"%c%c",'"',EOF);
                    fclose(ar);
                    fclose(fp);
                    return -3;
                }
            }
        }
    }

    else if (mode == 0){
        FILE *ar= fopen(ARM,"w");
        fprintf(ar,"%c",'"');
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
                                if(arman==0)printf("%d\n",init+1);
                                else fprintf(ar,"%d\n",init+1);
                                fprintf(ar,"%c%c",'"',EOF);
                                fclose(fp);
                                fclose(ar);
                                return -3;

                            }
                            else if(cond == 1){
                                true++;
                                cnt1=init;
                                while(hfile[cnt1-1]!=' ' && hfile[cnt1-1]!='\n' && cnt1>0){
                                    cnt1--;
                                }
                                if(arman==0)printf("%d\n",cnt1+1);
                                else fprintf(ar,"%d\n",cnt1+1);
                                fprintf(ar,"%c%c",'"',EOF);
                                fclose(fp);
                                fclose(ar);
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
                                                if(arman==0)printf("%d\n",init+1);
                                                else fprintf(ar,"%d\n",init+1);
                                                fprintf(ar,"%c%c",'"',EOF);
                                                fclose(fp);
                                                fclose(ar);
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
            if(arman==0)printf("\n");
            else fprintf(ar,"\n");
            fprintf(ar,"%c%c",'"',EOF);
            fclose(ar);
            fclose(fp);
            return -3;
        }
    }

    return -1;
}

void replace(){
    char address[200]={0};
    char str1[1000] = {0};
    char str2[10000]={0};
    char st[30]={0};
    char file[30]={0};
    int cnt = 0;
    char c = 0;
    int cond = 0;
    int mode = 0;
    char all[30]={0};
    char mod[30]={0};


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

int grepFunc(char address[] , char str[] , int mode,FILE* armm){
    char row[1000]={0};
    int index;
    int res=0;
    char text[100][100];
    char c;
    for (int ii=0 ; ii<100 ; ii++){
        for (int jj=0 ; jj<100 ; jj++){
            text[ii][jj]=0;
        }
    }

    FILE *fp = fopen(address,"r+");
    if (fp == NULL){
        printf("File not found\n");
        fclose(armm);
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
    if (text[i][j] == EOF){
        text[i][j] = '\n';
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
                        if(arman==0)printf("%s: ",address);
                        else fprintf(armm,"%s: ",address);
                        while(text[count][j]!=0){
                            if(arman==0)printf("%c",text[count][j]);
                            else fprintf(armm,"%c",text[count][j]);
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
                        if(arman==0)printf("%s\n",address);
                        else fprintf(armm,"%s\n",address);
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
    for(int i=0 ; i<100; i++){
        for (int j=0 ; j<100 ; j++){
            address[i][j]=0;
        }
    }
    char str1[1000]={0};
    char st[30]={0};
    char op[10]={0};
    char file[30]={0};
    int cnt = 0;
    char c = 0;
    int mode = 0;

    scanf("%s ",op);
    if(arman==0){
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
    }
    else{
        if (strcmp(op,"--files")!=0){
            mode = 1;
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
            scanf("%s ",file);
            if(strcmp(file , "--files")!=0){
                printf("invalid command\n");
                return;
            }
        }
    }

    FILE* arm = fopen(ARM , "r");
    if(arman==0)scanf("%c",&c);
    else fscanf(arm,"%c",&c);
    if (c == '"'){
        char c1;
        if(arman==0)scanf("%c",&c);
        else fscanf(arm,"%c",&c);
        while(c!='"') {
            if (c == 92) {
                if(arman==0)scanf("%c",&c1);
                else fscanf(arm,"%c",&c1);
                if (c1 == '"') {
                    str1[cnt] = c1;
                    cnt++;
                    if(arman==0)scanf("%c",&c);
                    else fscanf(arm,"%c",&c);
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    if(arman==0)scanf("%c",&c);
                    else fscanf(arm,"%c",&c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                if(arman==0)scanf("%c",&c);
                else fscanf(arm,"%c",&c);
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
    if(arman==0) {
        scanf("%s ", file);
        if (strcmp(file, "--files") != 0) {
            printf("Invalid args\n");
            return;
        }
    }
    fclose(arm);
    c=1;

    int res=0;
    int i=0;
    scanf("%c",&c);
    while(c!='\n'){
        cnt=0;
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
        //printf(">%s<",address[i]);

        if(c==' ' && arman==0){
            char c1,c2,c3;
            scanf("%c",&c);
            if(c != '/' && c != '"'){
                scanf("%c%c",&c2,&c3);
                if(c=='=' && c2=='D' && c3==' '){
                    arman=1;
                }
            }
        }
        else{
            if(c==' ')scanf("%c",&c);
            arman=0;
        }

        i++;
        if(arman==1){
            c='\n';
        }
    }
    i=0;
    FILE* arr = fopen(ARM,"w");
    fprintf(arr,"%c",'"');
    while (address[i][0] != 0){
        res += grepFunc(address[i],str1,mode,arr);
        i++;
    }
    fprintf(arr,"%c%c",'"',EOF);
    fclose(arr);

    if (mode==1){
        FILE* ar = fopen(ARM,"w");
        fprintf(ar,"%c",'"');
        if(arman==0)printf("%d\n",res);
        else fprintf(ar,"%d\n",res);
        fprintf(ar,"%c%c",'"',EOF);
        fclose(ar);
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
    FILE* fi=fopen(address,"w");
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
    createUndo(address);
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
        scanf("%c",&c);
        strcpy(address2 , appendAddress(ADD , address2));
    }
    else{
        while(c != '\n' && c !=' '){
            if (c == '/'){
                c = '\\';
            }
            address2[cnt] = c;
            cnt++;
            scanf("%c",&c);
        }
        strcpy(address2 , appendAddress(ADD , address2));
    }

    FILE* arm=fopen(ARM,"w");
    if (c==' '){
        char c1,c2,c3;
        scanf("%c%c%c",&c1,&c2,&c3);
        if (c1!='=' || c2!='D' || c3!=' '){
            printf("invalid arguments\n");
            return;
        }
        arman=1;
        fprintf(arm,"%c",'"');
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
            if(arman==0)printf(">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n" , ii , line2);
            else fprintf(arm,">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n" , ii , line2);
            while (text2[j] !=0 && text2[j] !=EOF){
                if(arman==0)printf("%c",text2[j++]);
                else fprintf(arm,"%c",text2[j++]);
            }
            if(arman==0)printf("\n");
            else {
                fprintf(arm,"\n");
                fprintf(arm,"%c%c",'"',EOF);
                fclose(arm);
            }


            return;
        }
        else if(text2[j]==0){
            if(arman==0)printf("<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n" , ii , line1);
            else fprintf(arm,"<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n" , ii , line1);
            while (text[i] !=0 && text[i] !=EOF){
                if(arman==0)printf("%c",text[i++]);
                else fprintf(arm,"%c",text[i++]);
            }
            if(arman==0)printf("\n");
            else {
                fprintf(arm,"\n");
                fprintf(arm,"%c%c",'"',EOF);
                fclose(arm);
            }
            return;
        }
        else if (text[i] != text2[j]){
            if(arman==0)printf("============ #%d ============\n",ii);
            else fprintf(arm,"============ #%d ============\n",ii);
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
                    if(arman==0)printf("%c",l1[li]);
                    else fprintf(arm,"%c",l1[li]);
                    l1[li++]=0;
                }
                if (arman==0)printf("\n");
                else fprintf(arm,"\n");
                li=0;
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    if(arman==0)printf("%c",l2[lj]);
                    else fprintf(arm,"%c",l2[lj]);
                    l2[lj++]=0;
                }
                if(arman==0)printf("\n");
                else fprintf(arm,"\n");
                lj=0;
            }
            else{
                int word=1;
                while(l1[li] !=0 && l1[li] !=EOF){
                    if (l1[li] == ' '){
                        word++;
                    }
                    else if (li == 0 && res == 1){
                        if(arman==0)printf(">>");
                        else fprintf(arm,">>");
                        while (l1[li] != ' ' && l1[li] != 0){
                            if(arman==0)printf("%c",l1[li]);
                            else fprintf(arm,"%c",l1[li]);
                            l1[li++]=0;
                        }
                        if(arman==0)printf("<<");
                        else fprintf(arm,"<<");
                        continue;
                    }
                    else if(word == res){
                        if(arman==0)printf(">>");
                        else fprintf(arm,">>");
                        while (l1[li] != ' ' && l1[li] != 0){
                            if(arman==0)printf("%c",l1[li]);
                            else fprintf(arm,"%c",l1[li]);
                            l1[li++]=0;
                        }
                        if(arman==0)printf("<<");
                        else fprintf(arm,"<<");
                        continue;
                    }

                    if(arman==0)printf("%c",l1[li]);
                    else fprintf(arm,"%c",l1[li]);
                    l1[li++]=0;
                }
                if(arman==0)printf("\n");
                else fprintf(arm,"\n");
                li=0;

                word=1;
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    if (l2[lj] == ' '){
                        word++;
                    }
                    else if (lj == 0 && res == 1){
                        if(arman==0)printf(">>");
                        else fprintf(arm,">>");
                        while (l2[lj] != ' ' && l2[lj] != 0){
                            if(arman==0)printf("%c",l2[lj]);
                            else fprintf(arm,"%c",l2[lj]);
                            l2[lj++]=0;
                        }
                        if(arman==0)printf("<<");
                        else fprintf(arm,"<<");
                        continue;
                    }
                    else if(word == res){
                        if(arman==0)printf(">>");
                        else fprintf(arm,">>");
                        while (l2[lj] != ' ' && l2[lj] != 0){
                            if(arman==0)printf("%c",l2[lj]);
                            else fprintf(arm,"%c",l2[lj]);
                            l2[lj++]=0;
                        }
                        if(arman==0)printf("<<");
                        else fprintf(arm,"<<");
                        continue;
                    }

                    if(arman==0)printf("%c",l2[lj]);
                    else fprintf(arm,"%c",l2[lj]);
                    l2[lj++]=0;
                }

                if(arman==0)printf("\n");
                else fprintf(arm,"\n");
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
    if(arman==0)printf("\n");
    else fprintf(arm,"\n");

    fprintf(arm,"%c%c",'"',EOF);
    fclose(arm);

}

void tree(char *basePath, const int root,FILE* arm)
{
    int i;
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0 && root<depth*2 && undofinder(dp->d_name) == 0)
        {
            for (i=0; i<root; i++)
            {
                if (i%2 == 0 || i == 0) {
                    if (arman==0){
                        printf(ANSI_COLOR_CYAN"%c%s", 179, ANSI_COLOR_RESET);
                    }
                    else{
                        fprintf(arm,"%c", 179);
                    }

                }
                else {
                    if(arman==0)printf(" ");
                    else fprintf(arm," ");
                }

            }

            if(arman==0) {
                printf(ANSI_COLOR_CYAN"%c%c", 195, 196);
                printf(ANSI_COLOR_RED"%s\n%s", dp->d_name, ANSI_COLOR_RESET);
            }
            else{
                fprintf(arm,"%c%c", 195, 196);
                fprintf(arm,"%s\n", dp->d_name);
            }

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(path, root + 2,arm);
        }
    }
    closedir(dir);
}

void treefun(){
    char c;
    scanf("%d%c",&depth,&c);

    if (depth < -1){
        if (c=='\n'){
            printf("invalid depth\n");
            return;
        }
        else if(c== ' '){
            char c1,c2;
            scanf("%c%c",&c1,&c2);
            if (c1=='='&& c2=='D'){
                scanf("%c",&c);
                arman=1;
                FILE* arm=fopen(ARM,"r");
                fprintf(arm,"invalid depth\n");
                fclose(arm);
                return;
            }
            else{
                printf("invalid command\n");return;
            }
        }
    }

    if (c==' '){
        char c1,c2,c3;
        scanf("%c%c%c",&c1,&c2,&c3);
        if (c1=='=' && c2=='D' && c3==' '){
            arman=1;
        }
        else{
            printf("invalid args\n");
            return;
        }
    }

    if (depth == -1){
        depth = 50;
    }
    FILE* arm = fopen(ARM , "w");
    fprintf(arm,"%c",'"');
    tree(DIRE , 0,arm);
    fprintf(arm,"%c%c",'"',EOF);
    fclose(arm);
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
    if (strcmp(list , "tree")==0){
        return 14;
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

        else if (com == -1) {
            break;
        }

        else if (com == 2) {
            char dum;
            char file[30]={0};
            scanf("%s", file);
            scanf("%c", &dum);
            if (strcmp(file, "--file") == 0) {
                if (arman==0){
                    int rr = insert();
                }
                else if(arman==1){
                    arman=0;
                    int rr=insertarman();
                }

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        else if (com == 1 && arman==0) {
            char dum;
            char file[30];
            char address[200]={0};
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

        else if (com == 3 && arman==0){
            char dum;
            char file[30];
            char address[200]={0};
            scanf("%s ", file);
            if (strcmp(file, "--file") == 0) {
                char c;int cnt=0;
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
                if (c=='\n'){
                    //printf("%s",address);
                    cat(address);
                }
                else if (c == ' '){
                    char arm[4];
                    scanf("%s ", arm);
                    if(strcmp(arm,"=D")==0){
                        arman=1;
                        catarman(address);
                    }
                    else{
                        printf("invalid arguments\n");
                    }
                }

            } else {
                char c = 0;
                while (c != '\n') {
                    scanf("%c", &c);
                }
                printf("Invalid command\n");
            }
        }

        else if (com == 4 && arman==0) {
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

        else if (com == 5 && arman==0) {
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

        else if (com == 6 && arman==0){
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

        else if (com == 7 && arman==0){
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

        else if (com == 8){
            char dum;
            char str[30];
            scanf("%s ", str);
            if(arman==0){
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
            else{
                if (strcmp(str, "--file") == 0) {
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

        }
        else if (com == 9 && arman==0){
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

        else if (com == 10){
            grep();

        }

        else if (com == 11 && arman==0){
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


        else if (com == 12 && arman==0){
            indent();
        }

        else if (com == 13 && arman==0){
            compare();
        }

        else if (com == 14 && arman==0){
            treefun();
        }
        else{
            printf("invalid command\n");
        }
    }

    return 0;
}
