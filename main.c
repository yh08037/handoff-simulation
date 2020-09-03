#include "handoff_simulator.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int num = 10000;
    int result = 0;
    double average = 0;

    verbose = 1;

    for (int i = 0; i < num; i++)
    {
        if (verbose)
            printf("\n\n#################### start %d ####################\n", i + 1);
        result = simulate();
        printf("#%d handoff : %d\n", i + 1, result);
        average += (double)result / num;
    }
    printf("average handoff : %lf\n", average);

    return 0;
}
