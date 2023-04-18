#include <stdio.h>

#define SYS 10

typedef struct my_mm {
    char m[SYS];
    int* p[SYS];
    int i[SYS];
    int n[SYS];
} my_mm_t;
int g_mem[SYS];
my_mm_t mms;

int* my_calloc(int n, int size);
void mem_status(void);
void my_free(int *p);


int main() {
    int* np1 = my_calloc(1, 1);
    int* np2 = my_calloc(1, 2);
    int* np3 = my_calloc(1, 3);
    int* np4 = my_calloc(1, 4);
    my_free(np1);
    my_free(np4);
    int* np5 = my_calloc(1, 5);
    int* np6 = my_calloc(1, 1);
    #ifdef DEBUG
        int* np7 = my_calloc(1, 3);
        int* np8 = my_calloc(1, 5);
        my_free(np1);
        my_free(np1);
    #endif
    return 0;
}


int* my_calloc(int n, int size) {
    int cnt = 0, start = 0;
    for (int i=0; i<SYS; i++) {
        if (mms.m[i] == 0) {
            if (cnt == 0) {
                start = i;
            }
            cnt++;
            if (cnt == n*size) {
                for (int i=start; i<start+n*size; i++) {
                    mms.m[i] = 1;
                }
                for (int i=0; i<SYS; i++) {
                    if (mms.p[i] == NULL) {
                        mms.p[i] = &g_mem[start];
                        mms.i[i] = start;
                        mms.n[i] = n*size;
                        break;
                    }
                }
                for (int i=0; i<n*size; i++) {
                    g_mem[start+i] = 0;
                }
                mem_status();
                #ifdef DEBUG
                    printf(" address = %p, allocated %d bytes", &g_mem[start], n*size);
                #endif
                printf("\n");
                return &g_mem[start];
            }
        } else {
            cnt = 0;
        }
    }
    mem_status();
    printf(" <- Out of space\n");
    return NULL;
}

void mem_status(void) {
    for (int i=0; i<SYS; i++) {
        printf("%d", mms.m[i]);
    }
}

void my_free(int *p) {
    for (int i=0; i<SYS; i++) {
        #ifdef DEBUG
            printf("i = %d, p = %p, mms.p[i] = %p\n", i, p, mms.p[i]);
        #endif
        if (mms.p[i] == p) {
            mms.p[i] = NULL;
            #ifdef DEBUG
                printf("i = %d, mms.p[i] = %p matched, and is cleared to %p\n", i, p, mms.p[i]);
            #endif
            for (int j=0; j<mms.n[i]; j++) {
                mms.m[mms.i[i]+j] = 0;
            }
            mem_status();
            #ifdef DEBUG
                printf(" address = %p, freed %d bytes", p, mms.n[i]);
            #endif
            mms.n[i] = 0;
            mms.i[i] = 0;
            printf("\n");
            return;
        }
    }
    mem_status();
    printf(" %p Invalid pointer\n", p);
}
