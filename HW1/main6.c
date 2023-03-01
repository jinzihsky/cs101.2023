#include <stdio.h>

int main() {
    char a[] = "81c8g8u168";
    char r[][5] = {
        "I", "II", "III", "IV", "V",
        "VI", "VII", "VIII", "IX"
        };
    int size = sizeof(a) / sizeof(a[0]);
    for (int i = 0; i < size; i++) {
        if (a[i]>='0' && a[i]<='9') {
            printf("%s", r[a[i]-'1']);
        } else {
            printf("%c", a[i]);
        }
        printf(" ");
    }
    printf("\n");
    return 0;    
}
