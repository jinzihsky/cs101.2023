#include <stdio.h>

void rep(char* str, char oldC, char newC){
    while (*str) {
        (*str == oldC) ? (*str = newC, str) : str++;
    }//if(*str == oldC){
    //*str = newC;
    //str++;
}

int main(){
    char str[100], oldC = 'a', newC = 'A';
    printf("Enter any  string: ");
    scanf("%s", str);
    printf("\nString before replacing: \n%s", str);
    rep(str, oldC, newC);
    printf("\n\nString after replacing %c with %c : \n%s", oldC, newC, str);
    
    return 0;

}
