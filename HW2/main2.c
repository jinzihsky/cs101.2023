#include <stdio.h>

int main() {
    char c;
    FILE * ifp = fopen(main2.c, "r+");
    FILE * ofp = fopen("main2.txt", "w+");
    int num = 1;
    fprintf(ofp, "01 ");
    while ((c = getc(ifp)) != EOF) {
        c == '\n' ? fprintf(ofp,"\n%02d ", ++num) : fprintf(ofp, "%c", c);
    }   
    fclose(ifp);
    fclose(ofp);
    return 0;
}
