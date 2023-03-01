#include <stdio.h>
#define SIZE(a) sizeof(a)/sizeof(a[0])-1

int string_to_int(char s[], int size);
int isnum(int c);

int main() {
    char a[] = "-99acbc";
    char b[] = "99acbc";
    char c[] = "ac-99bc";
    string_to_int(a, SIZE(a));
    string_to_int(b, SIZE(b));
    string_to_int(c, SIZE(c));

}

int string_to_int(char s[], int size) {
    int begin = -1; 
    int v = 0;     
    for (int i = 0; i < size; i++) {
        int c = isnum(s[i]);
        if (c >= 0) {
            if (begin < 0) {
                begin = i;
            }
            v = v*10 + c;
        } else {
            if (begin >= 0) {
                break;
            }
        }
    }
    if (s[begin-1]=='-') {
        v *= -1;
    }
    printf("%d\n", v);
    return v;
}

int isnum(int c) {
    if (c >= '0' && c <= '9') {
        return c-'0';
    }
    return -2;
}
