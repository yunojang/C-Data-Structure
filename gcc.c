#include <stdio.h>

int A = 10;
int static B = 20;

#define INF 10000
#define MAX(a,b) (a > b? a: b)

int main() {
    int a = INF;
    printf("%d ", MAX(a, B));
}