#include <stdio.h>
//Catalan
//C(0) = C(1) = 1
//C(n+1) = C(0)*C(n) + C(1)*C(n−1) + ... + C(n−1)*C(1) + C(n)*C(0), n >= 2
int main(void){
    int n;
    scanf("%d", &n);

    // int dp[n+1];
    // for(int i = 0; i < n + 1; i++)
    //     dp[i] = 0;
    // dp[0] = 1;
    // for(int i = 1; i <= n; i++){
    //     for(int j = 0; j < i; j++){
    //         dp[i] += dp[j] * dp[i - j - 1];
    //     }
    // }
    // printf("%d\n", dp[n]);


    //Catalan formulaC : (2n,n)/(n+1)
    long res = 1 ;
    for (int i = n + 1 ; i <= 2 * n; i++) 
        res = res * i / (i - n);
    printf("%ld\n", res / (n + 1));
    return 0;
}