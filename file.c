#include <stdio.h>
#include "file.h"

void read_file(FILE* fp, char* content) {
    fread(content, sizeof(char), sizeof content, fp);
}

unsigned int fsize(FILE* fp) {
    fseek(fp, 0, SEEK_END);
    int f_length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return f_length;
}
