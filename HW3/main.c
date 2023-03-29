#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXLOT 69
#define SPLOT 10
#define NORMAL 6
#define MAX_GEN 5
#define LOTTO_M 100

int lot[MAXLOT];


void init_lot(void);
void shuf_lot(void);
void sort_lot(void);
void swap_lot(int i, int j);
int sp_lot(void);
int inlist(int list[], int a, int b, int c);

typedef struct {
    int receipt_id;
    int receipt_price;
    char receipt_time[32];
    int lotto_set[5][7];
} lotto_record_t;


int main(int argc, char* argv[]) {
    srand((unsigned) time(NULL));

    time_t curtime;
    char time_str[80];
    int n;
    FILE* fp;
    FILE* ftxt;
    int last_rec = -1;
    int ticket_no = 0;
    char TXT[80];
    int a, b, c;
    lotto_record_t lottos[LOTTO_M];
    
    printf("歡迎光臨長庚樂透彩購買機台\n");
    fp = fopen("record.bin", "rb");
    if (fp) {
        for (int i=0; i<LOTTO_M; i++) {
            int c = fread(&lottos[i], sizeof(lotto_record_t), 1, fp);
            if (!c) {
                last_rec = i - 1;
                break;
            }
        }
        fclose(fp);
        ticket_no = lottos[last_rec].receipt_id;
        fp = fopen("record.bin", "ab");
    } else {
        fp = fopen("record.bin", "wb");
    }
    ticket_no++;
    sprintf(TXT, "lotto[%05d].txt", ticket_no);
    
    printf("請問您要買幾組樂透彩：");
    scanf("%d", &n);
    if (n == 0) {
        fclose(fp);
        printf("請輸入中獎號碼 (最多三個)：");
        scanf("%d %d %d", &a, &b, &c);
        printf("輸入中獎號碼為：%02d %02d %02d\n", a, b, c);
        printf("以下為中獎彩券：\n");
        for (int i=0; i<=last_rec; i++) {
            for (int j=0; j<5; j++) {
                int chk;
                if (chk=inlist(lottos[i].lotto_set[j], a, b, c)) {
                    printf("彩券 No. %d\n", j+1);
                    printf("售出時間：%s\n", lottos[i].receipt_time);
                    printf("號碼：");
                    for (int k=0; k<7; k++) {
                        printf("%02d ", lottos[i].lotto_set[j][k]);
                    }
                    printf("\n");
                }
            }
        }
        return 0;
    }
    lottos[last_rec+1].receipt_id = ticket_no;
    lottos[last_rec+1].receipt_price = n * 100;
    printf("已為您購買的 %d 組樂透組合輸出至 lotto[%05d].txt\n", n, ticket_no);

    ftxt = fopen(TXT, "w");
    fprintf(ftxt, "========= lotto649 =========\n");

    time(&curtime);
    strcpy(time_str, ctime(&curtime));
    for (int i=0; i<sizeof(time_str)/sizeof(time_str[0]); i++) {
        if (time_str[i] == '\0') {
            time_str[i-1] = '\0';
            break;
        }
    }
    fprintf(ftxt, "========+ No.%05d +========\n", ticket_no);
    fprintf(ftxt, "= %s =\r\n", time_str);
    strcpy(lottos[last_rec+1].receipt_time, time_str);

    init_lot();

    for (int i=0; i<MAX_GEN; i++) {
        shuf_lot();
        sort_lot();
        fprintf(ftxt, "[%1d]: ",i+1);
        for (int j=0; j<NORMAL; j++) {
            if (i<n) {
                fprintf(ftxt, "%02d ", lot[j]);
                lottos[last_rec+1].lotto_set[i][j] = lot[j];
            } else {
                fprintf(ftxt, "-- ");
                lottos[last_rec+1].lotto_set[i][j] = 0;
            }
        }
        if (i<n) {
            int splot = sp_lot();
            fprintf(ftxt, "%02d\n", splot);
            lottos[last_rec+1].lotto_set[i][NORMAL] = splot;
        } else {
            fprintf(ftxt, "--\n");
        }
    }
    fwrite(&lottos[last_rec+1], sizeof(lottos[0]), 1, fp);
    fclose(fp);

    fprintf(ftxt, "========= cise@CGU =========\n");
    fclose(ftxt);
    return 0;
}

void init_lot(void) {
    for (int i=0; i<MAXLOT; i++) {
        lot[i]=i+1;
    }
}

void shuf_lot(void) {
    int tmp, k;
    for (int i=MAXLOT-1; i>0; i--) {
        k = rand() % (i+1);
        swap_lot(i, k);
    }
}

int sp_lot(void) {
    for (int i=NORMAL; i<MAXLOT; i++) {
        if (lot[i] <= SPLOT) {
            return lot[i];
        }
    }
    return -1;
}

void sort_lot(void) {
    int tmp;
    for (int i=0; i<NORMAL; i++) {
        for (int j=0; j<NORMAL; j++) {
            if (lot[i] < lot[j]) {
                swap_lot(i, j);
            }
        }
    }
}

void swap_lot(int i, int j) {
   int tmp = lot[i];
   lot[i] = lot[j];
   lot[j] = tmp;
}

int inlist(int list[], int a, int b, int c) {
    for (int i=0; i<7; i++) {
        if (list[i] == a)
            return 1;
        if (list[i] == b)
            return 1;
        if (list[i] == c)
            return 1;
    }
    return 0;
}
