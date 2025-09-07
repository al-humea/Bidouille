#ifndef VECTORS_H
# define VECTORS_H
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
//vectors definition only on vec3 cause no time
typedef struct vec3{float x; float y; float z;} vec3;
vec3 v3add(vec3 a, vec3 b);
vec3 v3sub(vec3 a, vec3 b);
vec3 v3scal(float scal, vec3 a);
float v3norm(vec3 a);
vec3 v3u(vec3 a);
float v3dist(vec3 a, vec3 b);
//vectors2
float v3scalprod(vec3 a, vec3 b);
float v3angle(vec3 a, vec3 b);
vec3 v3prod(vec3 a, vec3 b);
#endif 