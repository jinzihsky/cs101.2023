#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;


int lot[69];

void init(void) {
    for (int i = 0; i < 69; i++) {
        lot[i] = i+1;
    }
}


void swap(int i, int j) {
   int p = lot[i];
   lot[i] = lot[j];
   lot[j] = p;
}

void shuf(void) {
    int p, k;
    for (int i = 69-1; i > 0; i--) {
        k = rand() % (i+1);
        swap(i, k);
    }
}

int sp(void) {
    for (int i = 6; i < 69; i++) {
        if (lot[i] <= 10) {
            return lot[i];
        }
    }
    return -1;
}

void sort(void) {
    int p;
    for (int i = 0; i < 6; i++) {
        for (int j=0; j < 6; j++) {
            if (lot[i] < lot[j]) {
                swap(i, j);
            }
        }
    }
}

int main(int argc, char* argv[]){
    srand((unsigned) time(NULL));
    
    time_t curtime;
    char timstr[80];
    
    int n;
    FILE *fp;
    FILE* fpt;
    int last = -1;
    int ticn = 0;
    char txt[80];
    lotto_record_t lotto[100];
    
    printf("歡迎光臨長庚樂透購買機台\n");
    fp = fopen("record.bin", "rb");
    if (fp) {
        for (int i = 0; i < 100; i++) {
            int c = fread(&lotto[i], sizeof(lotto_record_t), 1, fp);
            if (!c) {
                last = i - 1;
                break;
            }
        }
        fclose(fp);
        ticn = lotto[last].receipt_id;
        fp = fopen("record.bin", "ab");
    } else {
        fp = fopen("record.bin", "wb");
    }
    ticn++;
    sprintf(txt, "lotto%05d.txt", ticn);
    
    
    printf("請問您要購買幾組樂透:");
    scanf("%d", &n);
    if(n == 0){
        fclose(fp);
        int pr[10];
        int nc;
        printf("請輸入中獎號碼(最多三個):");
        for(int i = 0; i < 3; i++){
            scanf("%d", &pr[i]);
            nc = i + 1;
            char ch = getchar();
            if(ch == '\n'){
                break;
            }
        }
        printf("輸入中獎號碼為:");
        for (int i = 0; i < nc; i++) {
            printf("%02d ", pr[i]);
        }
        printf("\n");
        printf("以下為中獎彩券\n");
        for (int i = 0; i <= last; i++) {
            for (int j = 0; j < 5; j++) {
                int chk;
                if (chk = pr[i]) {
                    printf("彩券 No. %d\n", j+1);
                    printf("售出時間：%s\n", lotto[i].receipt_time);
                    printf("號碼：");
                    for (int k = 0; k < 7; k++) {
                        printf("%02d ", lotto[i].lotto_set[j][k]);
                    }
                    printf("\n");
                }
            }
        }
        return 0;
    }
    lotto[last+1].receipt_id = ticn;
    lotto[last+1].receipt_price = n * 50;
    printf("已為您購買的 %d 組樂透組合輸出至 lotto%05d.txt\n", n, ticn);
    fpt = fopen(txt, "w");
    fprintf(fpt, "========= lotto649 =========\n");
    
    time(&curtime);
    strcpy(timstr, ctime(&curtime));
    for (int i=0; i<sizeof(timstr)/sizeof(timstr[0]); i++) {
        if (timstr[i] == '\0') {
            timstr[i-1] = '\0';
            break;
        }
    }
    fprintf(fpt, "========+ NO.%05d +========\n", ticn);
    fprintf(fpt, "= %s =\r\n", timstr);
    strcpy(lotto[last+1].receipt_time, timstr);
    
    init();

    for (int i = 0; i < 5; i++) {
        shuf();
        sort();
        fprintf(fpt, " [%1d]: ",i+1);
        for (int j = 0; j < 6; j++) {
            if (i<n) {
                fprintf(fpt, "%02d ", lot[j]);
                lotto[last+1].lotto_set[i][j] = lot[j];
            } else {
                fprintf(fpt, "-- ");
                lotto[last+1].lotto_set[i][j] = 0;
            }
        }
        if (i<n) {
            int splot = sp();
            fprintf(fpt, "%02d\n", splot);
            lotto[last+1].lotto_set[i][6] = splot;
        } else {
            fprintf(fpt, "--\n");
        }
    }
    fwrite(&lotto[last+1], sizeof(lotto[0]), 1, fp);
    fclose(fp);

    fprintf(fpt, "========= cise@CGU =========\n");
    fclose(fpt);
    return 0;
}
