#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "file.h"

struct Coord {
    int x;
    int y;
};

struct Bridge {
    struct Coord from;
    struct Coord to;
    char c;
};

size_t lcs(char *seq_a, char *seq_b, char *ch_a, char *ch_b) {
    size_t len_a = strlen(seq_a);
    size_t len_b = strlen(seq_b);
    int table[len_a + 1][len_b + 1];
    memset(table, 0, sizeof table);
    struct Bridge bridges[len_b * len_a + 2];
    int bridge_num = 0;
    size_t lcs_counter = 0;

    int i, j;

    for (i = 1; i < len_a + 1; i++) {
        for (j = 1; j < len_b + 1; j++) {
            int top = table[i-1][j];
            int left = table[i][j-1];
            int val = top < left ? left : top;

            if (seq_a[i-1] == seq_b[j-1]) {
                struct Coord from = {.x = i - 1 , .y = j - 1};
                struct Coord to = {.x = i, .y = j};
                struct Bridge b = {.from = from, .to = to, .c = seq_a[i-1]};
                bridges[bridge_num++] = b;
                val = table[i-1][j-1];
                ++val;
            }

            table[i][j] = val;
        }
    }

    --j;--i;

    while (j != 0 || i != 0) {
        int val = table[i][j];
        int move = i != 0 ? table[i - 1][j] : -1;

        if (move == val) {
            //printf("Remove %c from input A\n", seq_a[i-1]);
            ch_a[--i] = -1;
            continue;
        }

        move = j != 0 ? table[i][j - 1] : -1;

        if (move == val) {
            //printf("Add %c to input B\n", seq_b[j-1]);
            ch_b[--j] = 1;
            continue;
        }

        if (move != val) {
            //printf("Keep %c\n", seq_b[i-1]);
            int b_i;
            for (b_i = 0; b_i < bridge_num; b_i++){
                struct Bridge b = bridges[b_i];
                if (b.to.x != i || b.to.y != j)
                    continue;

                ch_a[--i] = 0;
                ch_b[--j] = 0;
                i = b.from.x;
                j = b.from.y;
                break;
            }
        }
    }

    return 0;
}

void print_char(char c, int type){
    const char* RED = "\033[0;31m";
    const char* GREEN = "\033[0;32m";
    const char* NC = "\033[0m";

    if (type == 1) {
	printf("%s", GREEN);
    }

    if (type == -1) {
	printf("%s", RED);
    }

    printf("%c%s", c, NC);
}

int main(int argc, char **argv) {
    FILE *fp;
    fp = fopen("test.txt","r");
    int f_length = fsize(fp);
    char file_buffer[fsize(fp)];
    fread(file_buffer, sizeof(char), sizeof file_buffer, fp);
    fclose(fp);

    fp = fopen("test2.txt","r");
    int f_length_2 = fsize(fp);
    char file_buffer_2[fsize(fp)];
    fread(file_buffer_2, sizeof(char), sizeof file_buffer_2, fp);
    fclose(fp);

    char lcs_res[sizeof file_buffer_2];

    char ch_a[sizeof file_buffer];
    char ch_b[sizeof file_buffer_2];

    lcs(file_buffer, file_buffer_2, ch_a, ch_b);

    int i;
    printf("Old File\n");
    printf("-------------------------------------------\n");
    for (i = 0; i < sizeof ch_a -1; i++) {
	print_char(file_buffer[i], ch_a[i]);
    }
    printf("\n");
    printf("-------------------------------------------\n");
    printf("\n\n");

    printf("New File\n");
    printf("-------------------------------------------\n");
    for (i = 0; i < sizeof ch_b - 1; i++) {
        print_char(file_buffer_2[i], ch_b[i]);
    }
    printf("\n");

    return 0;  // make sure your main returns int
}
