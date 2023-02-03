#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <dirent.h>
#include <curses.h>


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
char* OUTP = "F:\\Uni\\Fop\\Project\\out.txt";
int arman=0;
int out=0;


#define LINE 36
#define COL 140
int mode;
int savebool;
char* filename;
char* textnew;char* text;int len;
char* varr;
char* over;
char* clipb = (char*)calloc(10000 , sizeof(char));
char* findtext = (char*)calloc(100,sizeof(char));
int* findindex = (int*)calloc(1000,sizeof(int));
char location[200]={0};

int indexx=0;int visx=0;int gloi=0;int bot=0;int gloj;
int indexy=0;int vixy=0;int top=0;int quit=0;

char* flname(char* name){
    char* heh=(char*)calloc(100,sizeof(char));
    int i=0;
    while(name[i]!='.')i++;
    while(name[i]!=92 && name[i]!='/')i--;
    i++;int j=0;
    while(name[i]!=0){
        heh[j++]=name[i++];
    }
    heh[j]='\0';
    if(strcmp(heh,"out.txt")==0){
        for(int j=0 ; j<100 ; j++)heh[j]=0;
        heh[0]=' ';
        return heh;
    }
    return heh;
}

char* stringfunction(WINDOW* win){
    int counter=0;char c;char *string=(char*)calloc(100,sizeof(char));
    while (1) {
        c=wgetch(win);
        if (c == ' ') {
            wprintw(win , "%c",c);wrefresh(win);
            return string;
            break;
        }
        if (c == '\n') {
            return string;
            break;
        }
        wprintw(win , "%c",c);wrefresh(win);
        string[counter] = c;
        counter++;
    }string[counter]='\0';
}

int numfunc(WINDOW* win){
    int a;int b=0;char c;
    while (1) {
        c=wgetch(win);
        if (c == ' ') {
            wprintw(win , "%c",c);wrefresh(win);
            return b;
            break;
        }
        if (c == '\n') {
            return b;
            break;
        }
        if (c == ':') {
            wprintw(win , "%c",c);wrefresh(win);
            return b;
            break;
        }
        wprintw(win , "%c",c);wrefresh(win);
        a = (int)(c-48);
        b=b*10+a;
    }
}

void scrprint(char* list , WINDOW* win , int mode , char* filename , int savebool){
    int i=0;int l=1;int chh=0;
    while(i/COL != top){
        if(over[i]=='\n')l++;
        i++;
    }
    int ch=0;
    i=0;
    int x;int y;
    getyx(win , y ,x);
    box(win , 0 ,0);
    start_color();
    init_pair(5 , 3 , 0);
    init_pair(6 , 4 , 0);
    init_pair(7 , 5 , 0);

    while(i<LINE){
        if(*(list + i*COL )==0){
            break;
        }
        if(ch==1 || i==0){
            mvwprintw(win , i+1 ,3 ,"%d" , l);ch=0;
        }
        else{
        }


        int j=0;
        while (j < COL && *(list + i*COL + j) !=0){
            if(*(list + i*COL + j) == '\n'){
                l++;ch=1;
                j=COL;
            }
            else{
                if( *(list + i*COL + j) == '{' || *(list + i*COL + j) == '}'){
                    wattron(win,COLOR_PAIR(5));
                    mvwprintw(win , i+1 ,6+j ,"%c" , *(list + i*COL + j));
                    wattroff(win,COLOR_PAIR(5));
                    j++;
                }
                else if( *(list + i*COL + j) == '[' || *(list + i*COL + j) == ']'){
                    wattron(win,COLOR_PAIR(6));
                    mvwprintw(win , i+1 ,6+j ,"%c" , *(list + i*COL + j));
                    wattroff(win,COLOR_PAIR(6));
                    j++;
                }
                else if( *(list + i*COL + j) == '(' || *(list + i*COL + j) == ')'){
                    wattron(win,COLOR_PAIR(7));
                    mvwprintw(win , i+1 ,6+j ,"%c" , *(list + i*COL + j));
                    wattroff(win,COLOR_PAIR(7));
                    j++;
                }
                else{
                    mvwprintw(win , i+1 ,6+j ,"%c" , *(list + i*COL + j));
                    j++;
                }
            }
        }
        j=0;
        i++;
    }

    init_pair(1 , 3 , 0);

    wattron(win,COLOR_PAIR(1));
    while(i<LINE-4){
        mvwprintw(win , i+1 ,1 ,"~");
        i++;
    }
    wattroff(win,COLOR_PAIR(1));

    int j=0;
    if(mode==0){
        j+=8;
        init_pair(2, 0 ,3);
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win , i+1 ,1 ," NORMAL ");
        wattroff(win,COLOR_PAIR(2));

    }
    else if(mode==1){
        j+=8;
        init_pair(2, 0 ,5);
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win , i+1 ,1 ," VISUAL ");
        wattroff(win,COLOR_PAIR(2));

    }
    else if(mode==2){
        j+=8;
        init_pair(2 , 0 , 2);
        wattron(win,COLOR_PAIR(2));
        mvwprintw(win , i+1 ,1 ," INSERT ");
        wattroff(win,COLOR_PAIR(2));
    }

    init_pair(3 , 0 , 8);
    wattron(win,COLOR_PAIR(3));
    i=0;
    wprintw(win ," ");j++;
    while(filename[i]!=0){
        wprintw(win ,"%c" , filename[i]);
        i++;j++;
    }
    wprintw(win ," ");j++;
    if(savebool==0){
        j+=2;
        wprintw(win ,"+ " );
    }
    wattroff(win,COLOR_PAIR(3));


    init_color(20 , 240 , 230 , 235);
    init_pair(4 , 0 , 20);
    wattron(win,COLOR_PAIR(4));
    while(j<COL+5){
        wprintw(win ," " );
        j++;
    }
    wattroff(win,COLOR_PAIR(4));
    wmove(win , y ,x);

}

char *appendAddress(char str1[], char str2[]) {
    char *fin = (char*)calloc(1000, sizeof(char));
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

char* readfile(char address[]){
    FILE* fp = fopen(address , "r+");
    if(fp==NULL){
        printf("file not found");
    }
    char* list = (char*)calloc(10000 , sizeof(char));
    char c;int j=0;
    while((c = getc(fp)) != EOF){
        list[j]=c;
        j++;
    }
    fclose(fp);
    return list;
}

char* overallarray(WINDOW* win , char* list){
    int i=0;
    int x=0;int y=0;
    char* arr = (char*)calloc(1000*(COL) , sizeof(char));
    while(list[i] != 0){
        if(list[i]=='\n'){
            arr[y*COL+x] = list[i];
            y = (y*COL+x)/COL+1;
            x=0;i++;continue;
        }
        arr[y*COL+x] = list[i];
        i++;x++;
    }
    return arr;
}

char* visualarray(WINDOW* win , char* list){
    char* varrr = (char*)calloc(COL*LINE , sizeof(char));
    int i=top; int j=0;
    while(i-top<LINE-4 && *(list+COL*i) !=0){
        while(*(list+COL*i+j) != 0 && j<COL){
            *(varrr+(i-top)*COL + j) = *(list+(i)*COL + j) ;
            j++;
        }
        j=0;
        i++;
    }
    bot = i-top;
    return varrr;
}

void textn(){
    char* textnn = (char*)calloc(COL*LINE , sizeof(char));
    int i=0; int j=0;int count =0;
    while( *(varr+COL*i) !=0){
        while(*(varr+COL*i+j) != 0 && j<COL){
            *(textnn+count) = *(varr+(i)*COL + j) ;
            j++;count++;
        }
        j=0;
        i++;
    }
    textnew = textnn;i=0;
}

int* convert(){
    int x=0;int y=0;int count=0;
    int * pos = (int*)malloc(2*sizeof(int));
    while(textnew[count] != 0){
        if (gloi == count){
            pos[0] = y;pos[1] = x;
            return pos;
        }
        if(textnew[count]=='\n' || x>COL-2){
            y = y+1;
            x=0;count++;continue;
        }
        count++;x++;
    }
}

int kfun(char* text){
    int i=1;
    while(text[i-1] != '\n' && i-1<COL-1 && text[i-1] != 0){
        i++;
    }
    return i;
}

void navigate(WINDOW* win , char c){
    int x;int* pos;
    int y;
    getyx(win , y ,x);
    if(c == 'h'){
        if(gloi != 0 && textnew[gloi-1] != '\n'){
            gloi--;
            int *pos = convert();
            wmove(win , 1+pos[0] , 6+pos[1]);
            wrefresh(win);
            return;
        }
    }
    else if(c == 'l'){
        if(textnew[gloi]=='\n'){
            return;
        }
        if(textnew[gloi+1] != 0 && textnew[gloi+1] != '\n'){
            gloi++;
            int *pos = convert();
            wmove(win , 1+pos[0] , 6+pos[1]);
            wrefresh(win);
            return;
        }
    }
    else if(c == 'j'){
        pos = convert();int cond=0;
        if(1+pos[0] < 5 && top> 0){
            top--;
            (varr) = (visualarray(win , over));
            textn();
            wclear(win);clear();
            scrprint(varr , win , mode , filename , savebool);gloi= gloi + kfun(varr);
        }
        if(gloi==0)return;
        int ii=gloi;int diff;if(textnew[gloi]=='\n')ii--;
        while(ii !=-1 && textnew[ii] != '\n'){
            ii--;
        }
        if(ii <= 0){
            return;
        }
        if(textnew[ii-1]==-1 || textnew[ii-1]=='\n'){
            gloi = ii;
            int* pos = convert();
            wmove(win , 1+pos[0] , 6+pos[1]);
            wrefresh(win);
            return;
        }

        diff = gloi-ii;
        ii--;
        while(ii !=-1 && textnew[ii] != '\n'){
            ii--;
        }
        int u=ii;
        ii++;

        while(textnew[ii] != '\n'){
            if(ii-u == diff){
                gloi = ii;
                int* pos = convert();
                wmove(win , 1+pos[0] , 6+pos[1]);
                wrefresh(win);
                return;
            }
            ii++;
        }
        ii--;
        gloi=ii;
        int* pos = convert();
        wmove(win , 1+pos[0] , 6+pos[1]);
        wrefresh(win);
        gloi = ii;return;
    }
    else if(c == 'k'){
        pos = convert();int cond=0;
        if(1+pos[0] > LINE-8 && bot> LINE-7){
            top++;gloi= gloi - kfun(varr);
            (varr) = (visualarray(win , over));
            textn();
            wclear(win);clear();
            scrprint(varr , win , mode , filename , savebool);
        }
        int ii=gloi;int diff;ii--;
        while(ii >=0 && textnew[ii] != '\n'){
            ii--;
        }
        diff = gloi-ii;
        ii++;
        while(textnew[ii] !=0 && textnew[ii] != '\n'){
            ii++;
        }
        if(textnew[ii] == 0 || textnew[ii+1]==0){
            return;
        }
        ii++;
        int u=ii-1;
        int ch=0;

        while(textnew[ii] != '\n'){
            ch=1;
            if(ii-u == diff){
                gloi = ii;
                pos = convert();
                wmove(win , 1+pos[0] , 6+pos[1]);
                wrefresh(win);
                return;
            }
            ii++;
        }
        gloi = ii;if(ch==1)gloi=ii-1;
        pos = convert();
        wmove(win , 1+pos[0] , 6+pos[1]);
        wrefresh(win);
        return;
    }
}

void commhandlern(WINDOW* win ,char c){

}

void highlight(WINDOW* win){
    int* pos = convert();int u=gloi;int ii=0;
    init_pair(8 , 0 , 3);gloi=gloj;
    wattron(win,COLOR_PAIR(8));
    mvwprintw(win , 1+pos[0] , 6+pos[1] ,"%c" , textnew[gloi]);gloi=u;
    if (gloi > gloj){gloi=gloj;
        for(int i=0 ; i<(u-gloj)+1 ; i++){
            int* pos = convert();
            if(textnew[gloi]!='\n')mvwprintw(win , 1+pos[0] , 6+pos[1] ,"%c" , textnew[gloi]);
            else mvwprintw(win , 1+pos[0] , 6+pos[1] ," ");
            gloi++;
        }
    }
    else if(gloi < gloj){gloi=gloj;
        for(int i=0 ; i<(gloj-u)+1 ; i++){
            int* pos = convert();
            if(textnew[gloi]!='\n')mvwprintw(win , 1+pos[0] , 6+pos[1] ,"%c" , textnew[gloi]);
            else mvwprintw(win , 1+pos[0] , 6+pos[1] ," ");
            gloi--;
        }
    }
    gloi=u;
    wattroff(win , COLOR_PAIR(8));
    pos = convert();
    wmove(win , 1+pos[0] , 6+pos[1]);wrefresh(win);
}

void clipfun(){
    for(int i=0 ; i<10000 ; i++){
        clipb[i]=0;
    }int ii;
    if(gloi>gloj){
        ii=gloj;
        for(int i=0 ; i<gloi-gloj+1 ; i++){
            clipb[i]=textnew[ii];ii++;
        }
    }
    else if(gloi<gloj){
        ii=gloi;
        for(int i=0 ; i<gloj-gloi+1 ; i++){
            clipb[i]=textnew[ii];ii++;
        }
    }
    else{
        clipb[0]=textnew[gloi];
    }
}

void modev(WINDOW* win){
    gloj=gloi;
    char c;wrefresh(win);
    while(1){
        wclear(win);
        scrprint(varr , win , mode , filename , savebool);
        highlight(win);wrefresh(win);
        c=wgetch(win);

        if(c=='h' || c=='j' || c=='k' || c=='l'){
            navigate(win , c );wrefresh(win);
        }
        else if(c=='d'){
            savebool=0;
            clipfun();
            char* temp = (char*)calloc(10000 , sizeof(char));int co=0;int ln=0;int j=0;
            if(gloj>gloi){
                while(ln<top){
                    temp[co]=text[co];
                    if(text[co]=='\n' || j==COL){
                        ln++;co++;j=0;continue;
                    }
                    j++;co++;
                }int coo=co;
                while(co-coo<gloi){
                    temp[co]=text[co];
                    co++;
                }
                while(text[co+gloj-gloi+1]!=0){
                    temp[co]=text[co-coo+gloj-gloi+1];
                    co++;
                }
                text=temp;
                over = overallarray(win , text);
                varr = visualarray(win , over);
                textn();

            }
            else{
                while(ln<top){
                    temp[co]=text[co];
                    if(text[co]=='\n' || j==COL){
                        ln++;co++;j=0;continue;
                    }
                    j++;co++;
                }int coo=co;
                while(co-coo<gloj){
                    temp[co]=text[co];
                    co++;
                }
                while(text[co+gloi-gloj+1]!=0){
                    temp[co]=text[co+gloi-gloj+1];
                    co++;
                }
                text=temp;
                over = overallarray(win , text);
                varr = visualarray(win , over);
                textn();
            }gloi=0;
            wclear(win);
            wmove(win , 1 , 6);
            mode=0;return;
        }
        else if(c=='y'){
            clipfun();
            mode = 0;return;
        }

        else{
            if(c=='i'){
                mode=2;return;
            }
            else if(c== 'q'){
                printf("%c" , textnew[gloi]);
                quit=1;return;
            }
        }
    }
}

void modei(WINDOW* win){
    char c;
    while(1){
        savebool=0;
        scrprint(varr , win , mode , filename , savebool);
        int* pos = convert();
        wmove(win , 1+pos[0] , 6+pos[1]);
        wrefresh(win);
        keypad(win , 1);
        c=wgetch(win);
        if(c == 27){
            mode=0;
            return;
        }
        char* temp = (char*)calloc(10000 , sizeof(char));int co=0;int ln=0;int j=0;
        while(ln<top){
            temp[co]=text[co];
            if(text[co]=='\n' || j==COL){
                ln++;co++;j=0;continue;
            }
            j++;co++;
        }int coo=co;
        while(co-coo<gloi){
            temp[co]=text[co];
            co++;
        }
        temp[co++]=c;
        while(text[co-1]!=0){
            temp[co]=text[co-1];co++;
        }
        text=temp;gloi++;
        over = overallarray(win , text);
        varr = visualarray(win , over);
        textn();
        wclear(win);
    }
}

void findnext(WINDOW* win , int ci){
    if(text[findindex[ci]] != findtext[0])return;
    int ln=0;int co=0;int j=0;int coo=0;

    while(co!=findindex[ci]){
        if(text[co]=='\n' || j==COL){
            ln++;co++;j=0;coo=co;continue;
        }

        j++;co++;
    }
    top=ln;

    (varr) = (visualarray(win , over));
    textn();
    wclear(win);clear();
    scrprint(varr , win , mode , filename , savebool);

    int glj=co-coo;


    int ind=0;j=0;co=coo;

    while(findindex[ind]<coo){
        ind++;
    }
    while(ln<=top+32){
        if(text[co]=='\n' || j==COL){
            ln++;co++;j=0;continue;
        }
        if(co==findindex[ind] && text[co]==findtext[0]){
            int cop=co;
            for(int s=0 ; s<len+1 ; s++){
                gloi=co-coo;
                int* pos = convert();
                init_pair(9 , 0 ,10);
                wattron(win,COLOR_PAIR(9));
                mvwprintw(win , pos[0]+1 ,6+pos[1] ,"%c" , text[co]);
                wattroff(win,COLOR_PAIR(9));
                co++;
            }
            ind++;co=cop;
        }
        j++;co++;
    }
    gloi=glj;
    int* po=convert();
    wmove(win , po[0]+1 , 6+po[1]);
    wrefresh(win);
}

void find2(WINDOW* win){

    mvwprintw(win ,LINE-2 , 2, "/");wrefresh(win);
    char c=wgetch(win);int co=0;int ind=0;int i=0;
    while(c!='\n'){
        findtext[co] = c;
        mvwprintw(win ,LINE-2 , 3+co, "%c",c);wrefresh(win);
        c = wgetch(win);
        co++;
    }
    len=co-1;
    co=0;
    while(text[i]!=0){
        int ii=i;
        while(text[i]==findtext[co]){

            if(findtext[co+1]==0){
                findindex[ind++]=ii;
            }
            i++;co++;
        }
        co=0;i=ii;
        i++;
    }
    int ln=0;co=0;int j=0;
    while(ln<top){
        if(text[co]=='\n' || j==COL){
            ln++;co++;j=0;continue;
        }
        j++;co++;
    }int coo=co;ind=0;int loj=gloi;

    while(findindex[ind]<coo){
        ind++;
    }
    while(ln<=top+32){
        if(text[co]=='\n' || j==COL){
            ln++;co++;j=0;continue;
        }
        if(co==findindex[ind] && text[co]==findtext[0]){
            int cop=co;
            for(int s=0 ; s<len+1 ; s++){
                gloi=co-coo;
                int* pos = convert();
                init_pair(9 , 0 ,10);
                wattron(win,COLOR_PAIR(9));
                mvwprintw(win , pos[0]+1 ,6+pos[1] ,"%c" , text[co]);
                wattroff(win,COLOR_PAIR(9));
                co++;
            }
            ind++;co=cop;
        }
        j++;co++;
    }
    gloi=loj;
    int* po=convert();
    wmove(win , po[0]+1 , 6+po[1]);
    wrefresh(win);
    return;
}

void save(WINDOW* win){
    if(savebool==1){
        wclear(win);
        scrprint(varr , win , mode , filename , savebool);
        wrefresh(win);
        return;
    }
    if (strcmp(filename," ")==0){
        wclear(win);
        savebool=1;
        scrprint(varr , win , mode , filename , savebool);
        wrefresh(win);
        mvwprintw(win , LINE-2 , 2 , "Enter file name: ");wrefresh(win);
        char c = wgetch(win);char addr[200]={0};int o=0;
        while(c != '\n'){
            addr[o++]=c;wprintw(win , "%c",c);
            c=wgetch(win);
        }addr[o]='\0';
        strcpy(addr , appendAddress(DIRE , addr));
        FILE* fp = fopen(addr , "w");
        int i=0;
        while(text[i]!=0){
            fprintf(fp , "%c",text[i]);
            i++;
        }
        fclose(fp);
        wclear(win);
        scrprint(varr , win , mode , filename , savebool);wrefresh(win);
        return;
    }
    createUndo(location);
    savebool=1;
    FILE* fp = fopen(location , "w");
    int i=0;
    while(text[i]!=0){
        fprintf(fp , "%c",text[i]);
        i++;
    }
    fclose(fp);
    wclear(win);
    scrprint(varr , win , mode , filename , savebool);wrefresh(win);

}

void saveas(WINDOW* win){
    
        wrefresh(win);
        char c = wgetch(win);char addr[200]={0};int o=0;
        while(c != '\n'){
            addr[o++]=c;wprintw(win , "%c",c);
            c=wgetch(win);
        }addr[o]='\0';
        strcpy(addr , appendAddress(DIRE , addr));
        FILE* fp = fopen(addr , "w");
        int i=0;
        while(text[i]!=0){
            fprintf(fp , "%c",text[i]);
            i++;
        }
        fclose(fp);
        wclear(win);
        scrprint(varr , win , mode , filename , savebool);
        wrefresh(win);
        return;
    
}

void undo2(WINDOW* win){
    char add[100]={0};
    int cnt = 0;
    char c = 0;
    gloi=0;

    cnt=0;
    while (location[cnt] != '.'){
        add[cnt] = location[cnt];
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
    FILE* fi=fopen(location,"w");
    cnt=0;
    while((c=(char)getc(fp))!=EOF){
        fprintf(fi,"%c",c);
    }
    fclose(fp);
    fclose(fi);
    remove(add);

    text=readfile(location);
    over = overallarray(win , text);
    varr = visualarray(win , over);
    textn();
    wclear(win);savebool=1;
    scrprint(varr , win , mode , filename , savebool);
    wmove(win,1,6);wrefresh(win);
}

void open(WINDOW* win){
    char address[200]={0};
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    else{
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '\n'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);if(c!='\n')wprintw(win,"%c",c);
        }
        //printf("%s\n",address);
        strcpy(address , appendAddress(ADD , address));
    }int i=0;while(address[i]!=0)i++;
    address[i]='\0';
   // printf("%s\n",address);
    save(win);
    filename = flname(address);
    savebool=1;
    strcpy(location , address);
    text=readfile(address);
    over = overallarray(win , text);gloi=0;top=0;bot=32;
    varr = visualarray(win , over);
    textn();gloi=0;wmove(win,1,6);
    wclear(win);
    scrprint(varr , win , mode , filename , savebool);
    wrefresh(win);
}

void indent2(WINDOW* win){
    char textt[10000]={0};
    int cnt = 0;
    char c = 0;
    savebool=0;
    cnt=0;
    int br1=0;
    int br2=0;
    while (text[cnt] != 0){
        if (text[cnt] == '{'){
            br1++;
        }
        else if(text[cnt] == '}'){
            br2++;
        }
        if (br2 > br1){
            
            return;
        }
        cnt++;
    }
    if (br1 != br2){
        return;
    }

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
                if(textt[n-1] != '\n' && textt[n-1] != '\t'){
                    textt[n++]=' ';
                }
            }
            if (textt[n-1] == '\n'){
                for (int i=0 ; i<tab-1 ; i++){
                    textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';
                }
            }

            textt[n++]='{';
            textt[n++]=' ';
            cnt++;
            while(text[cnt]==' '){
                cnt++;
            }
            cnt--;
            textt[n++]='\n';
            n--;
        }
        else if(text[cnt] == '\n'){
            textt[n++]='\n';
            for (int i=0 ; i<tab ; i++){
                textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';
            }
            n--;
        }
        else if(text[cnt] == '}'){

            tab--;
            if(textt[n-1]!='\n'){
                textt[n++]='\n';
            }
            for (int i=0 ; i<tab ; i++){
                textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';
            }
            textt[n++] = '}';
            cnt++;
            while(text[cnt]==' '){
                cnt++;
            }
            cnt--;
            textt[n] = '\n';
        }
        else{
            if (textt[n-1] == '\n'){
                for (int i=0 ; i<tab ; i++){
                    textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';textt[n++]=' ';
                }
            }
            textt[n]=text[cnt];
        }
        n++;
        cnt++;
    }
    text=textt;
    over = overallarray(win , text);
    varr = visualarray(win , over);
    textn();
    gloi=0;
    wclear(win);
    scrprint(varr , win , mode , filename , savebool);
    wmove(win,1,6);
    wrefresh(win);
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
    char dirname[70];
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
                if (list[count] == '0'||list[count]=='\0') {
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

int insert(WINDOW* win) {

    char* str = (char*)calloc(30,sizeof(char));
    char* pos = (char*)calloc(30,sizeof(char));
    int lno;
    int strt;
    char address[200];
    char text[5000] = {0};
    char textNew[10000];
    int cnt = 0;
    char c = 0;
    int cond = 0;
    c=wgetch(win);wprintw(win , "%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win , "%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win , "%c",c);
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
            c=wgetch(win);wprintw(win , "%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    createUndo(address);

    str=stringfunction(win);
    if (strcmp(str , "--str") == 0){
        cnt = 0;
        c=wgetch(win);wprintw(win , "%c",c);

        if (c == '"'){
            cond = 1;
            char memo[8];
            int num=1;
            c=wgetch(win);wprintw(win , "%c",c);
            while (1){
                text[cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win , "%c",c);
                if (c == '"'){

                    for (int i = 0; i<6 ; i++){
                        memo[i]=wgetch(win);wprintw(win , "%c",memo[i]);
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
                    c=wgetch(win);wprintw(win , "%c",c);
                }
            }
        }
        else{
            cond = -1;
            while(c != ' '){
                text[cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win , "%c",c);
                //printf("%c",c);
            }
        }
        if (cond == -1){

            pos = stringfunction(win);
            if(strcmp(pos , "--pos") == 0){
                lno=numfunc(win);
                strt=numfunc(win);
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
                    wclear(win);
                    wmove(win , 1,6);
                    scrprint(varr , win , mode , filename , savebool);wrefresh(win);
                    return 1;
                
            }
        }

        else if (cond == 1){

            lno=numfunc(win);
                strt=numfunc(win);
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
                wclear(win);
                wmove(win , 1,6);
                scrprint(varr , win , mode , filename , savebool);wrefresh(win);
                return 1;
            
        }

    }

    printf("Invalid arguments\n");
    return -1;

}

int insertarman(WINDOW* win) {

    char* str=(char*)calloc(30,sizeof(char));
    char* pos=(char*)calloc(30,sizeof(char));
    int lno;
    int strt;
    char address[200];
    char text[5000] = {0};
    char textNew[10000];
    int cnt = 0;
    char c = 0;
    int cond = 0;
    c=wgetch(win);wprintw(win , "%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win , "%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win , "%c",c);
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
            c=wgetch(win);wprintw(win , "%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    createUndo(address);

    FILE* arm = fopen(ARM,"r+");

    pos=stringfunction(win);

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
            lno=numfunc(win);
            strt=numfunc(win);
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
                wclear(win);
                wmove(win , 1,6);
                scrprint(varr , win , mode , filename , savebool);wrefresh(win);
                return 1;
            
        }
    }
    printf("Invalid arguments\n");
    return -1;
}

void cat(WINDOW* win,char list[]) {
    FILE* fout=fopen(OUTP,"w");
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
            fprintf(fout,"%c",c);
            c = (char)fgetc(fp);
        }
        printf("\n");
        fclose(fp);
    }
    fclose(fout);
    save(win);
    wclear(win);gloi=0;
    strcpy(location,OUTP);
    filename=flname(location);
    text = readfile(OUTP);
    over = overallarray(win , text);
    varr = visualarray(win , over);
    textn();savebool=1;
    scrprint(varr , win , mode , filename , savebool);
    wmove(win , 1 ,6);
    wrefresh(win);
}

void catarman(WINDOW* win,char list[]) {
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

void remve(WINDOW* win) {

    char* size=(char*)calloc(30,sizeof(char));
    char* pos=(char*)calloc(30,sizeof(char));
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200];
    char text[10000];
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
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
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    createUndo(address);

    pos=stringfunction(win);
    if (strcmp(pos , "--pos") == 0){
        lno=numfunc(win);
        strt=numfunc(win);
        size=stringfunction(win);
        if (strcmp(size , "-size") == 0) {
            sizei=numfunc(win);
            fb=wgetch(win);wprintw(win,"%c",fb);fb=wgetch(win);wprintw(win,"%c",fb);wgetch(win);
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
    wclear(win);
    scrprint(varr , win , mode , filename , savebool);
    wmove(win , 1 ,6);
    wrefresh(win);
}

void copy(WINDOW* win) {

    char* size=(char*)calloc(30,sizeof(char));
    char* pos=(char*)calloc(30,sizeof(char));
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200]={0};
    char text[10000];
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    else{
        while(c != ' '){
            if (c == '/'){
                c = (char)92;
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }

    pos=stringfunction(win);
    if (strcmp(pos , "--pos") == 0){
        lno=numfunc(win);
        strt=numfunc(win);
        size=stringfunction(win);
        if (strcmp(size , "-size") == 0) {
            sizei=numfunc(win);
            fb=wgetch(win);wprintw(win,"%c",fb);fb=wgetch(win);wprintw(win,"%c",fb);
            
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
    c=wgetch(win);
    wclear(win);
    scrprint(varr , win , mode , filename , savebool);
    wmove(win , 1 ,6);
    wrefresh(win);
}

void cut(WINDOW* win){

    char* size=(char*)calloc(30,sizeof(char));
    char* pos=(char*)calloc(30,sizeof(char));
    int lno;
    int strt;
    int sizei;
    char fb;
    char address[200]={0};
    char textt[10000];
    char clip[10000];
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
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
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    createUndo(address);

    pos=stringfunction(win);
    if (strcmp(pos , "--pos") == 0){
        lno=numfunc(win);
        strt=numfunc(win);
        size=stringfunction(win);
        if (strcmp(size , "-size") == 0) {
            sizei=numfunc(win);
            fb=wgetch(win);wprintw(win,"%c",fb);fb=wgetch(win);wprintw(win,"%c",fb);
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
                        textt[count] = c;
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }
                    textt[count] = EOF;
                    fclose(fp);
                    remove(address);
                    FILE *fil;
                    fil = fopen(address, "w");
                    int i = 0;
                    while (textt[i] != EOF){
                        fprintf(fil,"%c",textt[i]);
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
                    c=wgetch(win);
                    wclear(win);
                    scrprint(varr , win , mode , filename , savebool);
                    wmove(win , 1 ,6);
                    wrefresh(win);
                }

            }
            else if(fb =='b'){
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
                        textt[count] = c;
                        if (start1 == strt && line1 == lno){
                            ii = count;
                        }
                        if (c == '\n'){
                            line1++;
                            start1 = -1;
                        }
                        count++;
                    }

                    textt[count] = EOF;
                    fclose(fp);
                    remove(address);
                    FILE *fil;
                    fil = fopen(address, "w");
                    int i = -1;
                    start1 = -1;
                    line1 = 1;
                    int clipcount = 0;
                    while (textt[++i] != EOF){

                        if (i == (ii-sizei)+1){

                            for (int j=0 ; j<sizei ; j++){
                                clip[j]=textt[i];
                                i++;
                            }
                            i+= -1;
                        }
                        else{
                            fprintf(fil,"%c",textt[i]);
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
                    c=wgetch(win);
                    wclear(win);
                    scrprint(varr , win , mode , filename , savebool);
                    wmove(win , 1 ,6);
                    wrefresh(win);
                    
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

void paste(WINDOW* win){

    char* pos=(char*)calloc(30,sizeof(char));
    int lno;
    int strt;
    char address[200]={0};
    char text[10000];
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
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
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }
    createUndo(address);

    pos=stringfunction(win);
    if (strcmp(pos , "--pos") == 0){
        lno=numfunc(win);
        strt=numfunc(win);

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
            
            wclear(win);
            scrprint(varr , win , mode , filename , savebool);
            wmove(win , 1 ,6);
            wrefresh(win);

        }
    }
    else{
        printf("Invalid arguments\n");
    }
}

int find(WINDOW* win){
    char address[200]={0};
    char text[10000];
    char str[1000];
    char* file=(char*)calloc(30,sizeof(char));
    int cnt = 0;
    char c = 0;
    int cond = 0;
    int mode = 0;
    char* all=(char*)calloc(30,sizeof(char));
    char* mod=(char*)calloc(30,sizeof(char));
    int index = 0;
    FILE* fout = fopen(OUTP,"w");
    FILE* arm = fopen(ARM,"r");

    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
    else fscanf(arm,"%c",&c);
    if (c == '"'){
        char c1;
        if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
        else fscanf(arm,"%c",&c);
        while(c!='"') {

            if (cnt == 0 && c=='*'){
                cond = 1;
                if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                else fscanf(arm,"%c",&c);
            }
            else if (c == '*'){
                if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
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
                    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                    else fscanf(arm,"%c",&c);
                }
            }
            else if (c == 92) {
                if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                else fscanf(arm,"%c",&c1);
                if (c1 == '*' || c1 == '"') {
                    text[cnt] = c1;
                    cnt++;
                    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                    else fscanf(arm,"%c",&c);
                } else {
                    text[cnt] = c;
                    cnt++;
                    text[cnt] = c1;
                    cnt++;
                    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                    else fscanf(arm,"%c",&c);
                }
            } else {
                text[cnt] = c;
                cnt++;
                if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
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
                c=wgetch(win);wprintw(win,"%c",c);
                if(c1 == '"'){
                    cond = 0;
                    c=c1;
                }
                else{
                    cond = 2;
                    index = cnt;
                    text[cnt]=c1;
                    cnt++;
                    c=wgetch(win);wprintw(win,"%c",c);
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
                    c=wgetch(win);wprintw(win,"%c",c);
                }
            } else {
                text[cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win,"%c",c);
            }
        }
    }

    if (arman==0){
        file=stringfunction(win);
        if (strcmp(file, "--file") != 0){
            return -2;
        }
    }
    fclose(arm);
    arman=0;

    cnt = 0;
    char c1;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }
        c=wgetch(win);wprintw(win,"%c",c);scanf("%c",&c);
        strcpy(address , appendAddress(ADD , address));
        if (c == '\n'){
            mode = 0;
        }
        else if (c == ' '){
            c=wgetch(win);wprintw(win,"%c",c);
            if(c=='-')
                mode = 1;
            else{
                char c3,c2;
                c3=wgetch(win);wprintw(win,"%c",c3);c2=wgetch(win);wprintw(win,"%c",c2);
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
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
        if (c == '\n'){
            mode = 0;
        }
        else if (c == ' '){
            c=wgetch(win);wprintw(win,"%c",c);
            if(c=='-')
                mode = 1;
            else{
                char c3,c2;
                c3=wgetch(win);wprintw(win,"%c",c3);c2=wgetch(win);wprintw(win,"%c",c2);
                if(c3=='D' && c=='=' && c2==' '){
                    arman=1;
                }
            }
        }
    }

    if (mode != 0) {

        int shom = 0;
        c=wgetch(win);wprintw(win,"%c",c);
        while (c != '\n' && c != ' ') {
            all[shom]=c;
            c=wgetch(win);wprintw(win,"%c",c);
            shom++;
        }
        all[shom] = '\0';

        if (strcmp(all, "all") == 0) {

            int ty=0;
            if (c == ' '){
                ty=1;
                c=wgetch(win);wprintw(win,"%c",c);
                if(c=='-'){
                    mod=stringfunction(win);
                    if (strcmp(mod , "byword")==0){
                        if(c != '\n'){
                            char c2,c3;
                            c=wgetch(win);wprintw(win,"%c",c);c2=wgetch(win);wprintw(win,"%c",c2);c3=wgetch(win);wprintw(win,"%c",c3);
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
                            int ttrue=0;
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
                                                ttrue++;
                                                if (ttrue==1){
                                                    if(arman==0)fprintf(fout,"%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)fprintf(fout,",%d",word);
                                                    else fprintf(ar,",%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                ttrue++;
                                                if (ttrue==1){
                                                    if(arman==0)fprintf(fout,"%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)fprintf(fout,",%d",word);
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
                                                                ttrue++;
                                                                if (ttrue==1){
                                                                    if(arman==0)fprintf(fout,"%d",word);
                                                                    else fprintf(ar,"%d",word);
                                                                    indic++;
                                                                }
                                                                else{
                                                                    if(arman==0)fprintf(fout,",%d",word);
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
                            if (ttrue == 0){
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
                c2=wgetch(win);wprintw(win,"%c",c2);c3=wgetch(win);wprintw(win,"%c",c3);
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
                    int ttrue=0;
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
                                        ttrue++;
                                        if (ttrue==1){
                                            if(arman==0)fprintf(fout,"%d",init+1);
                                            else fprintf(ar,"%d",init+1);
                                        }
                                        else{
                                            if(arman==0)fprintf(fout,",%d",init+1);
                                            else fprintf(ar,",%d",init+1);
                                        }
                                    }
                                    else if(cond == 1){
                                        u++;
                                        ttrue++;
                                        cnt1=init;
                                        while(hfile[cnt1-1] != ' ' && hfile[cnt1-1] != '\n' && cnt1>0){
                                            cnt1--;
                                        }
                                        if (ttrue==1){
                                            if(arman==0)fprintf(fout,"%d",cnt1+1);
                                            else fprintf(ar,"%d",cnt1+1);
                                        }
                                        else{
                                            if(arman==0)fprintf(fout,",%d",cnt1+1);
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
                                                        ttrue++;
                                                        if (ttrue==1){
                                                            if(arman==0)fprintf(fout,"%d",init+1);
                                                            else fprintf(ar,"%d",init+1);
                                                            indic++;
                                                        }
                                                        else{
                                                            if(arman==0)fprintf(fout,",%d",init+1);
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
                    if (ttrue == 0){
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
                c=wgetch(win);wprintw(win,"%c",c);
                if(c=='-'){
                    mod=stringfunction(win);
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
                            int ttrue=0;
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
                                                ttrue++;
                                                if (ttrue==1){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                                else{
                                                    if(arman==0)printf(",%d",word);
                                                    else fprintf(ar,",%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                ttrue++;
                                                if (ttrue==1){
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
                                                                ttrue++;
                                                                if (ttrue==1){
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
                            if (ttrue == 0){
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
                            int ttrue=0;
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
                                                ttrue++;
                                                if (num == ttrue){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                ttrue++;
                                                if (num == ttrue){
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
                                                                ttrue++;
                                                                if (num == ttrue){
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
                            if(num > ttrue){
                                printf("-at argument too big\n");
                                fclose(ar);
                                fclose(fp);
                                return -3;
                            }
                            if (ttrue == 0){
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
                    int ttrue=0;
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
                                        ttrue++;
                                        if(arman==0)printf("%d\n",word);
                                        else fprintf(ar,"%d\n",word);
                                        fprintf(ar,"%c%c",'"',EOF);
                                        fclose(ar);
                                        fclose(fp);
                                        return -3;


                                    }
                                    else if(cond == 1){
                                        ttrue++;
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
                                                        ttrue++;
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
                    if (ttrue == 0){
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
                int ttrue = 0;
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
                                    ttrue++;

                                } else if (cond == 1) {
                                    u++;
                                    ttrue++;

                                } else if (cond == 2) {
                                    int indic = 0;
                                    while (hfile[cnt1] != 0 && indic == 0) {
                                        if (hfile[cnt1] == text[index]) {
                                            counts = index;
                                            int init1 = cnt1;
                                            while (hfile[cnt1] == text[counts] && text[counts] != 0) {
                                                if (text[counts + 1] == 0) {
                                                    ttrue++;
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
                if(arman==0)printf("%d\n",ttrue);
                else fprintf(ar,"%d\n",ttrue);
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
                            int ttrue=0;
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
                                                ttrue++;
                                                if (num == ttrue){
                                                    if(arman==0)printf("%d",word);
                                                    else fprintf(ar,"%d",word);
                                                }
                                            }
                                            else if(cond == 1){
                                                ttrue++;
                                                if (num == ttrue){
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
                                                                ttrue++;
                                                                if (num == ttrue){
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
                            if(num > ttrue){
                                printf("-at argument too big\n");
                                fclose(fp);
                                return -3;
                            }
                            if (ttrue == 0){
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
                    int ttrue=0;
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
                                        ttrue++;
                                        if (num == ttrue){
                                            if(arman==0)printf("%d",init+1);
                                            else fprintf(ar,"%d",init+1);
                                        }
                                    }
                                    else if(cond == 1){
                                        ttrue++;
                                        cnt1=init;
                                        while(hfile[cnt1-1]!=' ' && hfile[cnt1-1]!='\n' && cnt1>0){
                                            cnt1--;
                                        }
                                        if (num == ttrue){
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
                                                        ttrue++;
                                                        if (num == ttrue){
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
                    if(num > ttrue){
                        printf("-at argument too big\n");
                        fclose(ar);
                        fclose(fp);
                        return -3;
                    }
                    if (ttrue == 0){
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
            int ttrue=0;
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
                                ttrue++;
                                if(arman==0)printf("%d\n",init+1);
                                else fprintf(ar,"%d\n",init+1);
                                fprintf(ar,"%c%c",'"',EOF);
                                fclose(fp);
                                fclose(ar);
                                return -3;

                            }
                            else if(cond == 1){
                                ttrue++;
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
                                                ttrue++;
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
            if (ttrue == 0){
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

void replace(WINDOW* win){
    char address[200]={0};
    char str1[1000] = {0};
    char str2[10000]={0};
    char* st=(char*)calloc(30,sizeof(char));
    char* file=(char*)calloc(30,sizeof(char));
    int cnt = 0;
    char c = 0;
    int cond = 0;
    int mode = 0;
    char* all=(char*)calloc(30,sizeof(char));
    char* mod=(char*)calloc(30,sizeof(char));


    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        char c1;
       c=wgetch(win);wprintw(win,"%c",c);
        while(c!='"') {

            if (cnt == 0 && c=='*'){
                cond = 1;
                c=wgetch(win);wprintw(win,"%c",c);
            }
            else if (c == '*'){
                cond = 2;
                c=wgetch(win);wprintw(win,"%c",c);
                continue;
            }

            if (c == 92) {
                c1=wgetch(win);wprintw(win,"%c",c1);
                if (c1 == '*' || c1 == '"') {
                    str1[cnt] = c1;
                    cnt++;
                    c=wgetch(win);wprintw(win,"%c",c);
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    c=wgetch(win);wprintw(win,"%c",c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win,"%c",c);
            }
        }
    }

    if (c != '"') {
        char c1;
        while (c != ' ') {
            if (cnt == 0 && c=='*'){
                cond = 1;
                c=wgetch(win);wprintw(win,"%c",c);
            }
            else if (c == '*'){
                cond = 2;
                c=wgetch(win);wprintw(win,"%c",c);
                continue;
            }
            if (c == 92) {
                c=wgetch(win);wprintw(win,"%c",c1);
                if (c1 == '*') {
                    str1[cnt] = c1;
                    cnt++;
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    c=wgetch(win);wprintw(win,"%c",c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win,"%c",c);
            }
        }
    }

    st=stringfunction(win);
    cnt=0;
    if (strcmp(st , "--str2")==0){
        c=wgetch(win);wprintw(win,"%c",c);
        if (c == '"'){
            char c1;
            c=wgetch(win);wprintw(win,"%c",c);
            while(c!='"') {
                if (c == 92) {
                    c=wgetch(win);wprintw(win,"%c",c1);
                    if (c1 == '"') {
                        str2[cnt] = c1;
                        cnt++;
                        c=wgetch(win);wprintw(win,"%c",c);
                    } else {
                        str2[cnt] = c;
                        cnt++;
                        str2[cnt] = c1;
                        cnt++;
                        c=wgetch(win);wprintw(win,"%c",c);
                    }
                } else {
                    str2[cnt] = c;
                    cnt++;
                    c=wgetch(win);wprintw(win,"%c",c);
                }
            }
        }

        if (c != '"') {
            char c1;
            while (c != ' ' && c != '\n') {
                str2[cnt] = c;
                cnt++;
                c=wgetch(win);if(c!='\n')wprintw(win,"%c",c);
            }

        }

        if(c!='\n')file=stringfunction(win);
        if (strcmp(file , "--file")==0){

            cnt = 0;
            c=wgetch(win);wprintw(win,"%c",c);
            if (c == '"'){
                c=wgetch(win);wprintw(win,"%c",c);
                while(c != '"'){
                    if (c == '/'){
                        c = '\\';
                    }
                    address[cnt] = c;
                    cnt++;
                    c=wgetch(win);wprintw(win,"%c",c);
                }
                c=wgetch(win);wprintw(win,"%c",c);
                strcpy(address , appendAddress(ADD , address));
            }
            else{
                while(c != ' ' && c != '\n'){
                    if (c == '/'){
                        c = '\\';
                    }
                    address[cnt] = c;
                    cnt++;
                    c=wgetch(win);if(c!='\n')wprintw(win,"%c",c);
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
                    int ttrue = 0;
                    int init = 0;
                    int u =0;
                    while (htext[count] != 0 && htext[count] != '\0' && ttrue == 0){
                        if (htext[count] == str1[0]){
                            init = count;
                            while (htext[count] == str1[counts]){
                                if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                    if (cond == 0){
                                        index = init;
                                        size = counts;
                                        ttrue = 1;
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
                                        ttrue = 1;
                                        break;
                                    }

                                    else if(cond == 2){
                                        u = count;
                                        while(htext[count] != ' ' && htext[count] != '\n' && htext[count] != 0){
                                            count++;
                                        }
                                        index = init;
                                        size = count -init-1;
                                        ttrue = 1;
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
                        wclear(win);
                        scrprint(varr , win , mode , filename , savebool);
                        wmove(win , 1 ,6);
                        wrefresh(win);
                        fclose(fil);

                    }

                }

                else if(c==' '){
                    all=stringfunction(win);
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
                        int ttrue = 0;
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
                                        ttrue++;
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
                        if (ttrue == 0){
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
                            wclear(win);
                            scrprint(varr , win , mode , filename , savebool);
                            wmove(win , 1 ,6);
                            wrefresh(win);
                            printf("Success\n");

                        }
                    }
                    else if(strcmp(all,"-at")==0){

                        int num;
                        num=numfunc(win);
                        int count=0;
                        char htext[10000];
                        while ((htext[count]=(char)fgetc(fp)) != EOF){
                            count++;
                        }
                        fclose(fp);

                        count = 0;
                        int counts = 0;
                        int size=0;
                        int ttrue = 0;
                        int index=0;
                        int init = 0;
                        int u =0;
                        int numnum=0;

                        while (htext[count] != 0 && htext[count] != '\0'){
                            if (htext[count] == str1[0]){
                                init = count;
                                while (htext[count] == str1[counts]){
                                    if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                        ttrue++;
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
                        if (ttrue == 0){
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
                            wclear(win);
                            scrprint(varr , win , mode , filename , savebool);
                            wmove(win , 1 ,6);
                             wrefresh(win);
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
            
            int cel;char* tent=(char*)calloc(10000,sizeof(char));int tenta=0;savebool=0;
            if (c == '\n'){
                    int count=0;
                   
                    
                    int counts = 0;
                    int size = 0;
                    int index = 0;
                    int ttrue = 0;
                    int init = 0;
                    int u =0;
                    while (text[count] != 0 && text[count] != '\0' && ttrue == 0){
                        if (text[count] == str1[0]){
                            init = count;
                            while (text[count] == str1[counts]){
                                if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                    if (cond == 0){
                                        index = init;
                                        size = counts;
                                        ttrue = 1;
                                        break;
                                    }
                                    else if(cond == 1){
                                        u = count;
                                        count = init;
                                        while(text[count] != ' ' && text[count] != '\n' && count >= 0){
                                            count--;
                                        }
                                        index = count+1;
                                        size = u-count-1;
                                        ttrue = 1;
                                        break;
                                    }

                                    else if(cond == 2){
                                        u = count;
                                        while(text[count] != ' ' && text[count] != '\n' && text[count] != 0){
                                            count++;
                                        }
                                        index = init;
                                        size = count -init-1;
                                        ttrue = 1;
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
                        
                        cnt = 0;
                        while(text[cnt] != 0 && text[cnt] != EOF ){
                            if (cnt == index){
                                for (int i=0 ; str2[i]!=0 ; i++){
                                    tent[tenta++] = str2[i];
                                    

                                }
                                cnt += size+1;
                            }
                            tent[tenta++] = text[cnt];
                            cnt++;
                        }
                        printf("Success\n");
                        wclear(win);
                        text=tent;
                        
                        int ln=0;int co=0;int j=0;int coo=0;

                        while(co!=index){
                            if(text[co]=='\n' || j==COL){
                                ln++;co++;j=0;coo=co;continue;
                            }

                            j++;co++;
                        }
                        top=ln;
                        gloi=co-coo;
                        


                        over = overallarray(win , text);
                        varr = visualarray(win , over);
                        textn();savebool=1;
                        scrprint(varr , win , mode , filename , savebool);
                        int* pos = convert();
                        wmove(win , 1+pos[0],6+pos[1]);
                        wrefresh(win);


                    }

                }

                else if(c==' '){
                    all=stringfunction(win);
                    if (strcmp(all,"-all")==0){
                        int count=0;
                        

                        count = 0;
                        int counts = 0;
                        int size[1000] = {0};
                        int ttrue = 0;
                        int index[1000] = {0};
                        int init = 0;
                        int u =0;
                        int indexc=0;
                        int sizec=0;

                        while (text[count] != 0 && text[count] != '\0'){
                            if (text[count] == str1[0]){
                                init = count;
                                while (text[count] == str1[counts]){
                                    if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                        ttrue++;
                                        if (cond == 0){
                                            index[indexc] = init;
                                            size[sizec] = counts;
                                            indexc++;sizec++;
                                        }
                                        else if(cond == 1){
                                            u = count;
                                            count = init;
                                            while(text[count] != ' ' && text[count] != '\n' && count >= 0){
                                                count--;
                                            }
                                            index[indexc] = count+1;
                                            size[sizec] = u-count-1;
                                            sizec++;indexc++;
                                        }

                                        else if(cond == 2){
                                            u = count;
                                            while(text[count] != ' ' && text[count] != '\n' && 
                                            text[count] != 0  && text[count] != EOF){
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
                        if (ttrue == 0){
                            printf("string not found\n");
                        }
                        else{
                            
                            cnt = 0;
                            int cnti=0;
                            while(text[cnt] != 0 && text[cnt] != EOF ){
                                if (cnt == index[cnti]){
                                    for (int i=0 ; str2[i]!=0 ; i++){
                                        tent[tenta++]=str2[i];

                                    }
                                    cnt += size[cnti]+1;
                                    cnti++;
                                }
                                if (text[cnt] != 0 && text[cnt] != EOF){
                                    tent[tenta++]=text[cnt];
                                    cnt++;
                                }
                            }
                            
                            wclear(win);
                            text=tent;
                            printf("Success\n");


                            int ln=0;int co=0;int j=0;int coo=0;

                            while(co!=index[0]){
                                if(text[co]=='\n' || j==COL){
                                    ln++;co++;j=0;coo=co;continue;
                                }

                                j++;co++;
                            }
                            top=ln;
                            gloi=co-coo;



                            over = overallarray(win , text);
                            varr = visualarray(win , over);
                            textn();savebool=1;
                            scrprint(varr , win , mode , filename , savebool);
                           int* pos = convert();
                            wmove(win , 1+pos[0],6+pos[1]);
                            wrefresh(win);


                        }
                    }
                    else if(strcmp(all,"-at")==0){

                        int num;
                        num=numfunc(win);
                        int count=0;
                        

                        count = 0;
                        int counts = 0;
                        int size=0;
                        int ttrue = 0;
                        int index=0;
                        int init = 0;
                        int u =0;
                        int numnum=0;

                        while (text[count] != 0 && text[count] != '\0'){
                            if (text[count] == str1[0]){
                                init = count;
                                while (text[count] == str1[counts]){
                                    if (str1[counts+1] == 0 || str1[counts+1] == '\0'){
                                        ttrue++;
                                        numnum++;
                                        if (cond == 0 && numnum==num){
                                            index = init;
                                            size = counts;
                                        }
                                        else if(cond == 1 && numnum==num){
                                            u = count;
                                            count = init;
                                            while(text[count] != ' ' && text[count] != '\n' && count >= 0){
                                                count--;
                                            }
                                            index = count+1;
                                            size = u-count-1;

                                        }

                                        else if(cond == 2 && numnum==num){
                                            u = count;
                                            while(text[count] != ' ' && text[count] != '\n' && text[count] != 0  && text[count] != EOF){
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
                        if (ttrue == 0){
                            printf("string not found\n");
                        }
                        else if(numnum<num){
                            printf("-1\n");
                        }
                        else{
                            cnt = 0;
                            int cnti=0;
                            while(text[cnt] != 0 && text[cnt] != EOF ){
                                if (cnt == index){
                                    for (int i=0 ; str2[i]!=0 ; i++){
                                        tent[tenta++]=str2[i];

                                    }
                                    cnt += size+1;
                                    cnti++;
                                }
                                if (text[cnt] != 0 && text[cnt] != EOF){
                                    tent[tenta++]=text[cnt];
                                    cnt++;
                                }
                            }
                            
                            wclear(win);
                            
                            printf("Success\n");
                            int ln=0;int co=0;int j=0;int coo=0;

                            while(co!=index){
                                if(text[co]=='\n' || j==COL){
                                    ln++;co++;j=0;coo=co;continue;
                                }

                                j++;co++;
                            }
                            top=ln;
                            gloi=co-coo;
                        


                            over = overallarray(win , text);
                             varr = visualarray(win , over);
                            textn();savebool=1;
                            scrprint(varr , win , mode , filename , savebool);
                            int* pos = convert();
                            wmove(win , 1+pos[0],6+pos[1]);
                            wrefresh(win);


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

int grepFunc(WINDOW* win,char address[] , char str[] , int mode,FILE* armm){
    char row[1000]={0};
    int index;
    int res=0;
    char textt[100][100];
    char c;
    for (int ii=0 ; ii<100 ; ii++){
        for (int jj=0 ; jj<100 ; jj++){
            textt[ii][jj]=0;
        }
    }

    FILE *fp = fopen(address,"r+");
    FILE *fout = fopen(OUTP,"w");
    if (fp == NULL){
        printf("File not found\n");
        fclose(armm);
        return -1;
    }
    int i=0;
    int j=0;
    while((textt[i][j]=(char)getc(fp)) != EOF){
        j++;
        if (textt[i][j-1] == '\n'){
            i++;
            j=0;
        }
    }
    if (textt[i][j] == EOF){
        textt[i][j] = '\n';
    }
    fclose(fp);
    if (mode == 0){
        int count = 0;
        j=0;
        int init;
        int counts=0;
        while (textt[count][0] != 0){
            if(textt[count][j]==0){
                count++;
                j=0;
            }

            if (textt[count][j] == str[0]){
                init = j;
                while (textt[count][j] == str[counts] && textt[count][j]!='\n' && str[counts]!=0){
                    if (str[counts+1] == 0 || str[counts+1] == '\0'){
                        j=0;
                        if(arman==0)fprintf(fout,"%s: ",address);
                        else fprintf(armm,"%s: ",address);
                        while(textt[count][j]!=0){
                            if(arman==0)fprintf(fout,"%c",textt[count][j]);
                            else fprintf(armm,"%c",textt[count][j]);
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
        fclose(fout);
        save(win);
        wclear(win);gloi=0;
        strcpy(location,OUTP);
        filename=flname(location);
        text = readfile(OUTP);
        over = overallarray(win , text);
        varr = visualarray(win , over);
        textn();savebool=1;
        scrprint(varr , win , mode , filename , savebool);
        wmove(win , 1 ,6);
        wrefresh(win);
    }
    else if(mode == 1){
        int count = 0;
        j=0;
        int init;
        int result=0;
        int counts=0;
        while (textt[count][0] != 0){
            if(textt[count][j]==0){
                count++;
                j=0;
            }

            if (textt[count][j] == str[0]){
                init = j;
                while (textt[count][j] == str[counts] && textt[count][j]!='\n' && str[counts]!=0){
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
        }fclose(fout);

        return result;
    }
    else if(mode == 2){
        int count = 0;
        j=0;
        int init;
        int counts=0;
        while (textt[count][0] != 0){
            if(textt[count][j]==0){
                count++;
                j=0;
            }

            if (textt[count][j] == str[0]){
                init = j;
                while (textt[count][j] == str[counts] && textt[count][j]!='\n' && str[counts]!=0){
                    if (str[counts+1] == 0 || str[counts+1] == '\0'){
                        j=0;
                        if(arman==0)fprintf(fout,"%s\n",address);
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
        save(win);
        wclear(win);gloi=0;
        strcpy(location,OUTP);
        filename=flname(location);
        text = readfile(OUTP);
        over = overallarray(win , text);
        varr = visualarray(win , over);
        textn();savebool=1;
        scrprint(varr , win , mode , filename , savebool);
        wmove(win , 1 ,6);
        wrefresh(win);
    }

}

void grep(WINDOW* win){
    char address[100][100];
    for(int i=0 ; i<100; i++){
        for (int j=0 ; j<100 ; j++){
            address[i][j]=0;
        }
    }
    char str1[1000]={0};
    char* st=(char*)calloc(30,sizeof(char));
    char* op=(char*)calloc(30,sizeof(char));
    char* file=(char*)calloc(30,sizeof(char));
    int cnt = 0;
    char c = 0;
    int mode = 0;

    op=stringfunction(win);
    if(arman==0){
        if (strcmp(op,"--str")!=0){
            mode = 1;
            st=stringfunction(win);
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
            file=stringfunction(win);
            if(strcmp(file , "--files")!=0){
                printf("invalid command\n");
                return;
            }
        }
    }

    FILE* arm = fopen(ARM , "r");
    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
    else fscanf(arm,"%c",&c);
    if (c == '"'){
        char c1;
        if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
        else fscanf(arm,"%c",&c);
        while(c!='"') {
            if (c == 92) {
                if(arman==0){c1=wgetch(win);wprintw(win,"%c",c1);}
                else fscanf(arm,"%c",&c1);
                if (c1 == '"') {
                    str1[cnt] = c1;
                    cnt++;
                    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                    else fscanf(arm,"%c",&c);
                } else {
                    str1[cnt] = c;
                    cnt++;
                    str1[cnt] = c1;
                    cnt++;
                    if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                    else fscanf(arm,"%c",&c);
                }
            } else {
                str1[cnt] = c;
                cnt++;
                if(arman==0){c=wgetch(win);wprintw(win,"%c",c);}
                else fscanf(arm,"%c",&c);
            }
        }
    }

    if (c != '"') {
        while (c != ' ') {
            str1[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }
    }
    if(arman==0) {
        file=stringfunction(win);
        if (strcmp(file, "--files") != 0) {
            printf("Invalid args\n");
            return;
        }
    }
    fclose(arm);
    c=1;

    int res=0;
    int i=0;
    c=wgetch(win);wprintw(win,"%c",c);
    while(c!='\n'){
        cnt=0;
        if (c == '"'){
            c=wgetch(win);wprintw(win,"%c",c);
            while(c != '"'){
                if (c == '/'){
                    c = '\\';
                }
                address[i][cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win,"%c",c);
            }
            c=wgetch(win);wprintw(win,"%c",c);
            strcpy(address[i] , appendAddress(ADD , address[i]));
        }
        else{
            while(c != ' ' && c != '\n'){
                if (c == '/'){
                    c = '\\';
                }
                address[i][cnt] = c;
                cnt++;
                c=wgetch(win);wprintw(win,"%c",c);
            }
            strcpy(address[i] , appendAddress(ADD , address[i]));
        }
        //printf(">%s<",address[i]);

        if(c==' ' && arman==0){
            char c1,c2,c3;
            c=wgetch(win);wprintw(win,"%c",c);
            if(c != '/' && c != '"'){
                c2=wgetch(win);wprintw(win,"%c",c2);c3=wgetch(win);wprintw(win,"%c",c3);
                if(c=='=' && c2=='D' && c3==' '){
                    arman=1;
                }
            }
        }
        else{
            if(c==' ')c=wgetch(win);wprintw(win,"%c",c);
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
        res += grepFunc(win,address[i],str1,mode,arr);
        i++;
    }
    fprintf(arr,"%c%c",'"',EOF);
    fclose(arr);

    if (mode==1){
        FILE* fout=fopen(OUTP,"W");
        FILE* ar = fopen(ARM,"w");
        fprintf(ar,"%c",'"');
        if(arman==0)fprintf(fout,"%d\n",res);
        else {fprintf(ar,"%d\n",res);
        fprintf(ar,"%c%c",'"',EOF);
        fclose(ar);}fclose(fout);
        save(win);
        wclear(win);gloi=0;
        strcpy(location,OUTP);
        filename=flname(location);
        text = readfile(OUTP);
        over = overallarray(win , text);
        varr = visualarray(win , over);
        textn();savebool=1;
        scrprint(varr , win , mode , filename , savebool);
        wmove(win , 1 ,6);
         wrefresh(win);
    }
}

void undo(WINDOW* win){
    char address[200]={0};
    char add[100]={0};
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }wgetch(win);
        strcpy(address , appendAddress(ADD , address));
    }
    else{
        while(c != '\n'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);if(c!='\n')wprintw(win,"%c",c);
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

    wclear(win);
    wmove(win , 1,6);
    scrprint(varr , win , mode , filename , savebool);wrefresh(win);

}

void indent(WINDOW* win){
    char address[200]={0};
    char text[10000] = {0};
    char textn[10000]={0};
    int cnt = 0;
    char c = 0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
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
            c=wgetch(win);wprintw(win,"%c",c);
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
    wclear(win);
    wmove(win , 1,6);
    scrprint(varr , win , mode , filename , savebool);wrefresh(win);

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

void compare(WINDOW* win){
    char address[100]={0};
    char address2[100]={0};
    char textt[10000]={0};
    char text2[10000]={0};
    int cnt = 0;
    char c = 0;
    FILE* fout=fopen(OUTP,"w");
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
        c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
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
            c=wgetch(win);wprintw(win,"%c",c);
        }
        strcpy(address , appendAddress(ADD , address));
    }

    cnt=0;
    c=wgetch(win);wprintw(win,"%c",c);
    if (c == '"'){
       c=wgetch(win);wprintw(win,"%c",c);
        while(c != '"'){
            if (c == '/'){
                c = '\\';
            }
            address2[cnt] = c;
            cnt++;
            c=wgetch(win);wprintw(win,"%c",c);
        }
        c=wgetch(win);wprintw(win,"%c",c);
        strcpy(address2 , appendAddress(ADD , address2));
    }
    else{
        while(c != '\n' && c !=' '){
            if (c == '/'){
                c = '\\';
            }
            address2[cnt] = c;
            cnt++;
            c=wgetch(win);if(c!='\n')wprintw(win,"%c",c);
        }
        strcpy(address2 , appendAddress(ADD , address2));
    }

    FILE* arm=fopen(ARM,"w");
    if (c==' '){
        char c1,c2,c3;
        c1=wgetch(win);wprintw(win,"%c",c1);c2=wgetch(win);wprintw(win,"%c",c2);c3=wgetch(win);wprintw(win,"%c",c3);
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
        textt[cnt++]=c;
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
    while (textt[i]!=0 || text2[j] !=0){
        if (textt[i] == 0){
            if(arman==0)fprintf(fout,">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n" , ii , line2);
            else fprintf(arm,">>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n" , ii , line2);
            while (text2[j] !=0 && text2[j] !=EOF){
                if(arman==0)fprintf(fout,"%c",text2[j++]);
                else fprintf(arm,"%c",text2[j++]);
            }
            if(arman==0)fprintf(fout,"\n");
            else {
                fprintf(arm,"\n");
                fprintf(arm,"%c%c",'"',EOF);
                fclose(arm);
            }
            fclose(fout);
            save(win);
            wclear(win);gloi=0;
            strcpy(location,OUTP);
            filename=flname(location);
            text = readfile(OUTP);
            over = overallarray(win , text);
            varr = visualarray(win , over);
            textn();savebool=1;
            scrprint(varr , win , mode , filename , savebool);
            wmove(win , 1 ,6);
            wrefresh(win);
            return;
        }
        else if(text2[j]==0){
            if(arman==0)fprintf(fout,"<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n" , ii , line1);
            else fprintf(arm,"<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n" , ii , line1);
            while (textt[i] !=0 && textt[i] !=EOF){
                if(arman==0)fprintf(fout,"%c",textt[i++]);
                else fprintf(arm,"%c",textt[i++]);
            }
            if(arman==0)fprintf(fout,"\n");
            else {
                fprintf(arm,"\n");
                fprintf(arm,"%c%c",'"',EOF);
                fclose(arm);
            }
            fclose(fout);
            save(win);
            wclear(win);gloi=0;
            strcpy(location,OUTP);
            filename=flname(location);
            text = readfile(OUTP);
            over = overallarray(win , text);
            varr = visualarray(win , over);
            textn();savebool=1;
            scrprint(varr , win , mode , filename , savebool);
            wmove(win , 1 ,6);
            wrefresh(win);
            return;
        }
        else if (textt[i] != text2[j]){
            if(arman==0)fprintf(fout,"============ #%d ============\n",ii);
            else fprintf(arm,"============ #%d ============\n",ii);
            ii++;jj++;
            while(textt[i]!='\n' && textt[i]!=0 && textt[i]!=EOF){
                l1[li++]=textt[i];
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
                    if(arman==0)fprintf(fout,"%c",l1[li]);
                    else fprintf(arm,"%c",l1[li]);
                    l1[li++]=0;
                }
                if (arman==0)fprintf(fout,"\n");
                else fprintf(arm,"\n");
                li=0;
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    if(arman==0)fprintf(fout,"%c",l2[lj]);
                    else fprintf(arm,"%c",l2[lj]);
                    l2[lj++]=0;
                }
                if(arman==0)fprintf(fout,"\n");
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
                        if(arman==0)fprintf(fout,">>");
                        else fprintf(arm,">>");
                        while (l1[li] != ' ' && l1[li] != 0){
                            if(arman==0)fprintf(fout,"%c",l1[li]);
                            else fprintf(arm,"%c",l1[li]);
                            l1[li++]=0;
                        }
                        if(arman==0)fprintf(fout,"<<");
                        else fprintf(arm,"<<");
                        continue;
                    }
                    else if(word == res){
                        if(arman==0)fprintf(fout,">>");
                        else fprintf(arm,">>");
                        while (l1[li] != ' ' && l1[li] != 0){
                            if(arman==0)fprintf(fout,"%c",l1[li]);
                            else fprintf(arm,"%c",l1[li]);
                            l1[li++]=0;
                        }
                        if(arman==0)fprintf(fout,"<<");
                        else fprintf(arm,"<<");
                        continue;
                    }

                    if(arman==0)fprintf(fout,"%c",l1[li]);
                    else fprintf(arm,"%c",l1[li]);
                    l1[li++]=0;
                }
                if(arman==0)fprintf(fout,"\n");
                else fprintf(arm,"\n");
                li=0;

                word=1;
                while(l2[lj] !=0 && l2[lj] !=EOF){
                    if (l2[lj] == ' '){
                        word++;
                    }
                    else if (lj == 0 && res == 1){
                        if(arman==0)fprintf(fout,">>");
                        else fprintf(arm,">>");
                        while (l2[lj] != ' ' && l2[lj] != 0){
                            if(arman==0)fprintf(fout,"%c",l2[lj]);
                            else fprintf(arm,"%c",l2[lj]);
                            l2[lj++]=0;
                        }
                        if(arman==0)fprintf(fout,"<<");
                        else fprintf(arm,"<<");
                        continue;
                    }
                    else if(word == res){
                        if(arman==0)fprintf(fout,">>");
                        else fprintf(arm,">>");
                        while (l2[lj] != ' ' && l2[lj] != 0){
                            if(arman==0)fprintf(fout,"%c",l2[lj]);
                            else fprintf(arm,"%c",l2[lj]);
                            l2[lj++]=0;
                        }
                        if(arman==0)fprintf(fout,"<<");
                        else fprintf(arm,"<<");
                        continue;
                    }

                    if(arman==0)fprintf(fout,"%c",l2[lj]);
                    else fprintf(arm,"%c",l2[lj]);
                    l2[lj++]=0;
                }

                if(arman==0)fprintf(fout,"\n");
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

            l1[li++]=textt[i];
            l2[lj++]=text2[j];
            i++;
            j++;
        }

    }
    if(arman==0)fprintf(fout,"\n");
    else fprintf(arm,"\n");

    fprintf(arm,"%c%c",'"',EOF);
    fclose(arm);fclose(fout);
    save(win);
    wclear(win);gloi=0;
    strcpy(location,OUTP);
    filename=flname(location);
    text = readfile(OUTP);
    over = overallarray(win , text);
    varr = visualarray(win , over);
    textn();savebool=1;
    scrprint(varr , win , mode , filename , savebool);
    wmove(win , 1 ,6);
    wrefresh(win);

}

void tree(FILE* fout,char *basePath, const int root,FILE* arm)
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
                        fprintf(fout,"%c", 179);
                    }
                    else{
                        fprintf(arm,"%c", 179);
                    }

                }
                else {
                    if(arman==0)fprintf(fout," ");
                    else fprintf(arm," ");
                }

            }

            if(arman==0) {
                fprintf(fout,"%c%c", 195, 196);
                fprintf(fout,"%s\n", dp->d_name);
            }
            else{
                fprintf(arm,"%c%c", 195, 196);
                fprintf(arm,"%s\n", dp->d_name);
            }

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            tree(fout,path, root + 2,arm);
        }
    }
    closedir(dir);
}

void treefun(WINDOW* win){
    char c;
    c=wgetch(win);wprintw(win , "%c",c);
    if(c=='-'){
        c=wgetch(win);wprintw(win , "%c",c);
        depth=(int)(c-48);
        depth*=(-1);
    }
    else{
        depth=(int)(c-48);
    }
    c=wgetch(win);if(c!='\n')wprintw(win , "%c",c);
    FILE* fout=fopen(OUTP,"w");

    if (depth < -1){
        if (c=='\n'){
            printf("invalid depth\n");
            return;
        }
        else if(c== ' '){
            char c1,c2;
            c1=wgetch(win);wprintw(win , "%c",c1);c2=wgetch(win);wprintw(win , "%c",c2);
            if (c1=='='&& c2=='D'){
                c=wgetch(win);wprintw(win , "%c",c);
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
        c1=wgetch(win);wprintw(win , "%c",c1);c2=wgetch(win);wprintw(win , "%c",c2);c3=wgetch(win);wprintw(win , "%c",c3);
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
    tree(fout,DIRE , 0,arm);
    fprintf(arm,"%c%c",'"',EOF);
    fclose(arm);fclose(fout);

    save(win);
    wclear(win);gloi=0;
    strcpy(location,OUTP);
    filename=flname(location);
    text = readfile(OUTP);
    over = overallarray(win , text);
    varr = visualarray(win , over);
    textn();savebool=1;
    scrprint(varr , win , mode , filename , savebool);
    wmove(win , 1 ,6);
    wrefresh(win);

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
    if(strcmp(list , "open")==0){
        return 15;
    }
    if(strcmp(list , "save")==0){
        return 16;
    }
    if(strcmp(list , "saveas")==0){
        return 17;
    }

    return 0;
}

void moden(WINDOW* win){
    char c;scrprint(varr , win , mode , filename , savebool);wrefresh(win);
    while(1){
        c=wgetch(win);

        if(c=='h' || c=='j' || c=='k' || c=='l'){
            navigate(win , c );
        }

        else{
            if(c == 'v'){
                mode = 1;return;
            }
            else if(c=='i'){
                mode=2;return;
            }
            else if(c=='/'){
                findtext = (char*)calloc(100,sizeof(char));
                findindex = (int*)calloc(1000,sizeof(int));
                find2(win);
                c=wgetch(win);
                int ci=0;
                while(c=='n'){
                    findnext(win , ci);
                    c=wgetch(win);
                    ci++;
                }
                wclear(win);
                int*po=convert();
                wmove(win , 1+po[0] , 6+po[1]);
                return;
            }
            else if(c=='p'){
                char* temp = (char*)calloc(10000 , sizeof(char));int co=0;int ln=0;int j=0;
                while(ln<top){
                    temp[co]=text[co];
                    if(text[co]=='\n' || j==COL){
                        ln++;co++;j=0;continue;
                    }
                    j++;co++;
                }int coo=co;
                while(co-coo<gloi){
                    temp[co]=text[co];
                    co++;
                }int cl=0;
                while(clipb[cl]!=0){
                    temp[co]=clipb[cl];
                    cl++;co++;
                }
                while(text[co-cl]!=0){
                    temp[co]=text[co-cl];
                    co++;
                }
                text=temp;
                over = overallarray(win , text);
                varr = visualarray(win , over);
                textn();
                wclear(win);
                scrprint(varr , win , mode , filename , savebool);
                int* pos = convert();
                wmove(win , pos[0]+1 , pos[1]+6);
                wrefresh(win);
            }

            else if(c=='u'){
                undo2(win);
            }
            
            else if(c=='='){
                indent2(win);
            }

            else if(c==':'){
                int com;
                
                    char input1[1000] = {0};
                    char input2[100] = {0};
                    int counter = 0;
                    int ident = 0;
                    char g = 0;
                    g=wgetch(win);
                    if (g != '\n') {
                        input1[counter] = g;
                        counter++;
                        mvwprintw(win ,LINE-2 ,2, "%c",g);wrefresh(win);
                    }

                    while (1) {
                        g=wgetch(win);
                        if (g == ' ') {
                            ident = 1;
                            wprintw(win , "%c",g);wrefresh(win);
                            break;
                        }
                        if (g == '\n') {
                            ident = -1;
                            break;
                        }
                        wprintw(win , "%c",g);wrefresh(win);
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
                                wscanw(win,"%c", &c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 2) {
                        char dum;
                        char file[30]={0};char c;int counter=0;
                        while (1) {
                            c=wgetch(win);
                            if (c == ' ') {
                                wprintw(win , "%c",c);wrefresh(win);
                                break;
                            }
                            if (c == '\n') {
                                
                                break;
                            }
                            wprintw(win , "%c",c);wrefresh(win);
                            file[counter] = c;
                            counter++;
                        }file[counter]='\0';
                        if (strcmp(file, "--file") == 0) {
                            if (arman==0){
                                int rr = insert(win);
                            }
                            else if(arman==1){
                                arman=0;
                                int rr=insertarman(win);
                            }

                        } else {
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 1 && arman==0) {
                        char dum;
                        char file[30];
                        char address[200]={0};int i=0;char c=wgetch(win);wprintw(win,"%c",c);
                        while(c!=' '){
                            file[i]=c;
                            i++;
                            c=wgetch(win);wprintw(win,"%c",c);
                        }

                        
                        //printf("%s",address);
                        if (strcmp(file, "--file") == 0) { i=0; c=wgetch(win);wprintw(win,"%c",c);
                            while(c!='\n'){
                                address[i]=c;
                                i++;
                                c=wgetch(win);if(c!='\n')wprintw(win,"%c",c);
                            }address[i]='\0';
                            createFile(address);
                            wclear(win);scrprint(varr , win , mode , filename , savebool);wmove(win,1,6);wrefresh(win);
                        } 
                        else {
                            char c = 0;
                            while (c != '\n') {
                                wscanw(win,"%c", &c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 3 && arman==0){
                        char dum;
                        char* file=(char*)calloc(30,sizeof(char));
                        char address[200]={0};
                        file=stringfunction(win);
                        if (strcmp(file, "--file") == 0) {
                            char c;int cnt=0;
                            c=wgetch(win);wprintw(win,"%c",c);
                            if (c == '"'){
                                c=wgetch(win);wprintw(win,"%c",c);
                                while(c != '"'){
                                    if (c == '/'){
                                        c = '\\';
                                    }
                                    address[cnt] = c;
                                    cnt++;
                                    c=wgetch(win);wprintw(win,"%c",c);
                                }
                                c=wgetch(win);wprintw(win,"%c",c);
                                strcpy(address , appendAddress(ADD , address));
                            }
                            else{
                                while(c != ' ' && c != '\n'){
                                    if (c == '/'){
                                        c = '\\';
                                    }
                                    address[cnt] = c;
                                    cnt++;
                                    c=wgetch(win);wprintw(win,"%c",c);
                                }
                                strcpy(address , appendAddress(ADD , address));
                            }
                            if (c=='\n'){
                                //printf("%s",address);
                                cat(win,address);
                            }
                            else if (c == ' '){
                                char* arm=(char*)calloc(4,sizeof(char));
                                arm=stringfunction(win);
                                if(strcmp(arm,"=D")==0){
                                    arman=1;
                                    catarman(win,address);
                                }
                                else{
                                    printf("invalid arguments\n");
                                }
                            }

                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 4 && arman==0) {
                        char dum;
                        char* file=(char*)calloc(30,sizeof(char));
                        file=stringfunction(win);
                        if (strcmp(file, "--file") == 0) {
                            remve(win);

                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 5 && arman==0) {
                        char dum;
                        char* file=(char*)calloc(30,sizeof(char));
                        file=stringfunction(win);
                        if (strcmp(file, "--file") == 0) {
                            copy(win);

                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 6 && arman==0){
                        char dum;
                        char* file=(char*)calloc(30,sizeof(char));
                        file=stringfunction(win);
                        if (strcmp(file, "--file") == 0) {
                            cut(win);

                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 7 && arman==0){
                        char dum;
                        char* file=(char*)calloc(30,sizeof(char));
                        file = stringfunction(win);
                        if (strcmp(file, "--file") == 0) {
                            paste(win);

                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 8){
                        char dum;
                        char* str=(char*)calloc(30,sizeof(char));
                        str=stringfunction(win);
                        if(arman==0){
                            if (strcmp(str, "--str") == 0) {
                                int u = find(win);
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
                                int u = find(win);
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
                        char* str=(char*)calloc(30,sizeof(char));
                        str=stringfunction(win);
                        if (strcmp(str, "--str1") == 0) {
                            //printf("aa");
                            replace(win);
                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }

                    else if (com == 10){
                        grep(win);

                    }

                    else if (com == 11 && arman==0){
                        char dum;
                        char* file=(char*)calloc(30,sizeof(char));
                        file=stringfunction(win);
                        if (strcmp(file, "--file") == 0) {
                            undo(win);

                        } else {
                            char c = 0;
                            while (c != '\n') {
                                c=wgetch(win);wprintw(win,"%c",c);
                            }
                            printf("Invalid command\n");
                        }
                    }


                    else if (com == 12 && arman==0){
                        indent(win);
                    }

                    else if (com == 13 && arman==0){
                        compare(win);
                    }

                    else if (com == 14 && arman==0){
                        treefun(win);
                    }
                    
                    else if(com==15){
                        open(win);
                        noecho();

                    }

                    else if(com==16){
                        save(win);
                        noecho();

                    }

                    else if(com==17){
                        saveas(win);
                    }

                    else{
                        printf("invalid command\n");
                    }
                
            }

            else if(c== 'q'){
                quit=1;return;
            }
        }
    }
}


int main() {

    FILE* ff= fopen(OUTP,"w");
    fprintf(ff," ");
    fclose(ff);

    initscr();
    noecho();
    WINDOW* win = newwin(36,140+10,0,0);
    refresh();

    wmove(win , 1 , 6);
    wrefresh(win);


    strcpy(location , OUTP);
    text = readfile(OUTP);
    over = overallarray(win , text);
    varr = visualarray(win , over);
    textn();


    savebool=1;
    filename = flname(OUTP);
    mode=0;


    scrprint(varr , win , mode , filename , savebool);
    wmove(win , 1 ,6);
    wrefresh(win);

    moden(win);
    char c=0;
    while(quit==0){
        if (mode==0){
            moden(win);
        }
        if (mode==1){
            modev(win);
        }
        if (mode==2){
            modei(win);
        }

    }



    endwin();

    return 0;
}