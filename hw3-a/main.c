#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define N 20

int c = 0;
time_t t;
struct tm* d;
typedef struct record {
    time_t t;
    char n;
    char f;
    char to;
} record_t;
record_t r[(2 << N) - 1];

void hanoi(int n, char f, char to, char temp) {
    if (n == 1) {
        r[c].t = time(NULL);
        r[c].n = n;
        r[c].f = f;
        r[c].to = to;
        c++;
        return;
    }
    hanoi(n-1, f, temp, to);
    r[c].t = time(NULL);
    r[c].n = n;
    r[c].f = f;
    r[c].to = to;
    c++;
    hanoi(n-1, temp, to, f);
}

int main(int argc, char const *argv[]) {
    int n = N;
    if (argc > 1) {
        n = atoi(argv[1]);
        if (n>N) {
            printf("請輸入 1~%d 之間的數字\n", N);
            return 0;
        }
    }
    printf("* 河內塔 %d 層 (遞迴) ***\n",n);
    t = time(NULL);
    d = localtime(&t);
    printf("計算開始時間：%d %02d%02d %02d:%02d:%02d\n", d->tm_year+1900, d->tm_mon+1, d->tm_mday, d->tm_hour, d->tm_min, d->tm_sec);
    printf("計算中...");
    hanoi(n, 0, 2, 1);
    printf("完成!\n");
    t = time(NULL);
    d = localtime(&t);
    printf("計算結束時間：%d %02d%02d %02d:%02d:%02d\n", d->tm_year+1900, d->tm_mon+1, d->tm_mday, d->tm_hour, d->tm_min, d->tm_sec);
    printf("總共移動 %d 次\n", c);
    printf("輸出移動過程到檔案中...");
    
    FILE* fp = fopen("hanoi.txt","w");
    for (int i=0; i<c; i++) {
        d = localtime(&r[i].t); 
        fprintf(fp,"%d (%d %02d%02d %02d:%02d:%02d) : %dP from %c to %c\n",
            i+1,
            d->tm_year+1900,
            d->tm_mon+1,
            d->tm_mday,
            d->tm_hour,
            d->tm_min,
            d->tm_sec,
            r[i].n,
            r[i].f+'A',
            r[i].to+'A'
        );
    }
    fclose(fp);

    printf("完成!\n");
    return 0;
}
