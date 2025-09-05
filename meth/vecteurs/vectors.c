#include "vectors.h"

vec3 v3add(vec3 a, vec3 b){
    vec3 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;
}

vec3 v3sub(vec3 a, vec3 b){
    vec3 c;
    c.x = a.x-b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

vec3 v3scal(float scal, vec3 a){
    vec3 c;
    c.x = a.x * scal;
    c.y = a.y * scal;
    c.z = a.z * scal;
    return c;
}

float v3norm(vec3 a){
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

vec3 v3u(vec3 a){
    vec3 c = {.x=0, .y=0, .z=0};
    float n = v3norm(a);
    if (n < 1e-8f)
        return c;
    c.x = a.x/n;
    c.y = a.y/n;
    c.z = a.z/n;
    return c;
}

float v3dist(vec3 a, vec3 b){
    return v3norm(v3sub(b, a));
}