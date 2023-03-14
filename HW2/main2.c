#include <stdio.h>

int main() {
    char c;
    int num = 1;
    FILE * ifp = fopen(__FILE__, "r");
    FILE * ofp = fopen("main2.txt", "w");
    if (ifp && ofp) {
        fprintf(ofp, "%02d ", num);
        while ((c = getc(ifp)) != EOF) {
            putc(c, ofp);
            if (c == '\n') {
                num++;
                fprintf(ofp, "%02d ", num);
            }
        }
        fclose(ifp);
        fclose(ofp);
    }
    printf("\n");
    return 0;
}

