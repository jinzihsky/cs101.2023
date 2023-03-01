#include <stdio.h>

char detectcase(char c); 
char clonecase(char c, char ref); 
char casenum(char c); 

int main() {
    char a[] = "Hello";

    int size = sizeof(a) / sizeof(a[0]) - 1;

    for (int i = 0; i < size; i++) {
        printf("%c", clonecase(a[size-i-1], a[i]));
    }
    printf("\n");

    return 0;
}

char detectcase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 'A';
    }
    if (c >= 'a' && c <= 'z') {
        return 'a';
    }
}

char clonecase(char c, char ref) {
    return casenum(c) + detectcase(ref);
}

char casenum(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c-'A';
    }
    if (c >= 'a' && c <= 'z') {
        return c-'a';
    }
}
