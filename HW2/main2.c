#include <stdio.h>

int main() {
    FILE * ifp, * ofp;
    char c;
    int num = 1;
    ifp = fopen(__FILE__, "r");
    ofp = fopen("main2.txt", "w");
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

