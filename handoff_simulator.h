#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SQRT3 1.73205080756887729353
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

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

double size_cell = 0.5;         // kilometer
double avg_speed = 4.0;         // km/h
double avg_distance = 0.1;      // kilometer
double avg_duration = 2.0 / 60; // hour
int verbose = 0;

Point vertex[6] = {{SQRT3 / 2.0, -1 / 2.0},
                   {SQRT3 / 2.0, 1 / 2.0},
                   {0, 1},
                   {-SQRT3 / 2.0, 1 / 2.0},
                   {-SQRT3 / 2.0, -1 / 2.0},
                   {0, -1}};

////////////////////////////// declarations //////////////////////////////

void reset_param();

void init_vertex();
void reset_vertex();

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

////////////////////////////// definitions //////////////////////////////

void reset_param()
{
    size_cell = 0.5;
    avg_speed = 4.0;
    avg_distance = 0.1;
    avg_duration = 2.0 / 60;
    verbose = 0;
}

void init_vertex()
{
    for (int i = 0; i < 6; i++)
    {
        (vertex + i)->x *= size_cell;
        (vertex + i)->y *= size_cell;
    }
}

void reset_vertex()
{
    (vertex + 0)->x = (vertex + 1)->x = SQRT3 / 2.0;
    (vertex + 0)->y = (vertex + 4)->y = -1 / 2.0;
    (vertex + 1)->y = (vertex + 3)->y = 1 / 2.0;
    (vertex + 2)->x = (vertex + 5)->x = 0;
    (vertex + 2)->y = 1;
    (vertex + 3)->x = (vertex + 4)->x = -SQRT3 / 2.0;
    (vertex + 5)->y = -1;
}

double standard_uniform()
{
    return (double)rand() / RAND_MAX;
}

double uniform(double a, double b)
{
    // b must be larger than a!!
    return standard_uniform() * (b - a) + a;
}

double exponential(double lambda)
{
    // lambda must be positive!!
    return -log(1 - standard_uniform()) / lambda;
}

int in_cell(Node *node)
{
    if (fabs(node->point.x) > size_cell * SQRT3 / 2.0)
        return 0;
    else if (fabs(node->point.x / SQRT3 + node->point.y) > size_cell)
        return 0;
    else if (fabs(-node->point.x / SQRT3 + node->point.y) > size_cell)
        return 0;

    return 1;
}

void print_point(Point point)
{
    printf("(%lf, %lf) ", point.x * 1000, point.y * 1000);
}

void print_node(Node *node)
{
    print_point(node->point);
    printf("%lf %d\n", node->duration * 60, node->handoff);
}

Node *create_node()
{
    return (Node *)malloc(sizeof(Node));
}

void destroy_node(Node *node)
{
    free(node);
}

void init_node(Node *node)
{
    while (1)
    {
        node->point.x = uniform(-size_cell * SQRT3 / 2.0, size_cell * SQRT3 / 2.0);
        node->point.y = uniform(-size_cell, size_cell);

        if (in_cell(node))
            break;
    }

    // average call duration : 2 min = 1/30 hour
    node->duration = exponential(1.0 / avg_duration);
    node->handoff = 0;
}

int on_segment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return 1;

    return 0;
}

int orientation(Point p, Point q, Point r)
{
    // 0 --> p, q and r are colinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise

    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0; // colinear

    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

int do_intersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return 1;

    // Special Cases : colinear
    if (o1 == 0 && on_segment(p1, p2, q1))
        return 1;
    if (o2 == 0 && on_segment(p1, q2, q1))
        return 1;
    if (o3 == 0 && on_segment(p2, p1, q2))
        return 1;
    if (o4 == 0 && on_segment(p2, q1, q2))
        return 1;

    return 0;
}

int choose_segment(Node *node, Node *newnode, int segment)
{
    int result = -1;

    for (int i = 0; i < 6; i++)
    {
        if (segment != -1 && i == (segment + 3) % 6)
            continue;

        if (do_intersect(node->point, newnode->point, vertex[i], vertex[(i + 1) % 6]))
        {
            result = i;
            break;
        }
    }

    return result;
}

void shift_node(Node *node, Node *newnode, int segment)
{
    double dx = vertex[segment].x + vertex[(segment + 1) % 6].x;
    double dy = vertex[segment].y + vertex[(segment + 1) % 6].y;

    node->point.x -= dx;
    node->point.y -= dy;

    newnode->point.x -= dx;
    newnode->point.y -= dy;

    newnode->handoff++;
}

void count_handoff(Node *node, Node *newnode)
{
    int segment = -1;

    while (!in_cell(newnode))
    {
        if (verbose)
        {
            printf("new node : ");
            print_point(newnode->point);
            printf("is out of cell\n");
        }

        segment = choose_segment(node, newnode, segment);

        if (verbose)
            printf("adjacent segment : %d\n", segment);

        shift_node(node, newnode, segment);

        if (verbose)
        {
            printf("shifted new node : ");
            print_point(newnode->point);
            printf("\n");
        }
    }
}

Node *move_node(Node *node)
{
    double speed = uniform(avg_speed - 2, avg_speed + 2); // [2km/h, 6km/h]
    double direction = uniform(0, 2 * M_PI);              // [0, 2pi]
    double distance = exponential(1.0 / avg_distance);    // average distance : 100 m

    Node *newnode = create_node();

    if (verbose)
    {
        printf("distance generated : %lf\n", distance * 1000);
        printf("time taking : %lf\n", distance / speed * 60);
    }

    if (distance > node->duration * speed)
    {
        if (verbose)
            printf("call duration time out\n");
        distance = node->duration * speed;
        newnode->duration = 0;
    }
    else
        newnode->duration - distance / speed;

    newnode->point.x = node->point.x + distance * cos(direction);
    newnode->point.y = node->point.y + distance * sin(direction);
    newnode->handoff = node->handoff;

    count_handoff(node, newnode);

    destroy_node(node);
    return newnode;
}

int simulate()
{
    int result = 0;
    Node *node = create_node();

    init_vertex();
    init_node(node);

    if (verbose)
    {
        printf("#init#  ");
        print_node(node);
    }

    do
    {
        node = move_node(node);
        if (verbose)
        {
            printf("#moved# ");
            print_node(node);
            printf("\n");
        }
    } while (node->duration > 0);

    result = node->handoff;

    reset_vertex();
    destroy_node(node);

    return result;
}