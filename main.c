#include "handoff_simulator.h"
#include <unistd.h>
#include <string.h>

int num = 10000;

void run(FILE *fp, char c, double val)
{

    switch (c)
    {
    case 'r': // meter->kilometer
        size_cell = val / 1000;
        fprintf(fp, "%lf,", size_cell);
        break;
    case 's': // km/h
        avg_speed = val;
        fprintf(fp, "%lf,", avg_speed);
        break;
    case 'd': // meter->kilometer
        avg_distance = val / 1000;
        fprintf(fp, "%lf,", avg_distance);
        break;
    case 't': // minute->hour
        avg_duration = val / 60;
        fprintf(fp, "%lf,", avg_duration);
        break;
    default:
        break;
    }

    int result = 0;
    double average = 0;

    for (int i = 0; i < num; i++)
    {
        result = simulate();
        average += (double)result / num;

        if (c == 'h')
            fprintf(fp, "%d\n", result);
    }

    if (c != 'h')
        fprintf(fp, "%lf\n", average);

    reset_param();
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    FILE *fp;

    fp = fopen("data.txt", "w");
    fprintf(fp, "handoff\n");
    run(fp, 'h', 0);
    fclose(fp);

    num = 100000;

    fp = fopen("data_r.txt", "w");
    fprintf(fp, "size_cell,handoff\n");
    for (double i = 100; i <= 1000; i += 10)
        run(fp, 'r', i);
    fclose(fp);

    fp = fopen("data_s.txt", "w");
    fprintf(fp, "avg_speed,handoff\n");
    for (double i = 2; i <= 10; i += 0.1)
        run(fp, 's', i);
    fclose(fp);

    fp = fopen("data_d.txt", "w");
    fprintf(fp, "avg_distance,handoff\n");
    for (double i = 10; i <= 1500; i += 10)
        run(fp, 'd', i);
    fclose(fp);

    fp = fopen("data_t.txt", "w");
    fprintf(fp, "avg_duration,handoff\n");
    for (double i = 0.1; i <= 20; i += 0.1)
        run(fp, 't', i);
    fclose(fp);

    return 0;
}
