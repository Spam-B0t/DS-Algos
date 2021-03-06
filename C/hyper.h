#include<stdio.h>

#define min(a, b) ((a)>(b)) ? (b):(a)


typedef struct{
    int len; long val[10000];
}hyper;

void inith(hyper *h){
    h->len=1; h->val[0]=0;
}

void copyh(hyper *a, hyper *b){
    for(int i=0; i<b->len; i++)a->val[i]=b->val[i];
    a->len=b->len;
}

void addh(hyper *a, hyper *b, int shift){
    int i=0;
    long x, rem=0;
    while(i<b->len || rem>0){
        x=rem;
        if(i+shift<a->len)x+=a->val[i+shift];
        else while(i+shift>=a->len){a->val[a->len]=0; a->len++;}
        if(i<b->len)x+=b->val[i];
        a->val[i+shift]=x%10000;
        rem=x/10000;
        i++;
    }
}

void mult_short(hyper *a, int b){
    int i;
    long x, rem=0;
    for(i=0; i<a->len; i++){
        x=a->val[i]*b+rem;
        a->val[i]=x%10000;
        rem=x/10000;
    }
    while(rem>0){a->len++; a->val[i]=rem%10000; rem/=10000; i++;}
}

void mult_hyper(hyper *a, hyper *b){
    hyper a_tmp, tmp;
    copyh(&a_tmp, a);
    copyh(&tmp, &a_tmp);
    mult_short(&tmp, b->val[0]);
    copyh(a, &tmp);
    for(int i=1; i<b->len; i++){
        copyh(&tmp, &a_tmp);
        mult_short(&tmp, b->val[i]);
        addh(a, &tmp, i);
    }
}

void div_short(hyper *a, int b){
    long x, rem=0, l=a->len-1;
    if(b>0)for(long i=l; i>=0; i--){
        x=rem*10000+a->val[i];
        rem=x%b;
        a->val[i]=x/b;
        if(a->val[i]==0 && a->len-1==i)a->len-=1;
    }
}

int mod_short(hyper *a, int b){
    int out=0;
    long mult=1;
    if(b>1)for(int i=0; i<a->len; i++){
        out=(out+a->val[i]*mult)%b;
        mult=(mult*10000)%b;
    }
    return out;
}

void print_hyper(hyper *a){
    printf("%ld", a->val[a->len-1]);
    for(int i=a->len-2; i>=0; i--)
        printf("%.4ld", a->val[i]);
}
