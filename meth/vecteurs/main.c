#include "vectors.h"

void vprint(const char *n, vec3 a){
    printf("v3 %s ={%.3f, %.3f, %.3f}\n",n, a.x, a.y, a.z);
}

int main(void) {
    srand(time(NULL));
    printf("Expérimentations vectorielles:\n");
    printf("Initialisation de deux vecteurs 3D aléatoire...\n");
    vec3 c, d;
    c.x = rand() % 200 - 100;
    c.y = rand() % 200 - 100;
    c.z = rand() % 200 - 100;
    d.x = rand() % 200 - 100;
    d.y = rand() % 200 - 100;
    d.z = rand() % 200 - 100;
    vprint("a",c);
    vprint("b",d);
    vprint("a+b", v3add(c, d));
    vprint("a-b", v3sub(c, d));
    vprint("a*3", v3scal(3, c));
    printf("|a| = %.3f\n", v3norm(c));
    vprint("â", v3u(c));
    printf("Distance entre a et b = %f\n", v3dist(c, d));
    return 0;
}