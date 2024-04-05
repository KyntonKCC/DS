#include <stdio.h>
void hanoi(int, int, int, int);

int main() {
    int n, Tower1 = 1, Tower2 = 2, Tower3 = 3;
    scanf("%d", &n);
    hanoi(n, Tower1, Tower3, Tower2);
}

void hanoi (int n, int from, int to, int temp) {
    if (n == 1) 
        printf("%d %d %d\n", n, from, to);
    else {
        hanoi(n-1, from, temp, to);
        printf("%d %d %d\n", n, from, to);
        hanoi(n-1, temp, to, from);
    }
}