//Jonathon Irigoyen jo839870

#include <stdio.h>
#include "kw26.h"
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include <memory.h>


Int40 *kw26Add(Int40 *p, Int40 *q){
    Int40 *parse = malloc(sizeof(Int40));
    if (p->digits == NULL)
        return NULL;
    if (q->digits == NULL)
        return NULL;
    parse->digits = calloc(40, sizeof(int));
    int carry = 0, i;
    for(i = 0; i<40; i++){
        parse->digits[i] = p->digits[i]+q->digits[i] + carry;
        carry=0;
        if(parse->digits[i] > 15){
            carry = 1;
            parse->digits[i] = parse->digits[i] - 16;
        }
        
    }
    return parse;
}

Int40 *kw26Destroyer(Int40 *p){
    if(NULL == p)
        return 0;
    free(p->digits);
    free(p);
    return 0;
}

Int40 *fibKw26(int n, Int40 *first, Int40 *second){
    //f(0) is hwconfigvar and f(1) is crypto var
    int i;
    Int40 *p, *q;
    Int40 *temp = malloc(sizeof(Int40));
    temp->digits = malloc(sizeof(int)*40);
    p = kw26Add( first, second);
    q = kw26Add( p, second);
    if (n == 0)
        return first;
    if(n == 1)
        return second;
    if (n == 2)
        return p;
    if (n==3)
        return q;

    for (i = 3; i<n; i++){
        temp = kw26Add(p, q);
        p = q;
        q = temp;
    }

    return temp;
}
Int40 *parseString(char *str){
    //convert string to int40
    int i= 0, b,d= 0;
    Int40 *parse = malloc(sizeof(Int40));
    
    parse->digits = malloc(sizeof(int)*40);
    
    if (str == NULL)
        return NULL;
     while(str[i] != '\0'){
         d++;
         i++;
         
     }
   
    if(d<39){

        d = 40-d;
        for (i=0; i<d; i++)
            parse->digits[39-i] = 0;
        for (i = 0; i<40-d; i++){
            b =  str[i] - '0';
            if(b>48)
                b = b-39;
            parse->digits[39-d-i] = b;
        }


    }
    else
    {for (i = 0; i<40; i++){
        if(str[i] == '\0')
            parse->digits[i] = 0;
        b =  str[i] - '0';
        
        if(b>48)
            b = b-39;
        parse->digits[39-i] = b;
    }
    }
    
    return parse;
    
}

Int40 *loadHWConfigVariable(int doSeed){
    
    Int40 *a = malloc(sizeof(Int40));
    int b = 0, c[4], d, e, i, j;
    a->digits = malloc(sizeof(int)*40);
    if(doSeed == 0){
        for(i = 0; i<40; i++)
            a->digits[i] = 1;
        return a;
    }
    else
    {
    srand(time(NULL));
        d = (rand() %90000+10000);
        for(b = 0;b<5; b++){
            c[b] = d%10;
            d /=10;
        }
        for(b=0; b<8; b++){
            e = b*5+5;
            j =0;
            for(i=5*b; i<e; i++){
                a->digits[i] = c[j];
            j++;
            }
                }
    }
    return a;
}

Int40 *loadCryptoVariable(char *inputFilename){
    FILE *file =fopen(inputFilename, "r");
    Int40 *a = malloc(sizeof(Int40));
    a->digits = malloc(sizeof(int)*40);
    int c, i;
    for (i = 0; i<40; i++){
        c = fgetc(file);
        c =  c - '0';
        if(c>48)
            c = c-39;
       a->digits[39-i] = c;
    }
    
        
    
    return a;
}

Int40 *loadPlainText(char *inputFilename){
    FILE *file =fopen(inputFilename, "r");
    int i= 0, b,d= 0, e, f[40];
    Int40 *parse = malloc(sizeof(Int40));
    
    parse->digits = malloc(sizeof(int)*40);
    for(e = 0; e<40; e++){
         f[e] = fgetc(file);
    }
    if (file == NULL)
        return NULL;
    while(f[i] != '\0'){
        d++;
        i++;
        
    }
    
    if(d<39){
        
        d = 40-d;
        for (i=0; i<d; i++)
            parse->digits[39-i] = 0;
        for (i = 0; i<40-d; i++){
        
            parse->digits[39-d-i] = b;
        }
        
        
    }
    else
    {for (i = 0; i<40; i++){
        if(f[i] == '\0')
            parse->digits[i] = 0;
        b =  f[i];
       
        parse->digits[39-i] = b;
    }
    }
    fclose(file);
    return parse;
    
    
}
Int40 *encrypt(Int40 *key, Int40 *inputText){
    Int40 *xor = malloc(sizeof(Int40));
    xor->digits = malloc(sizeof(int)*40);
    int i;
    for (i = 0; i<40; i++)
        xor->digits[i] = key->digits[i] ^ inputText->digits[i];
 
    return xor;
}


void kw26Rating(void){
    kw26RatingStruct *rating = malloc(sizeof(kw26RatingStruct));
    rating->NID = malloc(sizeof(char)*9);
    rating->degreeOfDifficulty = 3.0;
    rating->duration = 15.0;
    rating->NID = "jo839870";
    fprintf(stderr, "%s;", rating->NID);
    fprintf(stderr, "%lf;", rating->degreeOfDifficulty);
    fprintf(stderr, "%lf", rating->duration);
    free(rating);
        
}
