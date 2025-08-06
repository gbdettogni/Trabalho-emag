#include "stdio.h"

int main(){
    FILE* tsl = fopen("tsl", "w");
    fprintf(tsl, "1");
    fclose(tsl);
    return 0;
}