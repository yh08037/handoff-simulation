#ifndef HANDOFF_SIMULATOR_H
#define HANDOFF_SIMULATOR_H

#define _USE_MATH_DEFINES
#define SQRT3 1.73205080756887729353
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define SIZE_CELL 0.5           // kilometer
#define AVG_DURATION (1.0 / 30) // hour
#define AVG_DISTANCE 0.1        // kilometer

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int verbose = 0;

typedef struct _Point
{
    double x; // kilometer
    double y; // kilometer
} Point;

typedef struct _Node
{
    Point point;     // (kilometer, kilometer)
    double duration; // hour
    int handoff;     // count
} Node;

Point vertex[6] = {{SIZE_CELL * SQRT3 / 2.0, -SIZE_CELL / 2.0},
                   {SIZE_CELL * SQRT3 / 2.0, SIZE_CELL / 2.0},
                   {0, SIZE_CELL},
                   {-SIZE_CELL * SQRT3 / 2.0, SIZE_CELL / 2.0},
                   {-SIZE_CELL * SQRT3 / 2.0, -SIZE_CELL / 2.0},
                   {0, -SIZE_CELL}};

void swap(double *a, double *b);
double standard_uniform();
double uniform(double a, double b);
double exponential(double lambda);

int in_cell(Node *node);
void print_point(Point point);
void print_node(Node *node);
Node *create_node();
void destroy_node(Node *node);
void init_node(Node *node);

int on_segment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
int do_intersect(Point p1, Point q1, Point p2, Point q2);
int choose_segment(Node *node, Node *newnode, int segment);

void shift_node(Node *node, Node *newnode, int segment);
void count_handoff(Node *node, Node *newnode);
Node *move_node(Node *node);

int simulate();

#endif // HANDOFF_SIMULATOR_H