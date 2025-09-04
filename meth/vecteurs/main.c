#include "vectors.h"

int main(void) {
    srand(time(NULL));
    printf("Expérimentations vectorielles:\n");
    printf("Initialisation de deux vecteurs 2D puis 3D aléatoire...\n");
    vec2 *a, *b;
    vec3 *c, *d;
    a = malloc(sizeof(vec2));
    a->x = rand() % 200 - 100;
    a->y = rand() % 200 - 100;
    printf("v2a={%.3f, %.3f}\n", a->x, a->y);
    b = malloc(sizeof(vec2));
    b->x = rand() % 200 - 100;
    b->y = rand() % 200 - 100;
    printf("v2b={%.3f, %.3f}\n", b->x, b->y);
    c = malloc(sizeof(vec3));
    c->x = rand() % 200 - 100;
    c->y = rand() % 200 - 100;
    c->z = rand() % 200 - 100;
    printf("v3c={%.3f, %.3f}\n", c->x, c->y, c->z);
    d = malloc(sizeof(vec3));
    d->x = rand() % 200 - 100;
    d->y = rand() % 200 - 100;
    d->z = rand() % 200 - 100;
    printf("v3d={%.3f, %.3f}\n", d->x, d->y, d->z);


    b = malloc(sizeof(vec2));
    c = malloc(sizeof(vec3));
    d = malloc(sizeof(vec3));

    free(a);
    free(b);
    free(c);
    free(d);
    return 0;
}