#version 430
precision highp float;
#define M_PI 3.14159265358979

out vec4 oFragmentColor;
in vec3 v_pos;
in vec3 v_norm;
in float height;
layout(location=13) uniform vec3 uLightPos;
layout(location=14) uniform float uLightIntensity;
// MAIN PROGRAM
void main()
{
    // CONSTANT
    const vec3 gravelColor = vec3(0.29, 0.24, 0.22);
    const vec3 dirtColor = vec3(0.45, 0.34, 0.19);
    const vec3 grassColor = vec3(0.22, 0.63, 0.28);
    const vec3 rockColor = vec3(0.33, 0.31, 0.31);
    const vec3 snowColor = vec3(0.90, 0.90, 0.95);
    vec3 uKa = vec3(.8f);
    vec3 uKd = vec3(1.3f);
    vec3 normal = normalize(v_norm);
    if (gl_FrontFacing == false) normal = -normal;
    vec3 lightDir = normalize(uLightPos - v_pos);
    vec3 Ia = uLightIntensity * uKa;
    float diffuseTerm = max(0.f, dot(normal, lightDir));
    vec3 Id = uLightIntensity * uKd * vec3(diffuseTerm);
    Id = Id / M_PI; 
    

    vec3 gravelDirt = mix(gravelColor, dirtColor, smoothstep(-0.5, 0.02, height));
    vec3 dirtGrass = mix(gravelDirt, grassColor, smoothstep(0.03, 0.06, height));
    vec3 grassRock = mix(dirtGrass, rockColor, smoothstep(0.09, 0.10, height));
    vec3 rockSnow = mix(grassRock, snowColor, smoothstep(0.14, 0.15, height));
    vec3 color = rockSnow.rgb;

    vec3 finalColor = (Ia + Id)* color;
    oFragmentColor = vec4(finalColor, 1.f);
}