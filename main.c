#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>
#define nbr_of_ply 2

typedef struct node* ptr;

struct node {
    int coefficient;
    int power;
    ptr next;
};



typedef ptr list;
typedef ptr position;

void insert (list, int, int);
void printList (list);
void deleteList (list);
int readPoly (list, int);
void eliminateSimilarTerms (list);
position findPrevious (list, position);
int getValue (char *, int *);
list add (list, list);
list sub (list, list);
list mul (list, list);
double substitute (list, double);
int isSign (char *, int);
char nextChar (char *, int);
char previousChar (char *, int);
int isPower (char *, int);
int indexOfPreviousChar (char *, int);
int indexOfNextChar (char *, int);
int endOfTerm (char *, int);
void requestPoly(list);
int isInteger (double);
list doOperation (list, list, int);
int howToSub();
int valmenu(void);
//char* read_file(FILE*);



int wh;
double val,res;
int main()
{
    list L1 = (list) malloc(sizeof(struct node));
    L1 -> next = NULL;
    list L2 = (list) malloc(sizeof(struct node));
    L2 -> next = NULL;
    list summation = (list) malloc(sizeof(struct node));
    summation -> next = NULL;
    list multi = (list) malloc(sizeof(struct node));
    multi -> next = NULL;
    list diff1 = (list) malloc(sizeof(struct node));
    diff1 -> next = NULL;
    list diff2 = (list) malloc(sizeof(struct node));
    diff2 -> next = NULL;


    FILE *in ;

//open file
   // in = fopen("data.txt","r");



    int option;

    do{
        printf("\t\t        Menu\n");
        printf("\t\t1)Read data form file\n");
        printf("\t\t2)read data from screen\n");
        printf("\t\t3)Find sum\n");
        printf("\t\t4)Find diff(f1(x)-f2(x)\n");
        printf("\t\t5)Find diff(f2(x)-f1(x))\n");
        printf("\t\t6)Find product\n");
        printf("\t\t7)Exit\n");

        scanf("%d",&option);

        switch (option){

        case 1:
           // read_Data(in,l,nbr_of_ply);
               /**
    open file
    **/
    in = fopen("data.txt","r");
    char data[100]; /** the string where the data will be fitched;**/
    const char* data_from_file[2];
    char* polys;
    char* poly;
    /**
     get the data, and store it in this string
    **/
    int i=0;
    while(fgets(data, 100, in)){
        polys = strtok(data, ",");
       // data_from_file[i] = (char*)strtok(data, ",");
        //strcpy(data_from_file, polys);
        printf("%s\n", polys);
        data_from_file[i] = polys;
        i++;

    }

    /**
    close the file
    **/
    fclose(in);
printf("%s\n", data_from_file[0]);
printf("%s\n", data_from_file[1]);

    //data_from_file = read_file(in);
           break;
int Q;
        case 2:

            printf("\n\n");
            printf("\t\tCHOOSE WHAT YOU WANT TO ENTER\n");
            printf("\t\t1-enter first poly\n");
            printf("\t\t2-enter the second poly\n");
            scanf("%d",&Q);
            switch(Q){
        case 1:
            requestPoly(L1);
            break;
        case 2:
            requestPoly(L2);
            }

            break;

        case 3:

            summation=doOperation(L1, L2,1);
            printf("\n\n");
            printf("f1(x)+f2(x)=");
            printList(summation);
            printf("\n");
            printf("\t\t1-get value by subtitute\n");
            printf("\t\t2-return\n");
            scanf("%d",&wh);
            if(wh==1){
                printf("please enter value of x\n");
                scanf("%lf",&val);
                res=substitute(summation,val);
                printf("f1(%.2lf)+f2(%.2lf)=%.2lf",val,val,res);
                break;
            }
            else if(wh==2){
                break;
            }


        case 4:
            diff1=doOperation(L1, L2,2);
            printf("\n\n");
            printf("f1(x)-f2(x)=");
            printList(diff1);
            printf("\n");
            printf("\t\t1-get value by subtitute\n");
            printf("\t\t2-return\n");
            scanf("%d",&wh);
            if(wh==1){
                printf("please enter value of x\n");
                scanf("%lf",&val);
                res=substitute(diff1,val);
                printf("f1(%.2lf)+f2(%.2lf)=%.2lf",val,val,res);
                break;
            }
            else if(wh==2){
                break;
            }

        case 5:
            diff2=doOperation(L1,L2,3);
            printf("\n\n");
            printf("f2(x)-f1(x)=");
            printList(diff2);
            printf("\n");
            printf("\t\t1-get value by subtitute\n");
            printf("\t\t2-return\n");
            scanf("%d",&wh);
            if(wh==1){
                printf("please enter value of x\n");
                scanf("%lf",&val);
                res=substitute(diff2,val);
                printf("f1(%.2lf)+f2(%.2lf)=%.2lf",val,val,res);
                break;
            }
            else if(wh==2){
                break;
            }
        case 6:
            multi=doOperation(L1, L2,4);
            printf("\n\n");
            printf("f1(x)*f2(x)=");
            printList(multi);
            printf("\n");
            printf("\t\t1-get value by subtitute\n");
            printf("\t\t2-return\n");
            scanf("%d",&wh);
            if(wh==1){
                printf("please enter value of x\n");
                scanf("%lf",&val);
                res=substitute(multi,val);
                printf("f1(%.2lf)+f2(%.2lf)=%.2lf",val,val,res);
                break;
            }
            else if(wh==2){
                break;
            }

        default:
            printf("\t\t No such option! Enter your choice again please:\n\n");
            continue;
        }

    }while (option != 7);

    deleteList(L1);
    free(L1);
    deleteList(L2);
    free(L2);

    return 0;
}


list doOperation (list L1, list L2, int op){


    if ( (L1 -> next == NULL) || (L2 -> next == NULL) ){
        printf("Error! There is no entered functions.\n\n");
        printf("Press any key to return to main menu\n");
        return;
    }

    list result;

    if (op == 1){
        result = add(L1,L2);
        return result;
    }

    else if (op == 2){
        result = sub(L1,L2);
        return result;
    }

    else if (op == 3){
        result = sub(L2,L1);
        return result;
    }

    else if (op == 4){
        result = mul(L1,L2);
        return result;
    }

    printf("\n");

}

void requestPoly(list L){

    int n = 100;

    char option;

    printf("\n");
    printf("Enter the polynomial please\n");
    printf("Hint: Enter it in this form: Ax^n + Bx^m + Cx + x^s + D\n\n");

    deleteList(L);

    while(!readPoly(L, n)){

        deleteList(L);
        printf("\n");
        printf("1)Retry\n");
        printf("2)return\n\n");
        option = getch();

        if (option == '1'){
            system("cls");
            printf("Enter the polynomial please\n");
            printf("Hint: Enter it in this form: Ax^n + Bx^m + Cx + x^s + D\n\n");
        }
        else if (option == '2'){
            system("cls");
            return;
        }
        else{
            while( !( (option == '1')||(option == '2') ) ){
                system("cls");
                printf("you don't enter right thing:\n\n");
                printf("1)Retry\n");
                printf("2)Return\n\n");

                option = getch();
            }
        }
    }


    printf("\n");
    printf("Press any key to return to main menu\n");
    getch();
    system("cls");
}

int readPoly (list L ,int n){                     // this function will read the polynomial, insert its term to the list L in sorted due to larger power, eliminate similar terms in the polynomial and return 1 for success
                                                    // if the polynomial is incorrect, then zero will be returned
    char *poly = (char *) malloc(n * sizeof(char));

    int i = 0;
    int co = 1, pow = 0;
    int powerFound = 0;

    fflush(stdin);      // this function will clear the '\n' created after using scanf from the screen, so that gets can work properly
    gets(poly);

    if (   (poly[0] == '\0')  ||  (  (poly[0] == ' ')&&(nextChar(poly, 0) == '\0')  )   ){
        printf("Error! You didn't enter anything !\n");
        free(poly);
        return 0;
    }

    while ( (i != n - 1) && (poly[i] != '\0') ){

        if (poly[i] == 'X'){
            printf("Error! Please use small x only!\n");
            free(poly);
            return 0;
        }

        if ( (poly[i] == '+') || (poly[i] == '-') || (poly[i] == '*') ){            // making exception for cases like "x + " ,"x +++ 3"

            if ( (poly[i] == '+') || (poly[i] == '-') ){
                if ( (nextChar(poly, i) == '+') || (nextChar(poly, i) == '-') ){

                    int j = indexOfNextChar(poly, i);

                    if ( (nextChar(poly, j) == '+') || (nextChar(poly, j) == '-') ){     // next of next
                        printf("Error! You can't use more than one sign!\n");
                        free(poly);
                        return 0;
                    }
                }
            }

            if ( nextChar(poly,i) == '\0' ){
                printf("Error! Binary Operation must have two operators!\n");
                free(poly);
                return 0;
            }
        }

        if (poly[i] == '*') {                                                        // making exceptions for cases like x * x or x * a

            if  (    ( isdigit(previousChar(poly, i)) && isdigit(nextChar(poly, i)) ) || ( isdigit(previousChar(poly, i)) && (nextChar(poly, i) == 'x') )    ){

                int j = indexOfPreviousChar(poly, i);     // next of next

                if ( (j != -1) && isPower(poly, j)){
                    printf("Error! You can't use * expect between a coefficient and x (the coefficient at first, e.g 2 * x) or between two numbers (coefficient for some x)!\n");
                    free(poly);
                    return 0;
                }
            }

            else if ( isdigit(previousChar(poly, i)) ){         // "a * -x" or "b * +x" are valid
                if ( (nextChar(poly, i) == '+') || (nextChar(poly, i) == '-') ){
                    // do nothing, this is valid
                }
            }

            else{
                printf("Error! You can't use * expect between a number and x (the number first) or between two numbers and not for the power!\n");
                free(poly);
                return 0;
            }
        }

        else if (poly[i] == 'x')
            pow = 1;

        else if (poly[i] == '^'){

            if ( (previousChar(poly, i) == 'x') && (nextChar(poly, i) == '+') ){    // a special case for ax^+b

                short j = indexOfNextChar(poly, i);      // index of '+'

                j++;

                while(isdigit(poly[j]))
                    j++;

                j--;

                if ( !isdigit(nextChar(poly, j)) ){    // next of next ,,, if the char after + is not a number
                    printf("Error! Wrong use of power! You can only use it in this form ax^n\n");
                    free(poly);
                    return 0;
                }
            }

            else if ( (previousChar(poly, i) == 'x') && (nextChar(poly, i) == '-') ){
                printf("Error! You can't use a negative power in a polynomial!\n");
                free(poly);
                return 0;
            }

            else if  ( ( previousChar(poly, i) != 'x' ) || !isdigit( nextChar(poly, i) ) ){          // must be in the form x ^ n
                printf("Error! Wrong use of power! You can only use it in this form ax^n\n");
                free(poly);
                return 0;
            }

            else if ( isdigit(nextChar(poly, i)) ){             // in x^n then n must be the end of this term not like x^3x

                short j = indexOfNextChar(poly, i);

                if (!endOfTerm(poly, j)){
                    printf("Error! Power must be only a single number!\n");
                    free(poly);
                    return 0;
                }

            }

            powerFound = 1;
        }

        else if ( isdigit(poly[i]) ){          // making sure it is a number

            if (previousChar(poly, i) == 'x'){
                printf("Error! Coefficient must before x (e.g ax)\n");
                free(poly);
                return 0;
            }

            if (!powerFound){

                co *= getValue(poly, &i);      // (*=) is to keep the sign, and this function will return the coefficient and increment i to reach the index of the first character after the coefficient
                i--;

                if ( isdigit(nextChar(poly, i)) ){                              // here i is the index of the last digit in the coefficient, so we just need to check nextChar to make sure that we don't have two consecutive numbers without operator
                    printf("Error! A space between two numbers! Missed operator or something!\n");
                    free(poly);
                    return 0;
                }

            }
            else{
                pow = getValue(poly, &i);
                powerFound = 0;
                i--;
            }
        }

        else if ( (poly[i] != '+') && (poly[i] != '-') && (poly[i] != ' ') ){
            printf("Error! Invalid input %c\n",poly[i]);
            free(poly);
            return 0;
        }


        if (    (   (  ( poly[i] == '-')||(poly[i] == '+')  ) && ( !isSign(poly, i) )   ) || (poly[i+1] == '\0')    ){

                insert(L,co,pow);
                co = 1;
                pow = 0;
        }


        if (poly[i] == '-'){
            if (!powerFound)
                co *= -1;
        }

        i++;
    }

    if (i == n - 1){
        printf("Error! Too long polynomial!\n");
        free(poly);
        return 0;
    }

    free(poly);
    eliminateSimilarTerms(L);

    return 1;
}

int getValue (char *poly, int *i){    // This function will read any number (coefficient or power) and return it
    int value;                             // After executing this function, i will be the index of the first character after the number read

    int j = *i;
    while ( isdigit(poly[*i]) )
        (*i)++;

    char c = poly[*i];               // save the char at index i

    poly[*i] = '\0';                 // put a null character on this char so we will have a null after the number
    value = atoi(&poly[j]);          // convert the string number to an integer starting from j(index of first digit) and ending at i (the index of null)
    poly[*i] = c;                    // return the char to its position in the string

    return value;
}

void insert (list L, int co, int pow){     // this function will insert the polynomial term in the right place

    position temp=(position)malloc( sizeof(struct node) );

    if (temp != NULL){
        temp->coefficient= co;
        temp->power= pow;
    }
    else{
        printf("Out of Memory!\n");
        exit(0);
    }

    position p,previous;

    p = L -> next;
    previous = L;                          // previous points at the node before p

    while (p != NULL){
        if (p -> power > temp -> power){
            p = p -> next;
            previous = previous -> next;
        }
        else{
            previous -> next = temp;
            temp -> next = p;
            break;
        }
    }

    if (p == NULL){                // if the node that we want to add has a power that is smaller than the other nodes (or if the list is empty)
        previous -> next = temp;
        temp -> next = NULL;
    }
}

void eliminateSimilarTerms (list L){

    position p, q, previous;

    p = L -> next;

    while (p != NULL){
        q = p -> next;

        while (q != NULL){
            if (p -> power == q -> power ){
                p -> coefficient += q -> coefficient;
                previous = findPrevious(L,q);
                previous -> next = q -> next;
                free(q);
                q = previous -> next;
            }
            else{
                q = q -> next;
            }
        }

        p = p -> next;
    }

    // the following code deletes the zero from the polynomial

  /*  previous = L;
    p = L -> next;

    if ( (p != NULL) && (p -> next != NULL) ){  // p -> next != NULL is to check that the node containing the zero is not the only node in the polynomial

        while (p -> next != NULL){
            p = p -> next;
            previous = previous -> next;
        }

        if (p -> coefficient == 0){
            free(p);
            previous -> next = NULL;
        }
    }*/
}

position findPrevious (list L, position p){

    position previous = L;

    while ( (previous -> next != NULL) && (previous -> next != p) )
        previous = previous -> next;

    return previous;
}

void printList (list L){

    position p = L -> next;

    if (L -> next != NULL){
        while (p != NULL){

            if (p -> coefficient == 0){
                if (L -> next -> next == NULL)  // if this node is the only node, then print zero, otherwise do nothing
                printf("0");
            }

            else if (p -> power == 0)
                printf("%d ",p -> coefficient);

            else if ( (p -> power == 1) && ( (p -> coefficient != 1) && (p -> coefficient != -1) ) )
                printf("%dx ",p -> coefficient);

            else if ( (p -> power == 1) && (p -> coefficient == 1) )
                printf("x ");

            else if ( (p -> power == 1) && (p -> coefficient == -1) )
                printf("-x ");

            else if ( (p -> power > 1) && (p -> coefficient == 1) )
                printf("x^%d ",p -> power);

            else if ( (p -> power > 1) && (p -> coefficient == -1) )
                printf("-x^%d ",p -> power);

            else
                printf("%dx^%d ",p -> coefficient, p -> power);

            if (p -> next != NULL)  // don't put a plus after the last term
                printf("+ ");

            p = p -> next;
        }

        printf("\n");
    }
    else
        printf("Nothing to print! List is Empty\n");
}

void deleteList (list L){

    position p = L -> next;

    while (L -> next != NULL){
        L -> next = p -> next;
        free(p);
        p = L -> next;
    }
}

list add (list L1, list L2){                            /* this function will make a new list consisting of the 2 lists that we want to add
                                                           and then call the function eliminateSimilarTerm to find the final result */
    list sum = (list) malloc( sizeof(struct node) );

    if (sum != NULL){
        sum -> next = NULL;

        while (L1 -> next != NULL){
            insert(sum,L1 -> next -> coefficient,L1 -> next -> power);
            L1 = L1 -> next;
        }

        while (L2 -> next != NULL){
            insert(sum,L2 -> next -> coefficient,L2 -> next -> power);
            L2 = L2 -> next;
        }

        eliminateSimilarTerms (sum);
    }

    return sum;
}

list sub (list L1, list L2){                        /* this function will make a new list consisting of the 2 lists that we want to subtract,
                                                       but with coefficients of the second one multiplied by -1 ,and then call the function eliminateSimilarTerm to find the final result */
    list diff = (list) malloc( sizeof(struct node) );

    if (diff != NULL){
        diff -> next = NULL;

        while (L1 -> next != NULL){
            insert(diff, L1 -> next -> coefficient, L1 -> next -> power);
            L1 = L1 -> next;
        }

        while (L2 -> next != NULL){
            insert(diff, -(L2 -> next -> coefficient), L2 -> next -> power);
            L2 = L2 -> next;
        }

        eliminateSimilarTerms (diff);
    }

    return diff;
}

list mul (list L1, list L2){
                                                            /* this function will create a new list, multiply each term in the first list with all the terms of the second one
                                                               ,put the result in the new list, and then call the function eliminateSimilarTerm to find the final result */
    list product = (list) malloc( sizeof(struct node) );

    if (product != NULL){
        product -> next = NULL;

        position L2_firstNode = L2 -> next;

        L1 = L1 -> next;
        L2 = L2 -> next;

        while (L1 != NULL){
            while (L2 != NULL){
                insert (product, (L1 -> coefficient) * (L2 -> coefficient) , (L1 -> power) + (L2 -> power));
                L2 = L2 -> next;
            }

            L2 = L2_firstNode;
            L1 = L1 -> next;
        }

        eliminateSimilarTerms (product);
    }

    return product;
}

double substitute (list L, double x){           // this function will substitute a value in the polynomial an return the result

    double result = 0;
    L = L -> next;

    while (L != NULL){
        result += (L -> coefficient) * pow(x, L -> power);
        L = L -> next;
    }

    return result;
}

int isSign (char *poly,int i){                       // this function will determine if the given char in the given equation is a sign

    if ( ! ( (poly[i] == '+')||(poly[i] == '-') ) )
        return 0;

    char previousCharacter = previousChar(poly, i);

    if ( isdigit(previousCharacter) || previousCharacter == 'x' )
        return 0;
    else
        return 1;
}

char nextChar (char *str,int i){             // this function will return the next char in the string regardless of the spaces

    i++;

    while (str[i] == ' ')
        i++;

    return str[i];
}

char previousChar (char *str,int i){         // this function will return the first character before the one at index i (excluding spaces) and return a null char if i = 0

    if (i == 0)
        return '\0';

    i--;

    while ( (i > -1) && (str[i] == ' ') )
        i--;

    if (i == -1)
        return ' ';
    else
        return str[i];
}

int indexOfPreviousChar (char *str,int i){         // this function will return the index of the first previous char in the given string, regardless of the spaces and if i reached -1, then -1 will be returned

    i--;

    while ( (i > -1) && (str[i] == ' ') )
        i--;

    return i;
}

int indexOfNextChar(char *str,int i){         // this function will return the index of the first previous char in the given string, regardless of the spaces and if i reached the null char, then the index of the null char will be returned

    i++;

    while (str[i] == ' ')
        i++;

    return i;
}

int isPower (char *poly,int i){      // this function check if the value at index i is a power

    while ( isdigit(poly[i]) )
        i--;

    i++;                                // increment i by 1 so that we find previousChar in next step

    if (previousChar(poly, i) == '^')
        return 1;
    else
        return 0;

}

int endOfTerm (char *poly,int i){    // this function check if the value at index i is the last thing in the term (no 'x' or '*' after it)

    while ( isdigit(poly[i]) )
        i++;

    i--;                                // decrement i by 1 so that we find nextChar in next step

    if ( (nextChar(poly, i) == 'x') || (nextChar(poly, i) == '*') )
        return 0;
    else
        return 1;
}

int isInteger (double num){         // this function will the if the given double number can be replaced with an integer number

    int n = (int) num;

    if (n == num)
        return 1;
    else
        return 0;
}
/*
char* read_file(FILE* file){

    file = fopen("data.txt","r");
    char data[100];
    char *polys;
    char* poly;
    polys = fgets(data, 100, file);
    printf("%s", polys);
    while(fgets(data, 100, file)){
        polys = strtok(data, ",");
        printf("%s\n", polys);
    }
    while(fgets(data, 100, file)){

        char *poly;
        poly = strtok(data, ",");
        printf("%s\n", poly);
    }

    fclose(file);

    return polys;
}
*/
