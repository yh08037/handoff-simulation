#include "handoff_simulator.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int result = 0;
    double average = 0;

    int num = 10000;
    verbose = 0;

    char c;
    while ((c = getopt (argc, argv, "n:v:")) != -1)
        switch (c){
            case 'n':
                num = atoi(strdup(optarg));
                break;
            case 'v':
                verbose = atoi(strdup(optarg));
                break;
            default:
                break;
        }

    FILE *fp = fopen("data.txt", "w");

    for (int i = 0; i < num; i++)
    {
        if (verbose)
            printf("\n\n#################### start %d ####################\n", i + 1);

        result = simulate();
        
        if (verbose)
            printf("#%d handoff : %d\n", i + 1, result);
        
        fprintf(fp, "%d\n", result);

        average += (double)result / num;
    }
    
    fclose(fp);

    printf("average handoff : %lf\n", average);

    return 0;
}
