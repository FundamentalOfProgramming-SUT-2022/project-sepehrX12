#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
                break;
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
            if (c == '*'){
                break;
            }
            if (c == 92) {
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
                //printf("%c",c);
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

    if (cond == 1){
        //printf("%d",cond);
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
                            printf("File does not exist!");
                        }
                        else{
                            cnt=0;
                            int cnt1 =1;
                            int res;
                            int y=0;
                            char memo[1000];
                            int word = 0;
                            int word1 =0;
                            int u=0;
                            while((c = (char)fgetc(fp)) != EOF){
                                if (c == ' ' || c == '\n'){
                                    word++;
                                }
                                memo[cnt1]=c;
                                if (c != text[cnt]){
                                    y=0;
                                    cnt=0;
                                }
                                if (c == text[cnt]){
                                    if (y == 0){
                                        res = cnt1;
                                        word1 = word;
                                    }
                                    y=1;
                                    cnt++;
                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')){
                                    if (y==1){
                                        u++;
                                        if (u == 1){
                                            printf("%d" , word1);
                                        }
                                        else{
                                            printf(",%d" , word1);
                                        }
                                        cnt=0;
                                        y=0;
                                    }
                                    else{
                                        cnt=0;
                                        y=0;
                                    }

                                }

                                cnt1++;
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
                        int cnt1 =1;
                        int res;
                        int y=0;
                        char memo[1000];
                        int u=0;
                        while((c = (char)fgetc(fp)) != EOF){
                            memo[cnt1]=c;
                            if (c != text[cnt]){
                                y=0;
                                cnt=0;
                            }
                            if (c == text[cnt]){

                                if (y == 0){
                                    res = cnt1;
                                }
                                y=1;
                                cnt++;
                            }

                            if ((text[cnt] == 0 || text[cnt] == '\0')){
                                if (y==1){
                                    u++;
                                    int cnt2 = cnt1;
                                    while(cnt1 > 1 && memo[cnt1] != ' ' &&  memo[cnt1] != '\n'){
                                        cnt1--;
                                    }
                                    if (u == 1){
                                        printf("%d" , ++cnt1);
                                    }
                                    else{
                                        printf(",%d" , ++cnt1);
                                    }
                                    cnt1 = cnt2;
                                    cnt=0;
                                    y=0;
                                }
                                else{
                                    cnt=0;
                                    y=0;
                                }

                            }

                            cnt1++;
                        }
                        fclose(fp);
                        if (u==0){
                            return -1;
                        }
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
                        //printf("%s\n",address);
                        if (fp == NULL){
                            printf("File does not exist!");
                        }
                        else{
                            cnt=0;
                            int cnt1 =1;
                            int res;
                            int y=0;
                            char memo[1000];
                            int word=1;
                            int word1=1;
                            int final=0;
                            while((c = (char)fgetc(fp)) != EOF){
                                if (c == ' ' || c=='\n'){
                                    word++;
                                }
                                memo[cnt1]=c;
                                if (c != text[cnt]){
                                    y=0;
                                    cnt=0;
                                }
                                if (c == text[cnt]){

                                    if (y == 0){
                                        res = cnt1;
                                        word1=word;
                                    }
                                    y=1;
                                    cnt++;
                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')){
                                    if (y==1){
                                        cnt=0;
                                        y=0;
                                        int cnt2 = cnt1;
                                        final++;
                                        if (final == 1){
                                            printf("%d",word1);
                                        }
                                        else{
                                            printf(",%d",word1);
                                        }
                                        cnt1=cnt2;

                                    }
                                    else{
                                        cnt=0;
                                        y=0;
                                    }

                                }

                                cnt1++;
                            }
                            if (final > 0) {
                                printf("\n");
                                fclose(fp);
                                return -3;
                            }
                            return -1;
                        }
                    }
                    else if(strcmp(mod , "-at")==0){
                        int num;
                        scanf("%d",&num);
                        scanf("%c",&c);
                        FILE *fp;
                        fp = fopen(address, "r+");
                        //printf("%s\n",address);
                        if (fp == NULL){
                            printf("File does not exist!");
                        }
                        else{
                            cnt=0;
                            int cnt1 =1;
                            int res;
                            int y=0;
                            char memo[1000];
                            int u = 0;
                            int word = 1;
                            int word1 =1 ;
                            while((c = (char)fgetc(fp)) != EOF){
                                if (c == ' ' || c == '\n'){
                                    word++;
                                }
                                memo[cnt1]=c;
                                if (c != text[cnt]){
                                    y=0;
                                    cnt=0;
                                }
                                if (c == text[cnt]){
                                    if (y == 0){
                                        res = cnt1;
                                    }
                                    word1 = word;
                                    y=1;
                                    cnt++;
                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')){
                                    if (y==1){
                                        u++;
                                        cnt=0;
                                        y=0;
                                        while(cnt1 > 1 && memo[cnt1] != ' ' &&  memo[cnt1] != '\n'){
                                            cnt1--;
                                        }
                                        if (u == num){
                                            fclose(fp);
                                            return word1;
                                        }



                                    }
                                    else{
                                        cnt=0;
                                        y=0;
                                    }

                                }

                                cnt1++;
                            }
                            fclose(fp);
                            return -1;
                        }

                    }
                    return -1;
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
                        int cnt1 =1;
                        int res;
                        int y=0;
                        char memo[1000];
                        int word=1;
                        int word1=1;
                        while((c = (char)fgetc(fp)) != EOF){
                            if (c == ' ' || c=='\n'){
                                word++;
                            }
                            memo[cnt1]=c;
                            if (c != text[cnt]){
                                y=0;
                                cnt=0;
                            }
                            if (c == text[cnt]){

                                if (y == 0){
                                    res = cnt1;
                                    word1=word;
                                }
                                y=1;
                                cnt++;
                            }

                            if ((text[cnt] == 0 || text[cnt] == '\0')){
                                if (y==1){
                                    cnt=0;
                                    y=0;
                                    fclose(fp);
                                    return word1;
                                }
                                else{
                                    cnt=0;
                                    y=0;
                                }

                            }

                            cnt1++;
                        }
                        fclose(fp);
                        return -1;
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
                    int cnt1 = 1;
                    int res;
                    int y = 0;
                    char memo[1000];
                    int u = 0;
                    while ((c = (char) fgetc(fp)) != EOF) {
                        memo[cnt1] = c;
                        if (c != text[cnt]) {
                            y = 0;
                            cnt = 0;
                        }
                        if (c == text[cnt]) {

                            if (y == 0) {
                                res = cnt1;
                            }
                            y = 1;
                            cnt++;
                        }

                        if ((text[cnt] == 0 || text[cnt] == '\0')) {
                            if (y == 1) {
                                while (cnt1 > 1 && memo[cnt1] != ' ' && memo[cnt1] != '\n') {
                                    cnt1--;
                                }
                                u++;
                                cnt = 0;
                                y = 0;
                            } else {
                                cnt = 0;
                                y = 0;
                            }

                        }

                        cnt1++;
                    }
                    fclose(fp);
                    return u;
                }
                return -1;

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
                            int cnt1 =1;
                            int res;
                            int y=0;
                            char memo[1000];
                            int u = 0;
                            int word = 1;
                            int word1 =1 ;
                            int final = 0;
                            while((c = (char)fgetc(fp)) != EOF){
                                if (c == ' ' || c == '\n'){
                                    word++;
                                }
                                memo[cnt1]=c;
                                if (c != text[cnt]){
                                    y=0;
                                    cnt=0;
                                }
                                if (c == text[cnt]){
                                    if (y == 0){
                                        res = cnt1;
                                    }
                                    word1 = word;
                                    y=1;
                                    cnt++;
                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')){
                                    if (y==1){
                                        u++;
                                        cnt=0;
                                        y=0;
                                        while(cnt1 > 1 && memo[cnt1] != ' ' &&  memo[cnt1] != '\n'){
                                            cnt1--;
                                        }
                                        if (u == num){
                                            fclose(fp);
                                            return word1;
                                        }



                                    }
                                    else{
                                        cnt=0;
                                        y=0;
                                    }

                                }

                                cnt1++;
                            }
                            fclose(fp);
                            if (final == 0){
                                return -1;
                            }
                            return -1;
                        }
                    }
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
                        int cnt1 =1;
                        int res;
                        int y=0;
                        char memo[1000];
                        int u = 0;
                        while((c = (char)fgetc(fp)) != EOF){
                            memo[cnt1]=c;
                            if (c != text[cnt]){
                                y=0;
                                cnt=0;
                            }
                            if (c == text[cnt]){

                                if (y == 0){
                                    res = cnt1;
                                }
                                y=1;
                                cnt++;
                            }

                            if ((text[cnt] == 0 || text[cnt] == '\0')){
                                if (y==1){
                                    u++;
                                    cnt=0;
                                    y=0;
                                    if (u == num){
                                        while(cnt1 > 1 && memo[cnt1] != ' ' &&  memo[cnt1] != '\n'){
                                            cnt1--;
                                        }
                                        fclose(fp);
                                        return cnt1;
                                    }

                                }
                                else{
                                    cnt=0;
                                    y=0;
                                }

                            }

                            cnt1++;
                        }
                        fclose(fp);
                        return -1;
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
                int cnt1 =1;
                int res;
                int y=0;
                char memo[1000];
                while((c = (char)fgetc(fp)) != EOF){
                    memo[cnt1]=c;
                    if (c != text[cnt]){
                        y=0;
                        cnt=0;
                    }
                    if (c == text[cnt]){

                        if (y == 0){
                            res = cnt1;
                        }
                        y=1;
                        cnt++;
                    }

                    if ((text[cnt] == 0 || text[cnt] == '\0')){
                        if (y==1){
                            while(cnt1 > 1 && memo[cnt1] != ' ' &&  memo[cnt1] != '\n'){
                                cnt1--;
                            }
                            fclose(fp);
                            return ++cnt1;
                        }
                        else{
                            cnt=0;
                            y=0;
                        }

                    }

                    cnt1++;
                }
                fclose(fp);
            }
        }


    }



    else {
        cnt = 0;
        char c1;
        scanf("%c", &c);
        if (c == '"') {
            scanf("%c", &c);
            while (c != '"') {
                address[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }
            scanf("%c", &c);
            strcpy(address, appendAddress(ADD, address));
            if (c == '\n') {
                mode = 0;
            } else if (c == ' ') {
                mode = 1;
            }
        } else {
            while (c != ' ' && c != '\n') {
                address[cnt] = c;
                cnt++;
                scanf("%c", &c);
            }
            if (c == '\n') {
                mode = 0;
            } else if (c == ' ') {
                mode = 1;
            }
            strcpy(address, appendAddress(ADD, address));
        }

        if (mode != 0) {
            int shom = 0;
            scanf("%c", &c);
            while (c != '\n' && c != ' '){
                all[shom]=c;
                scanf("%c", &c);
                shom++;
            }
            all[shom] = '\0';
            //printf("%s",all);

            if (strcmp(all, "-all") == 0) {
                if (c == ' '){
                    scanf("%s", mod);
                    if (strcmp(mod, "-byword") == 0) {

                        FILE *fp;
                        fp = fopen(address, "r+");
                        //printf("%s\n",address);
                        if (fp == NULL) {
                            printf("File does not exist!");
                        } else {
                            cnt = 0;
                            int cnt1 = 1;
                            int res = 0;
                            int y = 0;
                            int rr = 1;
                            int u = 0;
                            while ((c = (char) fgetc(fp)) != EOF) {
                                if (c == ' ' || c == '\n') {
                                    rr++;
                                }
                                if (c != text[cnt]) {
                                    y = 0;
                                    cnt = 0;
                                }
                                if (c == text[cnt]) {
                                    //printf("%c",c);
                                    //printf("\n%s",text);
                                    if (y == 0) {
                                        res = cnt1;
                                    }
                                    y = 1;
                                    cnt++;

                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                    if (y == 1) {
                                        u ++;
                                        cnt = 0;
                                        y = 0;
                                        if (u == 1){
                                            printf("%d",rr);
                                        }
                                        else{
                                            printf(",%d",rr);
                                        }


                                    } else {
                                        cnt = 0;
                                        y = 0;
                                    }

                                }

                                cnt1++;
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
                    //printf("%s\n",address);
                    if (fp == NULL) {
                        printf("File does not exist!");
                    } else {
                        cnt = 0;
                        int cnt1 = 1;
                        int res;
                        int y = 0;
                        int u =0;
                        while ((c = (char) fgetc(fp)) != EOF) {
                            if (c != text[cnt]) {
                                y = 0;
                                cnt = 0;
                            }
                            if (c == text[cnt]) {
                                //printf("%c",c);
                                //printf("\n%s",text);
                                if (y == 0) {
                                    res = cnt1;
                                }
                                y = 1;
                                cnt++;

                            }

                            if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                if (y == 1) {
                                    cnt = 0;
                                    y = 0;
                                    u++;
                                    if (u == 1){
                                        printf("%d",res) ;
                                    }
                                    else{
                                        printf(",%d",res) ;
                                    }
                                } else {
                                    cnt = 0;
                                    y = 0;
                                }

                            }

                            cnt1++;
                        }
                        printf("\n");
                        fclose(fp);
                        return -3;
                    }
                }
            }

            else if (strcmp(all, "-count") == 0) {
                FILE *fp;
                fp = fopen(address, "r+");
                //printf("%s\n",address);
                if (fp == NULL) {
                    printf("File does not exist!");
                } else {
                    cnt = 0;
                    int cnt1 = 1;
                    int res = 0;
                    int y = 0;
                    while ((c = (char) fgetc(fp)) != EOF) {
                        if (c != text[cnt]) {
                            y = 0;
                            cnt = 0;
                        }
                        if (c == text[cnt]) {
                            //printf("%c",c);
                            //printf("\n%s",text);
                            y = 1;
                            cnt++;

                        }

                        if ((text[cnt] == 0 || text[cnt] == '\0')) {
                            if (y == 1) {
                                res++;
                                cnt = 0;
                                y = 0;
                            } else {
                                cnt = 0;
                                y = 0;
                            }

                        }

                        cnt1++;
                    }
                    fclose(fp);
                    return res;
                }
            }

            else if (strcmp(all, "-at") == 0) {
                int num;
                scanf("%d", &num);
                scanf("%c",&c);
                if (c == ' '){
                    scanf("%s", mod);
                    if (strcmp(mod,"-byword") == 0){
                        FILE *fp;
                        fp = fopen(address, "r+");
                        //printf("%s\n",address);
                        if (fp == NULL) {
                            printf("File does not exist!");
                        } else {
                            cnt = 0;
                            int cnt1 = 1;
                            int res = 0;
                            int y = 0;
                            int rr = 0;
                            int space = 0;
                            while ((c = (char) fgetc(fp)) != EOF) {
                                if (c==' ' || c=='\n'){
                                    space++;
                                }
                                if (c != text[cnt]) {
                                    y = 0;
                                    cnt = 0;
                                }
                                if (c == text[cnt]) {
                                    //printf("%c",c);
                                    //printf("\n%s",text);
                                    if (y == 0) {
                                        res = cnt1;
                                    }
                                    y = 1;
                                    cnt++;

                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                    if (y == 1) {
                                        rr++;
                                        if (rr == num) {
                                            fclose(fp);
                                            return ++space;
                                        }
                                        cnt = 0;
                                        y = 0;
                                    } else {
                                        cnt = 0;
                                        y = 0;
                                    }

                                }

                                cnt1++;
                            }
                            fclose(fp);
                            return -1;
                        }
                    }
                    return -1;
                }
                else{
                    FILE *fp;
                    fp = fopen(address, "r+");
                    //printf("%s\n",address);
                    if (fp == NULL) {
                        printf("File does not exist!");
                    } else {
                        cnt = 0;
                        int cnt1 = 1;
                        int res = 0;
                        int y = 0;
                        int rr = 0;
                        while ((c = (char) fgetc(fp)) != EOF) {
                            if (c != text[cnt]) {
                                y = 0;
                                cnt = 0;
                            }
                            if (c == text[cnt]) {
                                //printf("%c",c);
                                //printf("\n%s",text);
                                if (y == 0) {
                                    res = cnt1;
                                }
                                y = 1;
                                cnt++;

                            }

                            if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                if (y == 1) {
                                    rr++;
                                    if (rr == num) {
                                        fclose(fp);
                                        return res;
                                    }
                                    cnt = 0;
                                    y = 0;
                                } else {
                                    cnt = 0;
                                    y = 0;
                                }

                            }

                            cnt1++;
                        }
                        fclose(fp);
                        return -1;
                    }
                }
                return -1;

            }

            else if (strcmp(all, "-byword") == 0) {

                if (c == ' '){
                    scanf("%s", mod);
                    if (strcmp(mod, "-all") == 0) {
                        FILE *fp;
                        fp = fopen(address, "r+");
                        //printf("%s\n",address);
                        if (fp == NULL) {
                            printf("File does not exist!");
                        } else {
                            cnt = 0;
                            int cnt1 = 1;
                            int res = 0;
                            int y = 0;
                            int rr = 1;
                            int u = 0;
                            while ((c = (char) fgetc(fp)) != EOF) {
                                if (c == ' ' || c == '\n') {
                                    rr++;
                                }
                                if (c != text[cnt]) {
                                    y = 0;
                                    cnt = 0;
                                }
                                if (c == text[cnt]) {
                                    //printf("%c",c);
                                    //printf("\n%s",text);
                                    if (y == 0) {
                                        res = cnt1;
                                    }
                                    y = 1;
                                    cnt++;

                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                    if (y == 1) {
                                        u++;
                                        cnt = 0;
                                        y = 0;
                                        if (u == 1){
                                            printf("%d",rr);
                                        }
                                        else{
                                            printf(",%d",rr);
                                        }


                                    } else {
                                        cnt = 0;
                                        y = 0;
                                    }

                                }

                                cnt1++;
                            }
                            printf("\n");
                            fclose(fp);
                            return -3;
                        }
                    }
                    else if (strcmp(mod, "-at") == 0){
                        int num;
                        scanf("%d", &num);
                        //printf("%d",num);
                        FILE *fp;
                        fp = fopen(address, "r+");
                        //printf("%s\n",address);
                        if (fp == NULL) {
                            printf("File does not exist!");
                        } else {
                            cnt = 0;
                            int cnt1 = 1;
                            int res = 0;
                            int y = 0;
                            int rr = 0;
                            int space = 0;
                            while ((c = (char) fgetc(fp)) != EOF) {
                                if (c==' ' || c == '\n'){
                                    space++;
                                }
                                if (c != text[cnt]) {
                                    y = 0;
                                    cnt = 0;
                                }
                                if (c == text[cnt]) {
                                    //printf("%c",c);
                                    //printf("\n%s",text);
                                    if (y == 0) {
                                        res = cnt1;
                                    }
                                    y = 1;
                                    cnt++;

                                }

                                if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                    if (y == 1) {
                                        rr++;
                                        if (rr == num) {
                                            fclose(fp);
                                            return ++space;
                                        }
                                        cnt = 0;
                                        y = 0;
                                    } else {
                                        cnt = 0;
                                        y = 0;
                                    }

                                }

                                cnt1++;
                            }
                            fclose(fp);
                            return -1;
                        }
                    }
                    return -1;
                }
                else{
                    FILE *fp;
                    fp = fopen(address, "r+");
                    //printf("%s\n",address);
                    if (fp == NULL) {
                        printf("File does not exist!");
                    } else {
                        cnt = 0;
                        int cnt1 = 1;
                        int res = 0;
                        int y = 0;
                        int rr = 0;
                        while ((c = (char) fgetc(fp)) != EOF) {
                            if (c == ' ' || c == '\n') {
                                rr++;
                            }
                            if (c != text[cnt]) {
                                y = 0;
                                cnt = 0;
                            }
                            if (c == text[cnt]) {
                                //printf("%c",c);
                                //printf("\n%s",text);
                                if (y == 0) {
                                    res = cnt1;
                                }
                                y = 1;
                                cnt++;

                            }

                            if ((text[cnt] == 0 || text[cnt] == '\0')) {
                                if (y == 1) {
                                    rr++;
                                    return rr;
                                    fclose(fp);
                                } else {
                                    cnt = 0;
                                    y = 0;
                                }

                            }

                            cnt1++;
                        }
                        fclose(fp);
                        return -1;
                    }
                }

            }

        }

        if (mode == 0) {
            FILE *fp;
            fp = fopen(address, "r+");
            //printf("%s\n",address);
            if (fp == NULL) {
                printf("File does not exist!");
            } else {
                cnt = 0;
                int cnt1 = 1;
                int res;
                int y = 0;
                while ((c = (char) fgetc(fp)) != EOF) {
                    if (c != text[cnt]) {
                        y = 0;
                        cnt = 0;
                    }
                    if (c == text[cnt]) {
                        //printf("%c",c);
                        //printf("\n%s",text);
                        if (y == 0) {
                            res = cnt1;
                        }
                        y = 1;
                        cnt++;

                    }

                    if ((text[cnt] == 0 || text[cnt] == '\0')) {
                        if (y == 1) {
                            fclose(fp);
                            return res;
                        } else {
                            cnt = 0;
                            y = 0;
                        }

                    }

                    cnt1++;
                }
                fclose(fp);
            }
        }
    }

    return -1;
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
    }

    return 0;
}
