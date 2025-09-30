#version 430
precision highp float;

out vec4 oFragmentColor;
in vec3 pos;
layout(binding = 0) uniform samplerCube uSampler;

// MAIN PROGRAM
void main()
{
	oFragmentColor = texture(uSampler, pos);
}