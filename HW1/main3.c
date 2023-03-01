#include <stdio.h>

int main() {
    char a[]="ABCabcABC";
    int shift=4;

    printf("%s\n", a);
    printf("%d\n", shift);
    for (int i=shift; i<sizeof(a)/sizeof(a[0])-1; i++) {
        printf("%c", a[i]);
    }
    for (int i=0; i<shift; i++) {
        printf("%c", a[i]);
    }
    printf("\n");
    return 0;
}
