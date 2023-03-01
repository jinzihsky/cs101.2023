#include <stdio.h>

int main() {
    char a[] = {-9, 8, 7, 6, 5, -4, 3, -2, 1};
    int i = 4;

    int size = sizeof(a) / sizeof(a[0]);
    if (i > size) {
        printf("Warning! You have designated a number i=%d\n", i);
        printf("which is greater than the size of array (%d)\n.", size);
        printf("Now i=%d is used instead as the argument.\n", size);
        i = size;
    }
    char big[i];

    big[0] = a[0];

    for (int j = 1; j < size; j++) {
        int comp = j <= i ? j : i;
        for (int k = 0; k < comp; k++) {
            if (a[j] >= big[k]) {
                for (int m = i-1; m > k; m--) {
                    big[m] = big[m-1];
                }
                big[k] = a[j];
                break;
            } else {
                if (k == comp-1 && comp < i) {
                    big[k+1] = a[j];
                }
            }
        }
    }
    printf("%d\n", big[i-1]);
    return 0;
}
