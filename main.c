#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int command(char list[]){
    char c;
    //register 1 8
    //withdraw 2 8
    //balance 3 7
    //transfer 4  8
    //info 5 4
    //invalid 0 7
    //exit -1 4
    //batchreg 6 8
    //recent actions 7 6
    //deposit 8 7
    int count=0;
    c = list[count];
    while (c != 0){
        count++;
        c = list[count];
    }


    if (count > 8){
        return 0;
    }

    else if (count==8){
        if (list[0] == 'r' && list[1] == 'e' && list[2] == 'g' && list[3] == 'i' && list[4] == 's' && list[5] == 't' && list[6] == 'e' && list[7] == 'r'){
            return 1;
        }
        if(list[0] == 'w' && list[1] == 'i' && list[2] == 't' && list[3] == 'h' && list[4] == 'd' && list[5] == 'r' && list[6] == 'a' && list[7] == 'w'){
            return 2;
        }
        if(list[0] == 't' && list[1] == 'r' && list[2] == 'a' && list[3] == 'n' && list[4] == 's' && list[5] == 'f' && list[6] == 'e' && list[7] == 'r'){
            return 4;
        }
        if(list[0] == 'b' && list[1] == 'a' && list[2] == 't' && list[3] == 'c' && list[4] == 'h' && list[5] == 'r' && list[6] == 'e' && list[7] == 'g'){
            return 6;
        }
        return 0;

    }

    else if (count == 7){
        if (list[0] == 'b' && list[1] == 'a' && list[2] == 'l' && list[3] == 'a' && list[4] == 'n' && list[5] == 'c' && list[6] == 'e'){
            return 3;
        }
        if (list[0] == 'd' && list[1] == 'e' && list[2] == 'p' && list[3] == 'o' && list[4] == 's' && list[5] == 'i' && list[6] == 't'){
            return 8;
        }
        return 0;
    }

    else if (count == 4){
        if (list[0] == 'i' && list[1] == 'n' && list[2] == 'f' && list[3] == 'o'){
            return 5;
        }
        if (list[0] == 'e' && list[1] == 'x' && list[2] == 'i' && list[3] == 't'){
            return -1;
        }
        return 0;
    }



    else if (count == 6) {
        if (list[0] == 'r' && list[1] == 'e' && list[2] == 'c' && list[3] == 'e' && list[4] == 'n' && list[5] == 't') {
            return 7;
        }
    }

    return 0;
}



int main() {
    struct account* bank = create_account();
    long long accountNumber = 1000000000-1;
    int com=0;
    while (1){
        char input1[1000] = {0};
        char input2[100] = {0};
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

        //scanf("%s" , input1);
        com = command(input1);
        if (com == 0){
            if (ident == -1){
                printf("Invalid input\n");
            }
            else{
                char c=0;
                while (c != '\n'){
                    scanf("%c",&c);
                }
                printf("Invalid input\n");
            }

        }

        if (com == -1){
            break;
        }

        if (com == 1){
            char fName[35] = {0};
            char lName[35] = {0};
            scanf("%s",fName);
            scanf("%s",lName);
            //printf("%s %s",fName,lName);
            accountNumber++;
            add(bank,fName,lName,accountNumber);
            printf("Account number: %lld\n",accountNumber);

        }

        if (com == 8){
            long long accNum;
            long long amount;
            scanf("%lld %lld",&accNum,&amount);

            if (amount<=0){
                printf("Invalid amount\n");
            }

            else if (accNum<1000000 || accNum>accountNumber){
                printf("Invalid account number\n");
            }

            else{
                depo(accNum,bank,amount);
                printf("Success\n");
            }
        }

        if (com == 2){
            long long accNum;
            long long amount;
            scanf("%lld %lld",&accNum,&amount);

            if (amount<=0){
                printf("Invalid amount\n");
            }

            else if (accNum<1000000000 || accNum>accountNumber){
                printf("Invalid account number\n");

            }

            else{
                int res;
                res = with(accNum,bank,amount);
                if (res == -1){
                    printf("Not enough balance\n");
                }
                else{
                    printf("Success\n");
                }
            }
        }

        if (com == 3){
            long long accNum;
            scanf("%lld",&accNum);

            if (accNum<1000000000 || accNum>accountNumber){
                printf("Invalid account number\n");
            }
            else{
                printf("$%lld\n", balance(accNum,bank));
            }
        }

        if (com == 4){
            long long accNum1;
            scanf("%lld",&accNum1);
            long long accNum2;
            scanf("%lld",&accNum2);
            long long amount;
            scanf("%lld",&amount);

            if (amount<=0){
                printf("Invalid amount\n");
            }

            else if (accNum1<1000000000 || accNum1>accountNumber){
                printf("Invalid sender account number\n");
            }
            else if (accNum2<1000000000 || accNum2>accountNumber){
                printf("Invalid receiver account number\n");
            }
            else{
                long long res= transfer(accNum1,accNum2,amount,bank);
                if (res == -1){
                    printf("Not enough balance\n");
                }
                else{
                    printf("Success\n");
                }
            }
        }

        if (com == 5){
            long long accNum;
            scanf("%lld",&accNum);
            if (accNum<1000000000 || accNum>accountNumber){
                printf("Invalid account number\n");
            }
            else{
                char* name = infoname(accNum,bank);
                char* lname = infolname(accNum , bank);
                long long amount = infoamount(accNum,bank);
                int count = 0 ;

                printf("%s",name);


                printf(" ");
                printf("%s",lname);
                printf("\n");
                printf("$%lld\n" , amount);
            }


        }

        if (com == 6){
            int nums;
            char fName[35] = {0};
            char lName[35] = {0};
            scanf("%s",fName);
            scanf("%s",lName);
            scanf("%d",&nums);
            //printf("%s %s",fName,lName);
            long long first = accountNumber+1;
            struct account* new = addall(bank,fName,lName,first);
            accountNumber++;
            for (int i=1 ; i<nums ; i++){
                accountNumber++;
                new=addall(new,fName,lName,accountNumber);
            }
            printf("Account numbers: %lld-%lld\n",first,accountNumber);
        }

        if (com == 7){
            long long accNum;
            scanf("%lld",&accNum);
            if (accNum<1000000000 || accNum>accountNumber){
                printf("Invalid account number\n");
            }
            else{
                recent(accNum,bank);
            }

        }
    }

    return 0;
}
