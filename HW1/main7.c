#include <stdio.h>
#define T(a,n) t[a[n]-'0'][a[n+1]-'0'][a[n+2]-'0'][a[n+3]-'0']
#define P(a) printf("%c%c\n", T(a,0), T(a,4))

char n2c(int n);

int main() {
    char a[] = "10001111";
    char b[] = "10011110";

    // creat a 4D table
    int c = 0;
    char t[2][2][2][2] = {0};
    for (int i1=0; i1<2; i1++) {
        for (int i2=0; i2<2; i2++) {
            for (int i3=0; i3<2; i3++) {
                for (int i4=0; i4<2; i4++) {
                    t[i1][i2][i3][i4] = n2c(c++);
                }
            }
        }
    }
    P(a);
    P(b);
    return 0;
}

char n2c(int n) {
    if (n < 10) {
        return n+'0';
    } else {
        return n+'A'-10;
    }
}
