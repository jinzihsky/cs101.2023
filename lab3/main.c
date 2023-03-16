#include <stdio.h>

typedef struct person{
    int id;
    char first_name[32];
    char last_name[32];
}person_t;

int main(){
    FILE* fp = fopen("person.bin", "w+");
    person_t p[5] = {{1, "IU", "Lee"},
                     {2, "IUU", "Lee"},
                     {3, "IUUU", "Lee"},
                     {4, "IUUUU", "Lee"},
                     {1, "IUUUUU", "Lee"},
        
    };
    for(int i = 0; i < 5; i++){
        fwrite(p + i, sizeof(person_t), 1, fp);
    }
    fseek(fp, 0, SEEK_SET);
    person_t tmp[1];
    int i=0;
    while(fread(tmp, sizeof(person_t), 1, fp)){
        printf("[%d] %d: %s %s\n", i,
                                    tmp[0].id,
                                    tmp[0].first_name,
                                    tmp[0].last_name);
        i++;
    }
    fclose(fp);
    return 0;
}
