#include <stdio.h>

int main(void) {
    printf("running coop\n");
    fflush(stdout);
    fprintf(stderr, "some error!!!\n");
    return 0;
}
