#include <unistd.h>
#include <stdio.h>

int main(int ac, char **argv)
{
    execve(argv[1], &argv[1], NULL);
    fprintf(stderr, "Oops!\n");
    return -1;
}
