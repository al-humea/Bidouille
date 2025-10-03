#version 430
// INPUT
layout(location = 1) in vec3 position_in;
// OUTPUT
out vec3 v_pos; // position in view space
out vec3 v_norm;
out float height;
// UNIFORM
layout(location = 0) uniform mat4 uModelMatrix;
layout(location = 1) uniform mat4 uViewMatrix;
layout(location = 2) uniform mat4 uProjectionMatrix;
layout(location = 3) uniform float uTerrainElevation;
layout(location = 4) uniform vec2 uNoiseOffset;
layout(location = 5) uniform vec2 uNoiseScale;
layout(location = 6) uniform float uStartHeight;
layout(location = 7) uniform float uWeight;
layout(location = 8) uniform float uMult;
layout(location = 9) uniform float uNoisePower;
layout(location = 10) uniform int uFrequency;
layout(location = 11) uniform int uResolution;
layout(location = 12) uniform mat3 uMVnormalMatrix;

float fnoise2(vec2 p)
{
    vec2 f = fract(p);
    p = floor(p);
    float v = p.x + p.y * 1000.0;
    vec4 r = vec4(v, v + 1.0, v + 1000.0, v + 1001.0);
    r = fract(10000.0 * sin(r * .001));
    f = f * f * (3.0 - 2.0 * f);
    return 2.0 * (mix(mix(r.x, r.y, f.x), mix(r.z, r.w, f.x), f.y)) - 1.0;
}
float vertexHeight(vec2 v)
{
    vec2 st = vec2(v.x + uNoiseOffset.x, v.y + uNoiseOffset.y) * uNoiseScale;
    vec2 pos = vec2(st * uNoisePower);
    // fractal noise
    float h = uStartHeight;
    float w = uWeight;
    float m = uMult;
    for(int i = 0; i < uFrequency; ++i)
    {
        h += w * fnoise2(pos * m);
        w *= 0.5;
        m *= 2.0;
    }
    return h / uTerrainElevation;
}

vec3 computeNormalTri(vec3 A, vec3 B, vec3 C)
{
    return normalize(cross(B - A, C - A));
}
vec3 computeNormal(vec3 pos)
{
    float step = 1.f / float(uResolution - 1);
    // Get the 2D position of neighboring left, top, right, bottom, top-left and bottom-right vertices
    vec2 l2d = vec2(pos.x - step, pos.z);
    vec2 t2d = vec2(pos.x, pos.z - step);
    vec2 r2d = vec2(pos.x + step, pos.z);
    vec2 b2d = vec2(pos.x, pos.z + step);
    vec2 tl2d = vec2(pos.x - step, pos.z - step);
    vec2 br2d = vec2(pos.x + step, pos.z + step);
    // Get the 3D position of these 6 neighbors with the procedurale height
    vec3 l = vec3(l2d.x, vertexHeight(l2d), l2d.y);
    vec3 t = vec3(t2d.x, vertexHeight(t2d), t2d.y);
    vec3 r = vec3(r2d.x, vertexHeight(r2d), r2d.y);
    vec3 b = vec3(b2d.x, vertexHeight(b2d), b2d.y);
    vec3 tl = vec3(tl2d.x, vertexHeight(tl2d), tl2d.y);
    vec3 br = vec3(br2d.x, vertexHeight(br2d), br2d.y);
    // Compute the normal of the six neighboring triangles
    vec3 n1 = computeNormalTri(pos, l, tl);
    vec3 n2 = computeNormalTri(pos, tl, t);
    vec3 n3 = computeNormalTri(pos, t, r);
    vec3 n4 = computeNormalTri(pos, r, br);
    vec3 n5 = computeNormalTri(pos, br, b);
    vec3 n6 = computeNormalTri(pos, b, l);
    // Compute the normal based on the 6 neighbor's triangle normals
    vec3 normal = normalize(n1 + n2 + n3 + n4 + n5 + n6);
    return -normal;
}

// MAIN PROGRAM
void main()
{
    height = vertexHeight(position_in.xz);
    vec4 viewPos = uViewMatrix * uModelMatrix * vec4(position_in.x, height, position_in.z, 1.0);
    v_norm = uMVnormalMatrix * computeNormal(vec3(position_in.x, height, position_in.z));
    v_pos = viewPos.xyz;
    // - write position with matrix transformations into screen space
    gl_Position = uProjectionMatrix * viewPos;
}