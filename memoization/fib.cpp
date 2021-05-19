#include <stdio.h>
#include <time.h>

int fib(int n);
int fib_memo(int n);
int memo[999] = {0,1,0,};

int main(){
    int k;
    scanf("%d", &k);
    FILE *fp = fopen("time.csv", "w");
    printf("normal fib time");
    for(int i=0; i<k; i++){
        clock_t start = clock();
        fib(i);
        clock_t end = clock();
        fprintf(fp, "%d,",end-start);
        printf("%d\n",end-start);
    }

    fprintf(fp, "\n");
    printf("memoization fib time");
    for(int i=0; i<k; i++){
        clock_t start2 = clock();
        fib_memo(i);
        clock_t end2 = clock();
        fprintf(fp, "%d,", end2-start2);
        printf("%d\n", end2-start2);
    }
    fclose(fp);
}

int fib(int n){
    if(n==0) return 0;
    if(n==1) return 1;
    return (fib(n-1)+fib(n-2));
}

int fib_memo(int n){
    if (memo[n] != 0) return memo[n];
    else if(n==0) return 0;
    else if(n==1) return 1;
    else{
        int f = fib_memo(n-1) + fib_memo(n-2);
        memo[n] = f;
        return f;
    }

}