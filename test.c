#include "handoff_simulator.h"
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));

    int num = 10000;

    /* parameter parsing */

    char c;
    while ((c = getopt (argc, argv, "n:r:s:d:t:v:")) != -1)
        switch (c){
            case 'n': 
                num = atoi(strdup(optarg));
                break; 
            case 'r': // meter->kilometer
                size_cell = (double)atoi(strdup(optarg)) / 1000;
                break;
            case 's': // km/h
                avg_speed = (double)atoi(strdup(optarg));
                break;
            case 'd': // meter->kilometer
                avg_distance = (double)atoi(strdup(optarg)) / 1000;
                break;
            case 't': // minute->hour
                avg_duration = (double)atoi(strdup(optarg)) / 60;
                break;
            case 'v':
                verbose = atoi(strdup(optarg));
                break;
            default:
                break;
        }

    /* start simulation */

    FILE *fp = fopen("data.txt", "w");
    int result = 0;
    double average = 0;

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
