#include <stdio.h>

int main() {
    char a[]="AABBBCCCCddd";
    int f[256]={0};
    for (int i=0; i<sizeof(a)/sizeof(a[0])-1; i++) {
        f[a[i]]++;
    }
    for (int i=0; i<sizeof(f)/sizeof(f[0]); i++) {
        if (f[i]>0) {
            printf("%c%d", i, f[i]);
        }
    }
    printf("\n");
    return 0;
}
