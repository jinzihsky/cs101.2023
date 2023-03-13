#include <stdio.h>

int main() {
    FILE * ifp, * ofp;
    char c;
    int line_number = 1;
    ifp = fopen(__FILE__, "r");
    ofp = fopen("main2.txt", "w");
    if (ifp && ofp) {
        fprintf(ofp, "%02d ", line_number);
        while ((c = getc(ifp)) != EOF) {
            putc(c, ofp);
            if (c == '\n') {
                line_number++;
                fprintf(ofp, "%02d ", line_number);
            }
        }
        fclose(ifp);
        fclose(ofp);
    }
    printf("\n");
    return 0;
}

