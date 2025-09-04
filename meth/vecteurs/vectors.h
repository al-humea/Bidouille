#ifndef VECTORS_H
# define VECTORS_H
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
//vectors definition
typedef struct vec2{float x; float y;} vec2;
typedef struct vec3{float x; float y; float z;} vec3;

vec2 v2add(vec2 a, vec2 b);
vec3 v3add(vec3 a, vec3 b);
vec2 v2sub(vec2 a, vec2 b);
vec3 v3sub(vec3 a, vec3 b);
vec2 v2scal(float scal, vec2 a);
vec3 v3scal(float scal, vec3 a);
float v2norm(vec2 a);
float v3norm(vec3 a);
vec2 v2u(vec2 a);
vec3 v3u(vec3 a);
vec2 v2dist(vec2 a, vec2 b);
vec3 v3dist(vec3 a, vec3 b);


#endif 